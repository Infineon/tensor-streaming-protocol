using Protocol;
using System.Text.Json;

namespace DotNetCli;

public enum PrintMode
{
    Text,
    Json,
    Silent
}

public interface IClient
{
    DeviceConfigurationRequest Config { get; }

    JsonElement? LastResponseJson { get; set; }

    PrintMode PrintMode { get; }

    public bool Interactive { get; }

    void SendRequest(Request request);

    void AddStreamHandler(int device, int stream, IStreamHandler handler);

    public void CheckConnected();

    public void ErrorMessage(string message);

    public void WriteLine(string message);

    public void Flush();
}