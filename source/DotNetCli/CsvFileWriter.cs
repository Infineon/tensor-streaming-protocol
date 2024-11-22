using System.Globalization;
using System.Text;
using Protocol;

namespace DotNetCli;

public class CsvWriter : StreamHandlerBase
{
    private int _framesLeft;
    private readonly string? _filePath;
    private TextWriter? _writer;

    public CsvWriter(IClient client, int frameCount, string? targetPath = null)
        :base(client)
    {
        if (String.IsNullOrWhiteSpace(_filePath))
            _filePath = null;

        _filePath = targetPath;
        _framesLeft = frameCount;
    }

    public override void Start(StreamConfig stream)
    {
        base.Start(stream);

        var estimated = TimeSpan.FromSeconds(_framesLeft / stream.Frequency);

        Client.WriteLine(
            $"Reading {_framesLeft} frames from {stream.Name} " +
            $"with shape [{string.Join(",", stream.Shape.Select(x => x.Size))}] at {stream.Frequency} Hz. " +
            $"Estimated sample time {estimated}. Please wait...");

        if (_filePath != null) 
        {
            Client.WriteLine($"Creates CSV file {_filePath} with {ElementCount} columns.");
            var fileStream = new FileStream(_filePath, FileMode.OpenOrCreate);
            fileStream.SetLength(0);
            _writer = new StreamWriter(fileStream, Encoding.UTF8);
        }
    }

    public override bool ProcessDataChunk(DataChunk data)
    {
        if (_framesLeft > 0)
        {
            int expectedTotal = data.FrameCount * ElementSize * ElementCount;
            if (data.Payload.Span.Length != expectedTotal)
            {
                Client.ErrorMessage($"Unexpected payload size of {data.Payload.Span.Length} bytes. Expected {expectedTotal} bytes.");
                Close();
                return false;
            }

            var converted = ToDoubles(ElementType, data.Payload.Span);
            for (int i = 0; i < data.FrameCount && _framesLeft > 0; i++)
            {
                WriteLine(converted.AsSpan(i * ElementCount, ElementCount));
                _framesLeft--;
            }
        }

        if (_framesLeft != 0) 
            return true;
        
        Close();
        return false;
    }

    private void Close()
    {
        if (_writer != null)
        {
            _writer.Flush();
            if (_writer != Console.Out)
            {
                _writer.Close();
                _writer.Dispose();
            }
            _writer = null;
        }
    }

    private void WriteLine(Span<double> frame)
    {
        var line = new StringBuilder();
        for (var index = 0; index < frame.Length; index++)
        {
            var value = frame[index];
            line.Append(value.ToString(CultureInfo.InvariantCulture));
            if(index != frame.Length - 1)
                line.Append(", ");
        }

        if (_writer == null)
            Client.WriteLine(line.ToString());
        else
            _writer.WriteLine(line);
    }
}