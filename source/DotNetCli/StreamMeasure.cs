using System.Text.Json;
using System.Text.Json.Serialization;
using Protocol;

namespace DotNetCli;

internal class StreamMeasure : StreamHandlerBase
{
    private readonly RunningStatistics _statisticsTotal;
    private List<RunningStatistics>? _statistics;
    private DateTime? _startTime;
    private DateTime? _prevTime;
    private int _currentFrameNumber;
    private int _framesReceived;
    private int _framesLeft;
    private int _totalDropped;
    private int _chunksReceived;
    private TimeSpan _maxTimeDelta;
    private TimeSpan _clockDrift;
    private IClient _client;

    public StreamMeasure(IClient client, int count) : base(client)
    {
        _framesLeft = count;
        _client = client;
        _statisticsTotal = new();
        _maxTimeDelta = TimeSpan.Zero;
        _clockDrift = TimeSpan.Zero;
    }

    public override void Start(StreamConfig stream)
    {
        base.Start(stream);

        var estimated = TimeSpan.FromSeconds(_framesLeft / stream.Frequency);

        // If there are 9 or less elements, collect stats for feature each individually  
        if (ElementCount <= 9)
        {
            _statistics = new List<RunningStatistics>(ElementCount);
            for (int i = 0; i < ElementCount; i++)
            {
                _statistics.Add(new RunningStatistics());
            }
        }

        Client.WriteLine($"Reading {_framesLeft} frames from stream {stream.Name} estimated sample time {estimated}. Please wait...");
    }

    public override bool ProcessDataChunk(DataChunk data)
    {
        if (Stream == null || _framesLeft == 0)
            return false;

        var now = DateTime.UtcNow; 
        _startTime ??= now;

        _chunksReceived++;
        _framesReceived += data.FrameCount;

        int expectedTotal = data.FrameCount * ElementSize * ElementCount;
        if (data.Payload.Span.Length != expectedTotal)
        {
            Client.ErrorMessage($"Unexpected payload size of {data.Payload.Span.Length} bytes. Expected {expectedTotal} bytes.");
            return false;
        }

        var dropped = data.FrameNumber - _currentFrameNumber;

        // if (dropped != 0)
        //    Client.WriteLine($"Dropped {dropped} frames.");
        
        var startDelta = now - _startTime.Value;

        if(startDelta > TimeSpan.Zero)
            _clockDrift = startDelta - TimeSpan.FromSeconds((data.FrameNumber + data.FrameCount) / (double)Stream.Frequency);

        TimeSpan delta = TimeSpan.Zero;
        if (_prevTime.HasValue)
        {
            delta = ((now - _prevTime.Value) - TimeSpan.FromSeconds((dropped + data.FrameCount) / (double)Stream.Frequency)).Duration();
            if (delta > _maxTimeDelta)
                _maxTimeDelta = delta;
        }

        // WriteLine($"Chunk {_chunksReceived}: Measured Error {(int)delta.TotalMilliseconds} milliseconds. Frames: {data.FrameCount} Dropped: {dropped}");

        _prevTime = now;
        _currentFrameNumber = data.FrameNumber + data.FrameCount;
        _totalDropped += dropped;
        
        var converted = ToDoubles(ElementType, data.Payload.Span);

        _framesLeft -= dropped;

        for (int i = 0; i < data.FrameCount && _framesLeft > 0; i++)
        {
            var frame = converted.AsSpan(i * ElementCount, ElementCount);
            _statisticsTotal.PushRange(frame.ToArray());
            if (_statistics != null)
            {
                for (int j = 0; j < ElementCount; j++)
                {
                    _statistics[j].Push(frame[j]);
                }
            }

            _framesLeft--;
        }
        

        if(_framesLeft == 0)
        {
            JsonElement jsonElement = FormatJson();

            // Converting JsonElement back to formatted JSON string
            string formattedJsonString =
                JsonSerializer.Serialize(jsonElement, new JsonSerializerOptions { WriteIndented = true });

            _client.LastResponseJson = JsonDocument.Parse(formattedJsonString)?.RootElement;

            switch (_client.PrintMode)
            {
                case PrintMode.Text:
                    PrintStatisticsText();
                    break;
                case PrintMode.Json:
                    WriteLine(formattedJsonString);
                    break;
            }

            return false;
        }

        return true;
    }

    private void WriteLine(string header, object? value = null)
    {
        if (value == null)
        {
            Client.WriteLine(header);
            return;
        }

        Client.WriteLine(header.PadRight(30) + " " + value);
    }

    private void PrintStatisticsText()
    {
        int bytesReceived = ElementSize * ElementCount * _framesReceived;
        int framesAnalyzed = (int)(_statisticsTotal.Count / ElementCount);

        WriteLine("");
        WriteLine($"--- Statistics for Stream {Stream?.Name} ---");
        WriteLine("Max Chunk Arrival Error", (int)_maxTimeDelta.TotalMilliseconds + " milliseconds");   // Max chunk arrival time error
        WriteLine("Clock Drift", (int)_clockDrift.TotalMilliseconds + " milliseconds");             // Time error between first and last chunk
        WriteLine("Received", $"{_chunksReceived:N0} chunks / {_framesReceived:N0} frames / {bytesReceived:N0} bytes");
        WriteLine("Sampled", $"{framesAnalyzed:N0} frames");
        WriteLine("Average Frames in Chunk", _framesReceived / (float)_chunksReceived);
        WriteLine("Average Chunk Size", $"{bytesReceived / (float)_chunksReceived:N0} bytes");
        WriteLine("Dropped Frames Device", $"{_totalDropped:N0} frames");
        WriteLine("Dropped Frames Client", $"{_framesReceived - framesAnalyzed:N0} frames");
        WriteLine("Elements in Frame", ElementCount);
        WriteLine("Element Size", $"{ElementSize} bytes");

        if (_statistics != null)
        {
            var labels = GetNames(Stream);
            for (var i = 0; i < _statistics.Count; i++)
            {
                var stats = _statistics[i];
                string name = labels?.Length == _statistics.Count ? labels[i] : $"Component {i}";

                WriteLine($"{name} Minimum", stats.Minimum);
                WriteLine($"{name} Maximum", stats.Maximum);
                WriteLine($"{name} Mean", stats.Mean);
                WriteLine($"{name} Variance", stats.Variance);
                WriteLine($"{name} Kurtosis", stats.Kurtosis);
                WriteLine($"{name} Standard Deviation", stats.StandardDeviation);
                WriteLine($"{name} Sum", stats.Sum);
            }
        }
        else
        {
            WriteLine("Element Minimum", _statisticsTotal.Minimum);
            WriteLine("Element Maximum", _statisticsTotal.Maximum);
            WriteLine("Element Mean", _statisticsTotal.Mean);
            WriteLine("Element Variance", _statisticsTotal.Variance);
            WriteLine("Element Kurtosis", _statisticsTotal.Kurtosis);
            WriteLine("Element Standard Deviation", _statisticsTotal.StandardDeviation);
            WriteLine("Element Sum", _statisticsTotal.Sum);
        }
    }

    private JsonElement FormatJson()
    {
        int bytesReceived = ElementSize * ElementCount * _framesReceived;
        int framesAnalyzed = (int)(_statisticsTotal.Count / ElementCount);

        var jsonObject = new Dictionary<string, object>
        {
            {"StreamName", Stream?.Name ?? ""},
            {"MaxChunkArrivalError", _maxTimeDelta.TotalMilliseconds},      // Max chunk arrival time error
            {"ClockDrift", _clockDrift.TotalMilliseconds},                  // Time error between first and last chunk
            {"AsbClockDrift", _clockDrift.Duration().TotalMilliseconds},    // Absolute time error between first and last chunk
            {"ReceivedChunks", _chunksReceived},
            {"ReceivedFrames", _framesReceived},
            {"ReceivedBytes", bytesReceived},
            {"SampledFrames", framesAnalyzed},
            {"AverageFramesInChunk", _framesReceived / (float)_chunksReceived},
            {"AverageChunkSize", bytesReceived / (float)_chunksReceived},
            {"DroppedFramesDevice", _totalDropped},
            {"DroppedFramesClient", _framesReceived - framesAnalyzed},
            {"ElementsInFrame", ElementCount},
            {"ElementSize", ElementSize}
        };

        if (_statistics != null)
        {
            var statsList = new List<Dictionary<string, object>>();

            var labels = GetNames(Stream);
            for (var i = 0; i < _statistics.Count; i++)
            {
                var stats = _statistics[i];
                string name = labels?.Length == _statistics.Count ? labels[i] : $"Component {i}";

                var componentStats = new Dictionary<string, object>
                {
                    {"Name", name},
                    {"Minimum", stats.Minimum},
                    {"Maximum", stats.Maximum},
                    {"Mean", stats.Mean},
                    {"Variance", stats.Variance},
                    {"Kurtosis", stats.Kurtosis},
                    {"StandardDeviation", stats.StandardDeviation},
                    {"Sum", stats.Sum}
                };
                statsList.Add(componentStats);
            }
            jsonObject.Add("Statistics", statsList);
        }
        else
        {
            var totalStats = new Dictionary<string, double>
            {
                {"Minimum", _statisticsTotal.Minimum},
                {"Maximum", _statisticsTotal.Maximum},
                {"Mean", _statisticsTotal.Mean},
                {"Variance", _statisticsTotal.Variance},
                {"Kurtosis", _statisticsTotal.Kurtosis},
                {"StandardDeviation", _statisticsTotal.StandardDeviation},
                {"Sum", _statisticsTotal.Sum}
            };
            jsonObject.Add("TotalStatistics", totalStats);
        }

        var options = new JsonSerializerOptions
        {
            NumberHandling = JsonNumberHandling.AllowNamedFloatingPointLiterals
        };
        string jsonString = JsonSerializer.Serialize(jsonObject, options);
        JsonDocument jsonDocument = JsonDocument.Parse(jsonString);
        return jsonDocument.RootElement;
    }

    public static string[]? GetNames(StreamConfig? stream)
    {
        if (stream?.Shape == null || stream.Shape.Count == 0) 
            return null;

        return stream.Shape.Aggregate(
            (IEnumerable<string>)new[] { "" }, 
            (acc, shape) => acc.SelectMany(prefix => shape.Labels, (prefix, label) => $"{prefix}/{label}".Trim('/'))).ToArray();
    }
}