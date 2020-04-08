using NUnit.Framework;

namespace ControllerNUnitTest
{
  public class VariablesTest
  {
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void TestVariables()
    {
      PidToolkit.Controller.Variables variables;

      variables = new PidToolkit.Controller.Variables();
      Assert.IsNotNull(variables);

      Assert.AreEqual(0.0, variables.LastError,
        PidToolkitTesting.Parameters.Delta);
      Assert.AreEqual(0.0, variables.Error,
        PidToolkitTesting.Parameters.Delta);
      Assert.AreEqual(0.0, variables.Integral,
        PidToolkitTesting.Parameters.Delta);
      Assert.AreEqual(0.0, variables.Derivative,
        PidToolkitTesting.Parameters.Delta);
    }
  }
}
