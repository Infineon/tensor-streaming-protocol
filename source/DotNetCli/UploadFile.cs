using Google.Protobuf;
using Protocol;
using NAudio.Wave;

namespace DotNetCli;

internal class UploadFile : StreamHandlerBase
{
    private readonly IFileReader _reader;

    public UploadFile(IClient client, string filePath) : base(client)
    {
        _reader = new WavFileReader(filePath);
    }

    public override void Start(StreamConfig stream)
    {
        base.Start(stream);

        if (Stream != null)
            return;

        if (stream.Shape.Count != _reader.Shape.Length)
            throw new InvalidDataException($"The number of dimensions do not match. Stream have rank {stream.Shape.Count} but the file have rank {_reader.Shape.Length}");

        for (int i = 0; i < stream.Shape.Count; i++)
        {
            if (stream.Shape[i].Size != _reader.Shape[i])
                throw new InvalidDataException($"The size of dimension {i} do not match. Stream have a size of {stream.Shape[i].Size} but the file have {_reader.Shape[i]}");
        }
    }

    public override bool ProcessDataInquire(DataInquire data)
    {
        // Client.WriteLine($"Received DataInquire stream:{data.Stream} frames:{data.FrameCount}");

        var bytes = new List<byte>(data.FrameCount * ElementSize);

        bool isEof = false;
        int frameCount = 0;
        while (frameCount < data.FrameCount)
        {
            var frame = _reader.GetFrameFlat();

            if (frame == null)
            {
                isEof = true;
                break;
            }

            frameCount++;

            bytes.AddRange(NormalizedToBytesSaturating(frame));
        }

        if (bytes.Count > 0)
        {
            var request = new Request
            {
                Data = new DataChunk
                {
                    Device = Client.Config.Device,
                    Stream = data.Stream,
                    FrameCount = frameCount,
                    Payload = ByteString.CopyFrom(bytes.ToArray()),
                }
            };
            Client.SendRequest(request);
        }

        return !isEof;
    }
}


public interface IFileReader
{
    int[] Shape { get; }

    double[]? GetFrameFlat();
}


public class WavFileReader : IFileReader
{
    private WaveFileReader? _reader;

    public int[] Shape { get; }

    public WavFileReader(string filePath)
    {
        _reader = new WaveFileReader(filePath);

        Shape = new int [1];
        Shape[0] = _reader.WaveFormat.Channels;
    }

    public double[]? GetFrameFlat()
    {
        var frame = _reader?.ReadNextSampleFrame();
        if (frame == null)
        {
            _reader?.Dispose();
            _reader = null;
            return null;
        }

        return frame.Select(x => (double)x).ToArray();
    }
}