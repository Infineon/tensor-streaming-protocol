using Google.Protobuf;
using Microsoft.VisualBasic;
using Protocol;

namespace DotNetCli;

/// <summary>
/// Additional commands
/// </summary>
internal static class CommandsEx
{
    public static void Stats(IClient client, string streamStr, string framesStr)
    {
        if (!int.TryParse(streamStr, out int streamId))
        {
            client.ErrorMessage($"Unable to parse <stream> integer argument {streamStr}.");
            return;
        }

        if (!int.TryParse(framesStr, out int frameCount))
        {
            client.ErrorMessage($"Unable to parse <frames> integer argument {framesStr}.");
            return;
        }

        if (frameCount <= 0)
        {
            client.ErrorMessage("<frames> must be larger or equal to 1");
            return;
        }

        client.CheckConnected();

        // The Tag=-1 will prevent the response to be w
        client.SendRequest(new Request { Capabilities = new BoardCapabilitiesRequest { Device = client.Config.Device, Tag = -1} });

        if (!client.Interactive)
            client.Flush();

        client.AddStreamHandler(client.Config.Device, streamId, new StreamMeasure(client, frameCount));

        if (!client.MultiStreamTransaction)
        {
            client.SendRequest(new Request { Start = new StartRequest { Device = client.Config.Device } });

            if (!client.Interactive)
                client.Flush();
        }
    }

    public static void SendFileCommand(IClient client, string streamStr, string filePath)
    {
        if (!int.TryParse(streamStr, out int streamId))
        {
            client.ErrorMessage($"Unable to parse <stream> integer argument {streamStr}.");
            return;
        }

        filePath = Path.GetFullPath(filePath);

        if (!File.Exists(filePath))
        {
            client.ErrorMessage($"File not found. {filePath}");
            return;
        }

        client.CheckConnected();

        client.AddStreamHandler(client.Config.Device, streamId, new UploadFile(client, filePath));

        client.SendRequest(new Request { Capabilities = new BoardCapabilitiesRequest { Device = client.Config.Device, Tag = -1 } });

        client.Flush();

        client.WriteLine($"Sending file {filePath}");

    }

    public static void SaveCsv(IClient client, string streamStr, string? fileName, string framesStr)
    {
        if (!int.TryParse(streamStr, out int streamId))
        {
            client.ErrorMessage($"Unable to parse <stream> integer argument {streamStr}.");
            return;
        }

        if (!int.TryParse(framesStr, out int frameCount))
        {
            client.ErrorMessage($"Unable to parse <frames> integer argument {framesStr}.");
            return;
        }

        if (frameCount <= 0)
        {
            client.ErrorMessage("<frames> must be larger or equal to 1");
            return;
        }

        client.CheckConnected();

        client.SendRequest(new Request { Capabilities = new BoardCapabilitiesRequest { Device = client.Config.Device, Tag = -1 } });

        // Need to wait for the response here
        client.Flush();

        client.AddStreamHandler(client.Config.Device, streamId, new CsvWriter(client, frameCount, fileName));

        if (!client.MultiStreamTransaction)
        {
            client.SendRequest(new Request { Start = new StartRequest { Device = client.Config.Device } });

            if (!client.Interactive)
                client.Flush();
        }
    }

    public static void SendRandomDataCommand(IClient client, string deviceStr, string streamStr, string sizeStr, string framesStr)
    {
        if (!int.TryParse(deviceStr, out int deviceId))
        {
            client.ErrorMessage($"Unable to parse <device> integer argument {deviceStr}");
            return;
        }

        if (!int.TryParse(streamStr, out int streamId))
        {
            client.ErrorMessage($"Unable to parse <stream> integer argument {streamStr}");
            return;
        }

        if (!int.TryParse(sizeStr, out int size))
        {
            client.ErrorMessage($"Unable to parse <size> integer argument {sizeStr}");
            return;
        }

        if (!int.TryParse(framesStr, out int frameCount))
        {
            client.ErrorMessage($"Unable to parse <frames> integer argument {framesStr}");
            return;
        }

        if (frameCount <= 0)
        {
            client.ErrorMessage("<frames> must be larger or equal to 1");
            return;
        }

        client.CheckConnected();

        byte[] buffer = new byte[size];
        Random.Shared.NextBytes(buffer);

        var request = new Request
        {
            Data = new DataChunk
            {
                Device = deviceId,
                Stream = streamId,
                FrameCount = frameCount,
                Payload = ByteString.CopyFrom(buffer),
            }
        };
        client.SendRequest(request);

    }

}