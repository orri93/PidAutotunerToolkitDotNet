using NUnit.Framework;

namespace PidToolkitNUnitTest
{
  public class RangeTest
  {
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void TestRange()
    {
      PidToolkit.Range range = new PidToolkit.Range();

      Assert.AreEqual(0.0, range.Lowest, PidToolkitTesting.Parameters.Delta);
      Assert.AreEqual(255.0, range.Highest, PidToolkitTesting.Parameters.Delta);
    }

    [Test]
    public void TestRestrict()
    {
      double input, output, lowest, highest;
      PidToolkit.Range range = new PidToolkit.Range();

      lowest = -10.0;
      highest = 10.0;

      range.Lowest = lowest;
      range.Highest = highest;

      input = 0.0;
      output = range.Restrict(input);
      Assert.AreEqual(input, output, PidToolkitTesting.Parameters.Delta);
      Assert.IsFalse(range.IsHigh);
      Assert.IsFalse(range.IsLow);

      input = 5.5;
      output = range.Restrict(input);
      Assert.AreEqual(input, output, PidToolkitTesting.Parameters.Delta);
      Assert.IsFalse(range.IsHigh);
      Assert.IsFalse(range.IsLow);

      input = lowest;
      output = range.Restrict(input);
      Assert.AreEqual(input, output, PidToolkitTesting.Parameters.Delta);
      Assert.IsFalse(range.IsHigh);
      Assert.IsFalse(range.IsLow);

      input = highest;
      output = range.Restrict(input);
      Assert.AreEqual(input, output, PidToolkitTesting.Parameters.Delta);
      Assert.IsFalse(range.IsHigh);
      Assert.IsFalse(range.IsLow);

      input = lowest - 0.1;
      output = range.Restrict(input);
      Assert.AreEqual(lowest, output, PidToolkitTesting.Parameters.Delta);
      Assert.IsFalse(range.IsHigh);
      Assert.IsTrue(range.IsLow);

      input = highest + 0.1;
      output = range.Restrict(input);
      Assert.AreEqual(highest, output, PidToolkitTesting.Parameters.Delta);
      Assert.IsTrue(range.IsHigh);
      Assert.IsFalse(range.IsLow);
    }
  }
}
