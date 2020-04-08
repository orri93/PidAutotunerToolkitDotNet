using NUnit.Framework;

namespace ControllerNUnitTest
{
  public class SettingsTest
  {
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void TestSettings()
    {
      PidToolkit.Controller.Settings settings;

      settings = new PidToolkit.Controller.Settings();
      Assert.IsNotNull(settings);

      Assert.AreEqual(PidToolkit.ControlType.PID, settings.Type);

      Assert.AreEqual(0.0, settings.Time, PidToolkitTesting.Parameters.Delta);
      Assert.IsNull(settings.Range);
    }
  }
}
