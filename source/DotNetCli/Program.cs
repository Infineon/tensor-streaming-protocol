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

        bool interactive = true;
        string? testFile = null;

        for (var index = 0; index < args.Length; index++)
        {
            var arg = args[index];
            switch (arg)
            {
                case "--non-interactive" or "-i":
                    interactive = false;
                    break;
                case "--test" or "-t":
                    if (arg.Length - 1 <= index)
                    {
                        Console.WriteLine($"Error: Missing argument for option --test/-t");
                        Console.WriteLine();
                        PrintUsage();
                        return -1;
                    }                        
                    testFile = args[index+1];
                    index++;
                    break;
                default:
                    Console.WriteLine($"Error: Unknown argument {arg}");
                    Console.WriteLine();
                    PrintUsage();
                    return -1;
            }
        }

        if (testFile != null)
            return client.RunTestFile(testFile);
        else
            return client.Run(interactive);
    }

    private static void PrintUsage()
    {
        Console.WriteLine("Usage: dotnet run [OPTIONS]");
        Console.WriteLine("  -i, --non-interactive      Run in non interactive script mode.");
    }
}