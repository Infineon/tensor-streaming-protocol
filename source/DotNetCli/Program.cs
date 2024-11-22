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

        foreach (var arg in args)
        {
            switch (arg)
            {
                case "--non-interactive" or "-i":
                    interactive = false;
                    break;
                default:
                    Console.WriteLine($"Error: Unknown argument {arg}");
                    Console.WriteLine();
                    PrintUsage();
                    return -1;
            }
        }
        return client.Run(interactive);
    }

    private static void PrintUsage()
    {
        Console.WriteLine("Usage: dotnet run [OPTIONS]");
        Console.WriteLine("  -i, --non-interactive      Run in non interactive script mode.");
    }
}