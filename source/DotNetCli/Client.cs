using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.IO.Ports;
using System.Net.Sockets;
using Google.Protobuf;
using Protocol;

namespace DotNetCli;

public class Client : IClient
{
    private const int DefaultTcpPort = 12345;
    private const string DefaultTcpHost = "localhost";
    private const string DefaultComPort = "COM5";
    private const int SerialPortBaud = 115200; // 256000 also works for windows

    // False if -i or --non-interactive startup argument was passed, else true.
    // This will hide the prompt and only print outputs.
    // On any error the application will exit with -1.
    // Useful when used in scripts. 
    private bool _interactive;

    // If true, output will be printed as raw JSON
    private bool _jsonOutputFormat;

    // If not 0, a watchdog reset message will be sent.
    private TimeSpan _watchDogReset = TimeSpan.Zero;

    // When last package was received
    private DateTime _lastTimestamp;

    // Connection stream, serial, tcp
    // Note! take a lock on this object before accessing it!
    private Stream? _stream;
    private readonly object _streamReadLock = new();
    private readonly object _streamWriteLock = new();

    // Download target streams
    private readonly Dictionary<StreamKey, IStreamHandler> _streamHandler = new();

    // Holds the current request.
    public DeviceConfigurationRequest Config { get; private set; } = new();

    public int Run(bool interactive = true)
    {
        _interactive = interactive;

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

            if(cmd == null || cmd.StartsWith("#"))
                continue;

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
                    case ["list" or "ls", "all"]:
                        ListCommand("-1");
                        break;
                    case ["list" or "ls"]:
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
                    case ["update"]:
                        UpdateCommand();
                        break;
                    case ["clear"]:
                        ClearCommand();
                        break;
                    case ["cls"]:
                        ClearScreenCommand();
                        break;
                    case ["save", var stream, var fileName, var count]:
                        CommandsEx.SaveCsv(this, stream, fileName, count);
                        break;
                    case ["save", var stream, var fileName]:
                        CommandsEx.SaveCsv(this, stream, fileName, "1");
                        break;
                    case ["display", var stream, var count]:
                        CommandsEx.SaveCsv(this, stream, null, count);
                        break;
                    case ["display", var stream]:
                        CommandsEx.SaveCsv(this, stream, null, "1");
                        break;
                    case ["stats", var stream, var count]:
                        CommandsEx.Stats(this, stream, count);
                        break;
                    case ["stats", var stream]:
                        CommandsEx.Stats(this, stream, "1");
                        break;
                    case ["stop"]:
                        StopCommand(Config.Device.ToString());
                        break;
                    case ["stop", "all"]:
                        StopCommand("-1");
                        break;
                    case ["exit"]:
                        Environment.Exit(0);
                        return 0;
                    case ["help" or "?"]:
                        HelpCommand();
                        break;
                    case ["flush"]:
                        FlushCommand();
                        break;
                    case ["random", var stream, var size, var frames]:
                        CommandsEx.SendRandomDataCommand(this, Config.Device.ToString(), stream, size, frames);
                        break;
                    case ["random", var stream, var size]:
                        CommandsEx.SendRandomDataCommand(this, Config.Device.ToString(), stream, size, "1");
                        break;
                    default:
                        ErrorMessage("Invalid syntax. Try command 'help'.");
                        break;
                }
            }
            catch (Exception ex)
            {
                ErrorMessage($"Exception: {ex.Message}");
            }
        }
    }

    #region Basse Command handlers

    private void HelpCommand()
    {
        WriteLine("Base Commands:");
        WriteLine(" open tcp <addr>? <port>?               Connect over TCP. Defaults are used if addr and port are not given.");
        WriteLine(" open serial <port>?                    Connect over a serial port. Use port names like COM1.");
        WriteLine(" select <device>                        Select the specified device for subsequent commands.");
        WriteLine(" list all                               List all available devices.");
        WriteLine(" list                                   List the currently active device.");
        WriteLine(" mode                                   Toggle JSON mode on or off for the application.");
        WriteLine(" set bool <option> true|false           Set a boolean option on the selected device.");
        WriteLine(" set int <option> <value>               Set an integer option on the selected device.");
        WriteLine(" set float <option> <value>             Set a decimal (floating-point) option on the selected device.");
        WriteLine(" set index <option> <value>             Set an index option on the selected device.");
        WriteLine(" update                                 Send the updated options to the selected device.");
        WriteLine(" clear                                  Clear any queued updates waiting to be sent to the device.");
        WriteLine(" stop                                   Stop all data streams on the selected device.");
        WriteLine(" stop all                               Stop all data streams on all connected devices.");
        WriteLine(" help                                   Display this help message.");
        WriteLine(" close                                  Close the connection to the board.");
        WriteLine(" flush                                  Wait for 1 second idle time. Useful for command scripts execution.");
        WriteLine(" exit                                   Exit the application.");
        WriteLine("");
        WriteLine("Stream Commands:");
        WriteLine(" save <stream> <filename.csv> <frames>? Save a stream to a CSV file. Defaults to 1 frame if not specified.");
        WriteLine(" display <stream> <frames>?             Display the stream output to the screen. Defaults to 1 frame if not specified.");
        WriteLine(" stats <stream> <frames>?               Fetch and print statistics for the given number of frames.");
        WriteLine(" random <stream> <frames>?              Send random data to the active device for the specified number of frames.");
        WriteLine("");
        WriteLine("Use the up and down arrow keys to browse the command history.");
        WriteLine("");
    }


    private void ConnectTcpCommand(string host, string port)
    {
        try
        {
            if (!int.TryParse(port, out var portNumber))
                ErrorMessage($"Unable to parse integer port {port}.");

            // Close existing connection
            Close();

            // Connect over TCP
            var client = new TcpClient(host, portNumber);

            // Open a network streams
            lock (_streamWriteLock)
            lock (_streamReadLock)
            {
                _stream = client.GetStream();
                WriteLine($"Connected to {host} {portNumber}");
            }
        }
        catch (Exception ex)
        {
            ErrorMessage($"Failed to connect {host} {port}. {ex.Message}");
        }
    }

    private void ConnectSerialCommand(string port)
    {
        try
        {
            Close();

            lock (_streamWriteLock)
            lock (_streamReadLock)
            {
                SerialPort serial = new SerialPort(port, SerialPortBaud);
                serial.WriteTimeout = 2000;
                serial.Open();
                
                _stream = serial.BaseStream;
                WriteLine($"Connected to {serial.PortName} {serial.DataBits} {serial.Parity} {serial.StopBits} {serial.BaudRate}");
            }
        }
        catch (Exception ex)
        {
            ErrorMessage($"Failed to connect to serial {port}. {ex.Message}");
        }
    }

    private void DisconnectCommand()
    {
        Close();
    }

    private void StopCommand(string deviceStr)
    {
        if (!int.TryParse(deviceStr, out var deviceId))
            ErrorMessage($"Unable to parse integer argument {deviceStr}.");

        CheckConnected();

        SendRequest(new Request { Stop = new StopRequest { Device = deviceId } });

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
            ErrorMessage($"Unable to parse integer argument {deviceStr}.");
            return;
        }

        if (Config.Device != device && Config.Options.Any())
        {
            WriteLine($"There are {Config.Options.Count} pending update(s) on device {Config.Device}.");
            WriteLine($"Flush with the 'update' command, or clear with the 'clear' command first.");
            WriteLine($"Selected device is still {Config.Device}.");
            return;
        }
        Config.Device = device;
        WriteLine($"Device {device} selected.");
    }

    private void SetIndexCommand(string optionStr, string valueStr)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            ErrorMessage($"Unable to parse <option> integer argument {optionStr}.");
            return;
        }

        if (!int.TryParse(valueStr, out int indexValue))
        {
            ErrorMessage($"Unable to parse <value> integer argument {valueStr}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.OneofValue = indexValue;
                if (_interactive)
                    WriteLine($"Updated previous value. Still {Config.Options.Count} pending.");
                return;
            }
        }

        Config.Options.Add(new OptionValue { OptionId = optionId, OneofValue = indexValue });
        if (_interactive)
            WriteLine($"{Config.Options.Count} update(s) pending with 'update' command.");
    }

    private void SetFloatCommand(string optionStr, string valueStr)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            ErrorMessage($"Unable to parse <option> integer argument {optionStr}.");
            return;
        }

        if (!float.TryParse(valueStr, System.Globalization.CultureInfo.InvariantCulture, out float floatValue))
        {
            ErrorMessage($"Unable to parse <value> float argument {valueStr}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.FloatValue = floatValue;
                if (_interactive)
                    WriteLine($"Updated previous value. Still {Config.Options.Count} update(s) pending.");
                return;
            }
        }
        Config.Options.Add(new OptionValue { OptionId = optionId, FloatValue = floatValue });
        if (_interactive)
            WriteLine($"{Config.Options.Count} update(s) pending with 'update'.");
    }

    private void SetIntCommand(string optionStr, string valueStr)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            ErrorMessage($"Unable to parse <option> integer argument {optionStr}.");
            return;
        }

        if (!int.TryParse(valueStr, out int intValue))
        {
            ErrorMessage($"Unable to parse <value> integer argument {valueStr}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.IntValue = intValue;
                if (_interactive)
                    WriteLine($"Updated previous value. Still {Config.Options.Count} update(s) pending.");
                return;
            }
        }

        Config.Options.Add(new OptionValue { OptionId = optionId, IntValue = intValue });
        if (_interactive)
            WriteLine($"{Config.Options.Count} update(s) pending with 'update'.");
    }

    private void SetBoolCommand(string optionStr, string valueArg)
    {
        if (!int.TryParse(optionStr, out int optionId))
        {
            ErrorMessage($"Unable to parse <option> integer argument {optionStr}");
            return;
        }

        if (!bool.TryParse(valueArg, out bool boolValue))
        {
            ErrorMessage($"Unable to parse <value> boolean argument {valueArg}.");
            return;
        }

        foreach (var option in Config.Options)
        {
            if (option.OptionId == optionId)
            {
                option.BoolValue = boolValue;
                if (_interactive)
                    WriteLine($"Updated previous value. Still {Config.Options.Count} update(s) pending.");
                return;
            }
        }
        Config.Options.Add(new OptionValue { OptionId = optionId, BoolValue = boolValue });
        if (_interactive)
            WriteLine($"{Config.Options.Count} update(s) pending with 'update'.");
    }
    
    private void ClearCommand()
    {
        WriteLine($"{Config.Options.Count} updates cleared.");
        Config.Options.Clear();
    }

    private void UpdateCommand()
    {
        CheckConnected();
        SendRequest(new Request { Config = Config });
        Config.Options.Clear();
    }

    private void ListCommand(string device)
    {
        CheckConnected();

        if (!int.TryParse(device, out int deviceId))
        {
            ErrorMessage($"Unable to parse <device> integer argument {device}.");
            return;
        }

        SendRequest(new Request { Capabilities = new BoardCapabilitiesRequest { Device = deviceId } });
    }

    private void FlushCommand()
    {
        _lastTimestamp = DateTime.UtcNow + TimeSpan.FromSeconds(1);
        while (DateTime.UtcNow - _lastTimestamp < TimeSpan.FromSeconds(1))
        {
            Thread.Sleep(10);
        }
    }

    private void ToggleModeCommand()
    {
        _jsonOutputFormat = !_jsonOutputFormat;
        if(_interactive)
            WriteLine($"JSON responses is now {(_jsonOutputFormat ? "ON" : "OFF")}");
    }

    private void ClearScreenCommand()
    {
        Console.Clear();
    }

    #endregion

    #region Public Methods (IClient)

    public void AddStreamHandler(int device, int stream, IStreamHandler handler)
    {
        _streamHandler[new StreamKey(device, stream)] = handler;
    }

    public void CheckConnected()
    {
        if (_stream is not { CanWrite: true, CanRead: true })
        {
            throw new Exception("Not connected. Try 'open tcp' to connect to default host and port\n" +
                                "or 'open serial' to connect to default COM-port.");
        }
    }

    public void ErrorMessage(string message)
    {
        ClearCurrentConsoleLine();
        Console.Error.WriteLine(message);

        if (!_interactive)
            Environment.Exit(-1);
    }

    public void WriteLine(string text)
    {
        ClearCurrentConsoleLine();
        Console.WriteLine(text);
    }

    public void SendRequest(Request request)
    {
        lock (_streamWriteLock)
        {
            request.WriteDelimitedTo(_stream);
        }
    }

    #endregion

    #region Private helpers

    private void Close()
    {
        _streamHandler.Clear();

        try
        {
            _stream?.Close();
            _stream?.Dispose();
        }
        catch
        {
            // ignored
        }
        finally
        {
            _stream = null;
        }
    }

    [DoesNotReturn]
    private void ReceiveThreadHandler()
    {
        while (true)
        {
            // Wait for a connection
            if (_stream == null || !_stream.CanRead)
            {
                Thread.Sleep(100);
                continue;
            }

            try
            {
                Response? response;
                lock (_streamReadLock)
                {
                    response = Response.Parser.ParseDelimitedFrom(_stream);
                }

                _lastTimestamp = DateTime.UtcNow;

                switch (response.ResponseTypeCase)
                {
                    case Response.ResponseTypeOneofCase.None:
                    {
                        ErrorMessage("Null response.");
                        break;
                    }
                    case Response.ResponseTypeOneofCase.Capabilities:
                    {
                        foreach (var device in response.Capabilities.Board.Devices)
                        {
                            int index = 0;
                            foreach (var stream in device.Streams)
                            {
                                var key = new StreamKey(device.DeviceId, index++);

                                if(_streamHandler.TryGetValue(key, out var handler))
                                    handler.Start(stream);
                            }
                        }

                        if (response.Capabilities.Tag != -1)
                        {
                            if (_jsonOutputFormat)
                            {
                                JsonFormatter formatter = new JsonFormatter(JsonFormatter.Settings.Default.WithIndentation());
                                WriteLine(formatter.Format(response));
                            }
                            else
                            {
                                WriteLine(response.Capabilities.Format());
                            }
                        }

                        if (response.Capabilities.Board.WatchdogTimeout != (int)_watchDogReset.TotalMilliseconds)
                        {
                            _watchDogReset = TimeSpan.FromMilliseconds(response.Capabilities.Board.WatchdogTimeout);
                            if(_interactive)
                                WriteLine($"Watchdog updated to {_watchDogReset}");
                        }

                        break;
                    }
                    case Response.ResponseTypeOneofCase.Config:
                    {
                        int index = 0;
                        foreach (var stream in response.Config.Streams)
                        {
                            var key = new StreamKey(response.Config.Device, index++);

                            if (_streamHandler.TryGetValue(key, out var handler))
                                handler.Start(stream);
                        }

                        if (response.Config.Tag != -1)
                        {
                            if (_jsonOutputFormat)
                            {
                                JsonFormatter formatter = new JsonFormatter(JsonFormatter.Settings.Default.WithIndentation());
                                WriteLine(formatter.Format(response));
                            }
                            else
                            {
                                WriteLine(response.Config.Format());
                            }
                        }

                        break;
                    }
                    case Response.ResponseTypeOneofCase.Error:
                    {
                        if (_jsonOutputFormat)
                        {
                            JsonFormatter formatter =
                                new JsonFormatter(JsonFormatter.Settings.Default.WithIndentation());
                            WriteLine(formatter.Format(response));
                        }
                        else
                        {
                            WriteLine(response.Error.Format());
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

                if (_interactive && Config.Options.Any())
                    WriteLine($"NOTE! Listing is not updated. There are {Config.Options.Count} update(s) pending 'update' command.");

                PrintPrompt();
            }
            catch (Exception ex)
            {
                if(_stream != null)
                    ErrorMessage($"Exception: {ex.Message}");
            }
        }
    }

    [DoesNotReturn]
    [DebuggerNonUserCode]
    private void WatchDogThreadHandler()
    {
        while (true)
        {
            // Wait for a connection
            if (_stream == null || _watchDogReset == TimeSpan.Zero)
            {
                Thread.Sleep(100);
                continue;
            }

            try
            {
                // Wait for write access
                if (!_stream.CanWrite)
                {
                    Thread.Sleep(100);
                    continue;
                }

                if(_watchDogReset != TimeSpan.Zero)
                    Thread.Sleep(_watchDogReset);

                SendRequest(new Request { WatchdogReset = new WatchdogResetRequest() });
            }
            catch (Exception ex)
            {
                Close();
            }
        }
    }

    private void ClearCurrentConsoleLine()
    {
        if (!_interactive)
            return;

        int currentLineCursor = Console.CursorTop;
        Console.SetCursorPosition(0, Console.CursorTop);
        Console.Write(new string(' ', Console.WindowWidth));
        Console.SetCursorPosition(0, currentLineCursor);
    }

    private void PrintPrompt()
    {
        if(!_interactive)
            return;

        if (Console.CursorLeft != 0)
            Console.WriteLine();
        if(_stream == null)
            Console.Write($"(disconnected)$ ");
        else
            Console.Write($"(device {Config.Device})$ ");
    }

    #endregion
}