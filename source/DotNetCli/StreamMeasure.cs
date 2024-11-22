using Protocol;

namespace DotNetCli;

internal class StreamMeasure(IClient client, int count) : StreamHandlerBase(client)
{
    private readonly RunningStatistics _statisticsTotal = new();
    private List<RunningStatistics>? _statistics;
    private DateTime? _first;
    private int _currentFrameNumber;
    private int _framesReceived;
    private int _framesLeft = count;
    private int _totalDropped;
    private int _chunksReceived;
    private TimeSpan _maxTimeDelta = TimeSpan.Zero;

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
        _first ??= now;

        _chunksReceived++;
        _framesReceived += data.FrameCount;

        int expectedTotal = data.FrameCount * ElementSize * ElementCount;
        if (data.Payload.Span.Length != expectedTotal)
        {
            Client.ErrorMessage($"Unexpected payload size of {data.Payload.Span.Length} bytes. Expected {expectedTotal} bytes.");
            return false;
        }

        var dropped = data.FrameNumber - _currentFrameNumber;

        var measured = now - _first.Value;
        var expected = TimeSpan.FromSeconds(data.FrameNumber / Stream.Frequency);
        var delta = expected - measured;
        WriteLine($"Chunk {_chunksReceived}: Measured Error {(int)delta.TotalMilliseconds} milliseconds. Frames: {data.FrameCount} Dropped: {dropped}");

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
            PrintStatistics();
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

        Client.WriteLine(header.PadRight(25) + " " + value);
    }

    private void PrintStatistics()
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
        WriteLine("Dropped Device", $"{_totalDropped:N0} frames");
        WriteLine("Dropped Client", $"{_framesReceived - framesAnalyzed:N0} frames");
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
}