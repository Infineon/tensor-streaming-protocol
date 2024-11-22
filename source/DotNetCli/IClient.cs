using Protocol;

namespace DotNetCli;

public interface IClient
{
    DeviceConfigurationRequest Config { get; }

    void SendRequest(Request request);

    void AddStreamHandler(int device, int stream, IStreamHandler handler);

    public void CheckConnected();

    public void ErrorMessage(string message);

    public void WriteLine(string message);
}