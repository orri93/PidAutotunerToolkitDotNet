using System;

namespace PidToolkitConsoleApp
{
  class Program
  {
    static void Main(string[] args)
    {
      Console.WriteLine("Hello World!");

      PidToolkit.Controller.Pid pid = new PidToolkit.Controller.Pid();

      PidToolkit.AutoTune.Tuner tuner = new PidToolkit.AutoTune.Tuner();

      pid.Settings.Range = new PidToolkit.Range();
    }
  }
}
