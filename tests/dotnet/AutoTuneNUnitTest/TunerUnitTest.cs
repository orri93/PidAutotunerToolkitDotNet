using NUnit.Framework;
using PidToolkit.AutoTune;
using PidToolkit;

namespace AutoTuneNUnitTest
{
  public class Tests
  {
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void TestExecute()
    {
      double output;
      Parameters parameters = new Parameters();
      Settings settings = new Settings();

      settings.Lookback = 10;
      settings.NoiseBand = 10.0;
      settings.Type = ControlType.PID;

      Tuner tuner = new Tuner(parameters, settings);

      output = tuner.Execute(false, 0, 666.418, 0, 30.0);

      output = tuner.Execute(false, 1000, 666.418, 0, 30.0);

      output = tuner.Execute(true, 2000, 666.418, 0, 30.0);

      output = tuner.Execute(true, 3000, 66.44, 30.0, 30.0);
    }
  }
}