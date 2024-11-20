using System.Diagnostics.CodeAnalysis;
using System.IO.Ports;
using System.Net.Sockets;
using Google.Protobuf;
using Protocol;

namespace DotNetCli;

public readonly record struct StreamKey(int DeviceId, int StreamId);

public interface IStreamHandler
{
    void Start(StreamConfig stream);

    // Return false to be called again with more data. 
    // If false, a StopRequest message will be sent and
    // the writer will be removed.
    bool ProcessDataChunk(DataChunk data);
}

public class Client
{
    private const int DefaultTcpPort = 12345;
    private const string DefaultTcpHost = "localhost";
    private const string DefaultComPort = "COM5";
    private const int SerialPortBaud = 115200; // 256000 also works for windows

    private const string NotConnectedMessage = 
        "Not connected. Try 'open tcp' to connect to default host and port \n" +
        "or 'open serial' to connect to default COM-port."; 


    // If true, output will be printed as raw JSON
    public bool JsonOutputFormat;

    // Holds the current request.
    public DeviceConfigurationRequest Config = new();

    // If not 0, a watchdog reset message will be sent.
    public TimeSpan WatchDogReset = TimeSpan.Zero;

    // Connection stream, serial, tcp
    // Note! take a lock on this object before accessing it!
    public Stream? Stream;
    public object StreamReadLock = new();
    public object StreamWriteLock = new();

    // Download target streams
    private Dictionary<StreamKey, IStreamHandler> _streamHandler = new();
    private Dictionary<StreamKey, StreamConfig> _streamConfigs = new();

    public void Run()
    {
        // Start receive thread that print response messages
        var receiveThread = new Thread(ReceiveThreadHandler);
        receiveThread.Start();

        // Watchdog thread that sends watchdog reset messages periodically
        var watchdogThread = new Thread(WatchDogThreadHandler);
        watchdogThread.Start();

        Console.WriteLine();
        while (true)
        {
            PrintPrompt();
            string? cmd = Console.ReadLine();
            try
            {
                switch (cmd?.Split(' ', StringSplitOptions.RemoveEmptyEntries))
                {
                    case null or [] or [""]:
                        break;
                    case ["connect" or "open", "tcp"]:
                        ConnectTcpCommand(DefaultTcpHost, DefaultTcpPort.ToString());
                        break;
                    case ["connect" or "open", "tcp", var host, var port]:
                        ConnectTcpCommand(host, port);
                        break;
                    case ["connect" or "open", "serial"]:
                        ConnectSerialCommand(DefaultComPort);
                        break;
                    case ["connect" or "open", "serial", var port]:
                        ConnectSerialCommand(port);
                        break;
                    case ["disconnect" or "close"]:
                        DisconnectCommand();
                        break;
                    case ["list", "all"]:
                        ListCommand("-1");
                        break;
                    case ["list"]:
                        ListCommand(Config.Device.ToString());
                        break;
                    case ["mode"]:
                        ToggleModeCommand();
                        break;
                    case ["select", var device]:
                        SelectCommand(device);
                        break;
                    case ["set", "bool" or "b", var option, var value]:
                        SetBoolCommand(option, value);
                        break;
                    case ["set", "int" or "i", var option, var value]:
                        SetIntCommand(option, value);
                        break;
                    case ["set", "float" or "f", var option, var value]:
                        SetFloatCommand(option, value);
                        break;
                    case ["set", "index" or "x", var option, var value]:
                        SetIndexCommand(option, value);
                        break;
                    case ["update" or "flush"]:
                        UpdateCommand();
                        break;
                    case ["clear"]:
                        ClearCommand();
                        break;
                    case ["cls"]:
                        ClearScreenCommand();
                        break;
                    case ["save", var stream, var fileName, var count]:
                        SaveCsv(stream, fileName, count);
                        break;
                    case ["save", var stream, var fileName]:
                        SaveCsv(stream, fileName, "1");
                        break;
                    case ["display", var stream, var count]:
                        SaveCsv(stream, null, count);
                        break;
                    case ["display", var stream]:
                        SaveCsv(stream, null, "1");
                        break;
                    case ["stop"]:
                        StopCommand(Config.Device.ToString());
                        break;
                    case ["stop", "all"]:
                        StopCommand("-1");
                        break;
                    case ["exit"]:
                        return;
                    case ["help" or "?"]:
                        HelpCommand();
                        break;
                    case ["send", "random", var stream, var size, var frames]:
                        SendRandomDataCommand(Config.Device.ToString(), stream, size, frames);
                        break;
                    case ["send", "random", var stream, var size]:
                        SendRandomDataCommand(Config.Device.ToString(), stream, size, "1");
                        break;
                    default:
                        Console.WriteLine("Invalid syntax. Try command 'help'.");
                        break;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception: {ex.Message}");
            }
        }
    }

    #region Command handlers

    private static void HelpCommand()
    {
        Console.WriteLine("Available commands:");
        Console.WriteLine(" open tcp <addr>? <port>?               Connect over TCP. If addr and port are not given, defaults are used.");
        Console.WriteLine(" open serial <port>?                    Connect over a serial port. Use port names like COM1.");
        Console.WriteLine(" select <device>                        Select the specified device.");
        Console.WriteLine(" list all                               List all devices.");
        Console.WriteLine(" list                                   List the active device.");
        Console.WriteLine(" mode                                   Toggle JSON mode on/off.");
        Console.WriteLine(" set bool <option> true|false           Set a boolean option on the selected device.");
        Console.WriteLine(" set int <option> <value>               Set an integer option on the selected device.");
        Console.WriteLine(" set float <option> <value>             Set a decimal option on the selected device.");
        Console.WriteLine(" set index <option> <value>             Set an index option on the selected device.");
        Console.WriteLine(" update                                 Send updated options for the selected device.");
        Console.WriteLine(" clear                                  Clear any queued updates waiting to be sent.");
        Console.WriteLine(" save <stream> <filename.csv> <frames>? Save stream to CSV file. If frames are not given, defaults to 1.");
        Console.WriteLine(" display <stream> <frames>?             Same as save but writes to screen.");
        Console.WriteLine(" stop                                   Stop all streams on selected device.");
        Console.WriteLine(" stop all                               Stop all streams on all devices.");
        Console.WriteLine(" send random <stream> <frames>?         Send random data to the active device. If frames are not given, defaults to 1.");
        Console.WriteLine(" help                                   Display this help message.");
        Console.WriteLine(" close                                  Disconnect from the current device.");
        Console.WriteLine(" exit                                   Exit the application.");
        Console.WriteLine();
        Console.WriteLine("Use the up and down arrow keys to browse the command history.");
        Console.WriteLine();
    }

    private void SaveCsv(string streamStr, string? fileName, string framesStr = "1")
    {
        if (!int.TryParse(streamStr, out int streamId))
        {
            Console.WriteLine($"Unable to parse <stream> integer argument {streamStr}.");
            return;
        }

        if (!int.TryParse(framesStr, out int framesCount))
        {
            Console.WriteLine($"Unable to parse <frames> integer argument {framesStr}.");
            return;
        }

        SendRequest(new Request { Capabilities = new BoardCapabilitiesRequest { Device = Config.Device}});
        SendRequest(new Request { Start = new StartRequest { Device = Config.Device } });

        _streamHandler.Add(new StreamKey(Config.Device, streamId), new CsvWriter(fileName, framesCount));
    }

    private void ConnectTcpCommand(string host, string port)
    {
        try
        {
            if (!int.TryParse(port, out var portNumber))
                Console.WriteLine($"Unable to parse integer port {port}.");

            // Close existing connection
            CloseStream();

            // Connect over TCP
            var client = new TcpClient(host, portNumber);

            // Open a network streams
            lock (StreamWriteLock)
            lock (StreamReadLock)
            {
                Stream = client.GetStream();
                Console.WriteLine($"Connected to {host} {portNumber}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Failed to connect {host} {port}. {ex.Message}");
        }
    }

    private void ConnectSerialCommand(string port)
    {
        try
        {
            CloseStream();

            lock (StreamWriteLock)
            lock (StreamReadLock)
            {
                SerialPort serial = new SerialPort(port, SerialPortBaud);
                serial.WriteTimeout = 2000;
                serial.Open();
                
                Stream = serial.BaseStream;
                Console.WriteLine($"Connected to {serial.PortName} {serial.DataBits} {serial.Parity} {serial.StopBits} {serial.BaudRate}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Failed to connect to serial {port}. {ex.Message}");
        }
    }

    private void CloseStream()
    {
        try
        {
            Stream?.Dispose();
            Stream = null;
        }
        catch
        {
        }
    }

    private void DisconnectCommand()
    {
        CloseStream();
    }


    private void StopCommand(string deviceStr)
    {
        if (Stream is not { CanWrite: true, CanRead: true })
        {
            Console.WriteLine(NotConnectedMessage);
            return;
        }

        if (!int.TryParse(deviceStr, out var deviceId))
            Console.WriteLine($"Unable to parse integer argument {deviceStr}.");

        lock (StreamWriteLock)
        {
            var request = new Request { Stop = new StopRequest { Device = deviceId } };
            request.WriteDelimitedTo(Stream);
        }

        IEnumerable<StreamKey> remove
            = deviceId != -1 
            ? _streamHandler.Where(x => x.Key.DeviceId == deviceId).Select(x => x.Key) 
            : _streamHandler.Select(x => x.Key);

        foreach (var key in remove.ToArray())
        {
            _streamHandler.Remove(key);
        }
    }

    private void SelectCommand(string deviceStr)
    {
        if (!int.TryParse(deviceStr, out var device))
        {
            Console.WriteLine($"Unable to parse integer argument {deviceStr}.");
            return;
        }

        if (Config.Device != device && Config.Options.Any())
        {
            Console.WriteLine($"There are {Config.Options.Count} pending update(s) on device {Config.Device}.");
            Console.WriteLine($"Flush with the 'update' command, or clear with the 'clear' command first.");
            Console.WriteLine($"Selected device is still {Config.Device}.");
            return;
        }
        Config.Device = device;
        Console.WriteLine($"Device {device} selected.");
    }

    private void SetIndexCommand(string optionStr, string valueStr)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            Console.WriteLine($"Unable to parse <option> integer argument {optionStr}.");
            return;
        }

        if (!int.TryParse(valueStr, out int indexValue))
        {
            Console.WriteLine($"Unable to parse <value> integer argument {valueStr}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.OneofValue = indexValue;
                Console.WriteLine($"Updated previous value. Still {Config.Options.Count} pending.");
                return;
            }
        }

        Config.Options.Add(new OptionValue { OptionId = optionId, OneofValue = indexValue });
        Console.WriteLine($"{Config.Options.Count} update(s) pending with 'update' command.");
    }

    private void SetFloatCommand(string optionStr, string valueStr)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            Console.WriteLine($"Unable to parse <option> integer argument {optionStr}.");
            return;
        }

        if (!float.TryParse(valueStr, System.Globalization.CultureInfo.InvariantCulture, out float floatValue))
        {
            Console.WriteLine($"Unable to parse <value> float argument {valueStr}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.FloatValue = floatValue;
                Console.WriteLine($"Updated previous value. Still {Config.Options.Count} update(s) pending.");
                return;
            }
        }
        Config.Options.Add(new OptionValue { OptionId = optionId, FloatValue = floatValue });
        Console.WriteLine($"{Config.Options.Count} update(s) pending with 'update'.");
    }

    private void SetIntCommand(string optionStr, string valueStr)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            Console.WriteLine($"Unable to parse <option> integer argument {optionStr}.");
            return;
        }

        if (!int.TryParse(valueStr, out int intValue))
        {
            Console.WriteLine($"Unable to parse <value> integer argument {valueStr}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.IntValue = intValue;
                Console.WriteLine($"Updated previous value. Still {Config.Options.Count} update(s) pending.");
                return;
            }
        }

        Config.Options.Add(new OptionValue { OptionId = optionId, IntValue = intValue });
        Console.WriteLine($"{Config.Options.Count} update(s) pending with 'update'.");
    }

    private void SetBoolCommand(string optionStr, string valueArg)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            Console.WriteLine($"Unable to parse <option> integer argument {optionStr}");
            return;
        }

        if (!bool.TryParse(valueArg, out bool boolValue))
        {
            Console.WriteLine($"Unable to parse <value> boolean argument {valueArg}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.BoolValue = boolValue;
                Console.WriteLine($"Updated previous value. Still {Config.Options.Count} update(s) pending.");
                return;
            }
        }
        Config.Options.Add(new OptionValue { OptionId = optionId, BoolValue = boolValue });
        Console.WriteLine($"{Config.Options.Count} update(s) pending with 'update'.");
    }
    
    private void ClearCommand()
    {
        Console.WriteLine($"{Config.Options.Count} updates cleared.");
        Config.Options.Clear();
    }

    private void UpdateCommand()
    {
        if (Stream is not { CanWrite: true, CanRead: true })
        {
            Console.WriteLine(NotConnectedMessage);
            return;
        }

        lock (StreamWriteLock)
        {
            var request = new Request { Config = Config };
            request.WriteDelimitedTo(Stream);
        }
        Config.Options.Clear();
    }

    private void SendRandomDataCommand(string deviceStr, string streamStr, string sizeStr, string framesStr)
    {
        if (!int.TryParse(deviceStr, out int deviceId))
        {
            Console.WriteLine($"Unable to parse <device> integer argument {deviceStr}");
            return;
        }

        if (!int.TryParse(streamStr, out int streamId))
        {
            Console.WriteLine($"Unable to parse <stream> integer argument {streamStr}");
            return;
        }

        if (!int.TryParse(sizeStr, out int size))
        {
            Console.WriteLine($"Unable to parse <size> integer argument {sizeStr}");
            return;
        }

        if (!int.TryParse(framesStr, out int frameCount))
        {
            Console.WriteLine($"Unable to parse <frames> integer argument {framesStr}");
            return;
        }

        if (Stream is not { CanWrite: true, CanRead: true })
        {
            Console.WriteLine(NotConnectedMessage);
            return;
        }

        byte[] buffer = new byte[size];
        Random.Shared.NextBytes(buffer);

        ByteString bytes = ByteString.CopyFrom(buffer);

        lock (StreamWriteLock)
        {
            var request = new Request
            {
                Data = new DataChunk
                {
                    Device = deviceId, 
                    Stream = streamId, 
                    FrameCount = frameCount, 
                    Payload = bytes,
                }
            };
            request.WriteDelimitedTo(Stream);
        }
    }

    private void ListCommand(string device)
    {
        if (!int.TryParse(device, out int deviceId))
        {
            Console.WriteLine($"Unable to parse <device> integer argument {device}.");
            return;
        }

        if (Stream is not { CanWrite: true, CanRead: true })
        {
            Console.WriteLine(NotConnectedMessage);
            return;
        }

        SendRequest(new Request { Capabilities = new BoardCapabilitiesRequest { Device = deviceId } });
    }

    private void ToggleModeCommand()
    {
        JsonOutputFormat = !JsonOutputFormat;
        Console.WriteLine($"JSON responses is now {(JsonOutputFormat ? "ON" : "OFF")}");
    }

    private void ClearScreenCommand()
    {
        Console.Clear();
    }

    #endregion

    [DoesNotReturn]
    private void ReceiveThreadHandler()
    {
        while (true)
        {
            // Wait for a connection
            if (Stream == null)
            {
                Thread.Sleep(100);
                continue;
            }

            try
            {
                Response? response;
                lock (StreamReadLock)
                {
                    response = Response.Parser.ParseDelimitedFrom(Stream);
                }

                switch (response.ResponseTypeCase)
                {
                    case Response.ResponseTypeOneofCase.None:
                    {
                        ClearCurrentConsoleLine();
                        Console.Write("Null response.");
                        break;
                    }
                    case Response.ResponseTypeOneofCase.Capabilities:
                    {
                        ClearCurrentConsoleLine();
                        foreach (var device in response.Capabilities.Board.Devices)
                        {
                            int index = 0;
                            foreach (var stream in device.Streams)
                            {
                                var key = new StreamKey(device.DeviceId, index++);
                                _streamConfigs[key] = stream;

                                if(_streamHandler.TryGetValue(key, out var handler))
                                    handler.Start(stream);
                            }
                        }

                        if (JsonOutputFormat)
                        {
                                JsonFormatter formatter = new JsonFormatter(JsonFormatter.Settings.Default.WithIndentation());
                                Console.Write(formatter.Format(response));
                            }
                        else
                        {
                            Console.Write(response.Capabilities.Format());
                        }

                        if (response.Capabilities.Board.WatchdogTimeout != (int)WatchDogReset.TotalMilliseconds)
                        {
                            WatchDogReset = TimeSpan.FromMilliseconds(response.Capabilities.Board.WatchdogTimeout);
                            Console.WriteLine($"Watchdog updated to {WatchDogReset}");
                        }

                        break;
                    }
                    case Response.ResponseTypeOneofCase.Config:
                    {
                        ClearCurrentConsoleLine();

                        int index = 0;
                        foreach (var stream in response.Config.Streams)
                        {
                            var key = new StreamKey(response.Config.Device, index++);
                            _streamConfigs[key] = stream;

                            if (_streamHandler.TryGetValue(key, out var handler))
                                handler.Start(stream);
                        }
                        
                        if (JsonOutputFormat)
                        {
                            JsonFormatter formatter = new JsonFormatter(JsonFormatter.Settings.Default.WithIndentation());
                            Console.Write(formatter.Format(response));
                        }
                        else
                        {
                            Console.Write(response.Config.Format());
                        }

                        break;
                    }
                    case Response.ResponseTypeOneofCase.Error:
                    {
                        ClearCurrentConsoleLine();
                        if (JsonOutputFormat)
                        {
                            JsonFormatter formatter =
                                new JsonFormatter(JsonFormatter.Settings.Default.WithIndentation());
                            Console.Write(formatter.Format(response));
                        }
                        else
                        {
                            Console.Write(response.Error.Format());
                        }

                        break;
                    }
                    case Response.ResponseTypeOneofCase.Data:
                    {
                        StreamKey key = new StreamKey(response.Data.Device, response.Data.Stream);
                        if (_streamHandler.TryGetValue(key, out var handler))
                        {
                            if (!handler.ProcessDataChunk(response.Data))
                            {
                                _streamHandler.Remove(key);
                                SendRequest(new Request { Stop = new StopRequest { Device = key.DeviceId } });
                            }
                        }

                        continue;
                    }
                    default:
                        throw new ArgumentOutOfRangeException();
                }

                if (Config.Options.Any())
                    Console.WriteLine(
                        $"NOTE! Listing is not updated. There are {Config.Options.Count} update(s) pending 'update' command.");

                PrintPrompt();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception: {ex.Message}");
                CloseStream();
            }
        }
    }


    [DoesNotReturn]
    private void WatchDogThreadHandler()
    {
        while (true)
        {
            // Wait for a connection
            if (Stream == null || WatchDogReset == TimeSpan.Zero)
            {
                Thread.Sleep(100);
                continue;
            }

            try
            {
                // Wait for write access
                if (!Stream.CanWrite)
                {
                    Thread.Sleep(100);
                    continue;
                }

                if(WatchDogReset != TimeSpan.Zero)
                    Thread.Sleep(WatchDogReset);

                SendRequest(new Request { WatchdogReset = new WatchdogResetRequest() });
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception: {ex.Message}");
                CloseStream();
            }
        }
    }

    private void SendRequest(Request request)
    {
        lock (StreamWriteLock)
        {
            request.WriteDelimitedTo(Stream);
        }
    }

    private static void ClearCurrentConsoleLine()
    {
        int currentLineCursor = Console.CursorTop;
        Console.SetCursorPosition(0, Console.CursorTop);
        Console.Write(new string(' ', Console.WindowWidth));
        Console.SetCursorPosition(0, currentLineCursor);
    }

    private void PrintPrompt()
    {
        if (Console.CursorLeft != 0)
            Console.WriteLine();
        Console.Write($"(device {Config.Device})$ ");
    }
}