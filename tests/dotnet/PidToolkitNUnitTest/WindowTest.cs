using NUnit.Framework;

namespace PidToolkitNUnitTest
{
  public class WindowTest
  {
    const double Delta = 0.0000000001;

    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void TestMedian()
    {
      double median;
      double[] a1 = new double[] { 9.0, 1.0, 3.0, 6.0, 3.0, 8.0, 7.0 };
      double[] a2 = new double[] { 9.0, 1.0, 3.0, 2.0, 4.0, 5.0, 8.0, 6.0 };

      PidToolkit.Window window;

      window = CreateWindow(a1.Length, a1);
      median = window.Median;
      Assert.AreEqual(6.0, median, Delta);

      window = CreateWindow(a2.Length, a2);
      median = window.Median;
      Assert.AreEqual(4.5, median, Delta);
    }

    [Test]
    public void TestSum()
    {
      double sum;
      double[] a1 = new double[] { 900.0, 600.0, 470.0, 170.0, 430.0, 300.0 };

      PidToolkit.Window window = CreateWindow(a1.Length - 1, a1);
      sum = window.Sum;

      Assert.AreEqual(600.0 + 470.0 + 170.0 + 430.0 + 300.0, sum, Delta);
    }

    [Test]
    public void TestMean()
    {
      // https://www.mathsisfun.com/data/standard-deviation.html

      double mean;
      double[] a1 = new double[] { 900.0, 600.0, 470.0, 170.0, 430.0, 300.0 };

      PidToolkit.Window window = CreateWindow(a1.Length - 1, a1);
      mean = window.Mean;

      Assert.AreEqual(394, mean, Delta);
    }

    [Test]
    public void TestVariance()
    {
      // https://www.mathsisfun.com/data/standard-deviation.html

      double variance;
      double[] a1 = new double[] { 900.0, 600.0, 470.0, 170.0, 430.0, 300.0 };

      PidToolkit.Window window = CreateWindow(a1.Length - 1, a1);
      variance = window.Variance;

      Assert.AreEqual(21704.0, variance, Delta);
    }

    [Test]
    public void TestSd()
    {
      // https://www.mathsisfun.com/data/standard-deviation.html

      double sd;
      double[] a1 = new double[] { 900.0, 600.0, 470.0, 170.0, 430.0, 300.0 };

      PidToolkit.Window window = CreateWindow(a1.Length - 1, a1);
      sd = window.Sd;

      Assert.AreEqual(147.32277488562318, sd, Delta);
    }

    [Test]
    public void TestAdd()
    {
      PidToolkit.Window window = new PidToolkit.Window();

      for(int i = 0; i < 20; i++)
      {
        window.Add((double)i);
        Assert.AreEqual(i < 9 ? i + 1 : 10, window.Count);
      }

      Assert.AreEqual(10, window.Count);
    }

    private PidToolkit.Window CreateWindow(int size, double[] array)
    {
      PidToolkit.Window window = new PidToolkit.Window();
      window.Size = size;
      foreach (double a in array)
      {
        window.Add(a);
      }
      return window;
    }
  }
}