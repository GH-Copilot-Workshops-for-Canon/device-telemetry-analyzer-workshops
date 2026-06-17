using System.Diagnostics;

if (args.Length != 1)
{
    Console.Error.WriteLine("usage: DeviceTelemetry.Cli <input-file>");
    return 2;
}

var repoRoot = FindRepoRoot(AppContext.BaseDirectory);
var binary = Path.Combine(repoRoot, "build", "dta");

if (!File.Exists(binary))
{
    Console.Error.WriteLine("build/dta not found. Run `make build` first.");
    return 2;
}

var process = new Process
{
    StartInfo = new ProcessStartInfo
    {
        FileName = binary,
        ArgumentList = { args[0] },
        RedirectStandardOutput = true,
        RedirectStandardError = true,
    }
};

process.Start();
Console.Write(process.StandardOutput.ReadToEnd());
Console.Error.Write(process.StandardError.ReadToEnd());
process.WaitForExit();

return process.ExitCode;

static string FindRepoRoot(string start)
{
    var current = new DirectoryInfo(start);
    while (current is not null)
    {
        if (File.Exists(Path.Combine(current.FullName, "Makefile")))
        {
            return current.FullName;
        }
        current = current.Parent;
    }

    return Directory.GetCurrentDirectory();
}
