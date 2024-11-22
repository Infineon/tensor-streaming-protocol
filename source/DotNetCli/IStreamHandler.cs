using Protocol;

namespace DotNetCli;

public interface IStreamHandler
{
    void Start(StreamConfig stream);

    // Return false to be called again with more data. 
    // If false, a StopRequest message will be sent and
    // the writer will be removed.
    bool ProcessDataChunk(DataChunk data);
}

public readonly record struct StreamKey(int DeviceId, int StreamId);
