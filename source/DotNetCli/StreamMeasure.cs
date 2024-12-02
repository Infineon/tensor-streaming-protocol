using System.Text.Json;
using Protocol;

namespace DotNetCli;

internal class StreamMeasure : StreamHandlerBase
{
    private readonly RunningStatistics _statisticsTotal;
    private List<RunningStatistics>? _statistics;
    private DateTime? _prevTime;
    private int _currentFrameNumber;
    private int _framesReceived;
    private int _framesLeft;
    private int _totalDropped;
    private int _chunksReceived;
    private TimeSpan _maxTimeDelta;
    private IClient _client;

    public StreamMeasure(IClient client, int count) : base(client)
    {
        _framesLeft = count;
        _client = client;
        _statisticsTotal = new();
        _maxTimeDelta = TimeSpan.Zero;
    }

    public override void Start(StreamConfig stream)
    {
        base.Start(stream);

        var estimated = TimeSpan.FromSeconds(_framesLeft / stream.Frequency);

        if (ElementCount < 9)
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
        if (Stream == null)
            return false;

        var now = DateTime.UtcNow;
        _prevTime ??= now;

        _chunksReceived++;
        _framesReceived += data.FrameCount;

        int expectedTotal = data.FrameCount * ElementSize * ElementCount;
        if (data.Payload.Span.Length != expectedTotal)
        {
            Client.ErrorMessage(
                $"Unexpected payload size of {data.Payload.Span.Length} bytes. Expected {expectedTotal} bytes.");
            return false;
        }

        var dropped = data.FrameNumber - _currentFrameNumber;

        var delta = now - _prevTime.Value;
        _prevTime = now;
        
        if (data.FrameNumber != 0)
            delta -= TimeSpan.FromSeconds(1 / (double)Stream.Frequency);
        
        // WriteLine($"Chunk {_chunksReceived}: Measured Error {(int)delta.TotalMilliseconds} milliseconds. Frames: {data.FrameCount} Dropped: {dropped}");

        if (delta.Duration() > _maxTimeDelta)
            _maxTimeDelta = delta.Duration();

        _currentFrameNumber = data.FrameNumber + data.FrameCount;
        _totalDropped += dropped;
        if (_framesLeft > 0)
        {
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

            return true;
        }
        else
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
        WriteLine("Measured Time Error", (int)_maxTimeDelta.TotalMilliseconds + " milliseconds");
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
            for (var i = 0; i < _statistics.Count; i++)
            {
                var stats = _statistics[i];
                string name;
                if (Stream?.Shape.Count == 1 && Stream.Shape[0].Labels.Count == _statistics.Count)
                    name = Stream.Shape[0].Labels[i];
                else
                    name = $"Component {i}";

                WriteLine($"{name} Minimum", stats.Minimum);
                WriteLine($"{name} Maximum", stats.Maximum);
                WriteLine($"{name} Mean", stats.Mean);
                WriteLine($"{name} Variance", stats.Variance);
                WriteLine($"{name} Kurtosis", stats.Kurtosis);
                WriteLine($"{name} Standard Deviation", stats.StandardDeviation);
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
        }
    }

    private JsonElement FormatJson()
    {
        int bytesReceived = ElementSize * ElementCount * _framesReceived;
        int framesAnalyzed = (int)(_statisticsTotal.Count / ElementCount);

        var jsonObject = new Dictionary<string, object>
        {
            {"StreamName", Stream?.Name},
            {"MeasuredTimeError", _maxTimeDelta.TotalMilliseconds},
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
            for (var i = 0; i < _statistics.Count; i++)
            {
                var stats = _statistics[i];
                string name;
                if (Stream?.Shape.Count == 1 && Stream.Shape[0].Labels.Count == _statistics.Count)
                    name = Stream.Shape[0].Labels[i];
                else
                    name = $"Component {i}";

                var componentStats = new Dictionary<string, object>
                {
                    {"Name", name},
                    {"Minimum", stats.Minimum},
                    {"Maximum", stats.Maximum},
                    {"Mean", stats.Mean},
                    {"Variance", stats.Variance},
                    {"Kurtosis", stats.Kurtosis},
                    {"StandardDeviation", stats.StandardDeviation}
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
                {"StandardDeviation", _statisticsTotal.StandardDeviation}
            };
            jsonObject.Add("TotalStatistics", totalStats);
        }

        string jsonString = JsonSerializer.Serialize(jsonObject);
        JsonDocument jsonDocument = JsonDocument.Parse(jsonString);
        return jsonDocument.RootElement;
    }
}