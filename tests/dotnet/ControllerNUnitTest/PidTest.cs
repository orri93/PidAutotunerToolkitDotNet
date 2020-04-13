using NUnit.Framework;

namespace ControllerNUnitTest
{
  public class PidTest
  {
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void TestExecute()
    {
      PidToolkit.Controller.Pid pid = new PidToolkit.Controller.Pid();
      Assert.IsNotNull(pid.Variables);
      Assert.IsNotNull(pid.Settings);
      Assert.IsNotNull(pid.Terms);
    }
  }
}