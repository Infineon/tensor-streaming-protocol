using System.Globalization;

namespace DotNetCli;

public static class Program
{
    public static int Main(string[] args)
    {
        var culture = (CultureInfo)CultureInfo.InvariantCulture.Clone();
        culture.NumberFormat.NumberGroupSeparator = " ";
        culture.NumberFormat.NumberDecimalSeparator = ".";
        CultureInfo.DefaultThreadCurrentCulture = culture;
        CultureInfo.DefaultThreadCurrentUICulture = culture;

        var client = new Client();

        string? testFile = null;

        for (var index = 0; index < args.Length; index++)
        {
            var arg = args[index];
            switch (arg)
            {
                case "--help" or "-h":
                {
                    PrintUsage();
                    return 0;
                }
                case "--test" or "-t":
                {
                    if (arg.Length - 1 <= index)
                    {
                        Console.WriteLine($"Error: Missing argument for option --test/-t");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }

                    testFile = Path.GetFullPath(args[index + 1]);

                    if (!File.Exists(testFile))
                    {
                        Console.WriteLine($"Error: File not found {testFile}");
                        return -1;
                    }

                    Environment.CurrentDirectory = Path.GetDirectoryName(testFile) ?? ".";

                    index++;
                    break;
                }
                case "--serial-port" or "-sp":
                {
                    if (arg.Length - 1 <= index)
                    {
                        Console.WriteLine($"Error: Missing argument for option --serial-port/-sp");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }

                    client.DefaultComPort = args[index + 1].Trim();
                    index++;
                    break;
                }
                case "--serial-baud" or "-sb":
                {
                    if (arg.Length - 1 <= index)
                    {
                        Console.WriteLine($"Error: Missing baud argument for option --serial-baud/-sb");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }
                    if (!int.TryParse(args[index + 1], out var baud))
                    {
                        Console.WriteLine($"Error: Failed to parse baud argument for option --serial-baud/-sb");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }
                    client.SerialPortBaud = baud;
                    index++;
                    break;
                }
                case "--tcp-host" or "-th":
                {
                    if (arg.Length - 1 <= index)
                    {
                        Console.WriteLine($"Error: Missing host argument for option --tcp-host/-th");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }

                    client.DefaultTcpHost = args[index + 1].Trim();
                    index++;
                    break;
                }
                case "--tcp-port" or "-tp":
                {
                    if (arg.Length - 1 <= index)
                    {
                        Console.WriteLine($"Error: Missing port argument for option --tcp-port/-tp");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }
                    if (!int.TryParse(args[index + 1], out var port))
                    {
                        Console.WriteLine($"Error: Failed to parse port argument for option --tcp-port/-tp");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }
                    client.DefaultTcpPort = port;
                    index++;
                    break;
                }
                default:
                {
                    Console.WriteLine($"Error: Unknown argument {arg}");
                    Console.WriteLine();
                    PrintUsage();
                    return -1;
                }
            }
        }

        if (testFile != null)
            return client.RunTestFile(testFile);
        else
            return client.RunInteractive();
    }

    private static void PrintUsage()
    {
        Console.WriteLine("Usage: dotnet run [OPTIONS]");
        Console.WriteLine("  -h, --help                       This help.");
        Console.WriteLine("  -t, --test <file.test>           Execute test script. If any test fails. Return code will be -1.");
        Console.WriteLine("  -sp, --serial-port <com_port>    Set default port to use. On windows this should be COMn, on linux /dev/ttySn");
        Console.WriteLine("  -sb, --serial-baud <baud_rate>   Baud rate to use for serial port.");
        Console.WriteLine("  -th, --tcp-host <host>           Sets default TCP host.");
        Console.WriteLine("  -tp, --tcp-port <port>           Sets default TCP port.");
    }
}