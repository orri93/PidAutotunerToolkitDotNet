using System.Collections.Generic;

namespace PidToolkit
{
  public class Window
  {
    public Window()
    {
      this.Size = 10;
      this.list = new List<double>();
      this.Range = null;
    }

    public int Size { get; set; }

    public int Count { get { return this.list.Count; } }

    public double[] Array { get { return this.list.ToArray();} }

    public double Sum { get { return this.sum; } }

    public double Mean { get  { return this.sum / this.list.Count; } }

    public double Median
    {
      get
      {
        // https://en.wikipedia.org/wiki/Median
        if (this.list.Count > 1)
        {
          int medianindex = this.list.Count / 2;
          List<double> sorted = new List<double>(this.list);
          sorted.Sort();
          if (sorted.Count % 2 == 0)
          {
            return (sorted[medianindex - 1] + sorted[medianindex]) / 2.0;
          }
          else
          {
            return sorted[medianindex];
          }
        }
        else if(this.list.Count == 1)
        {
          return this.list[0];
        }
        else
        {
          return 0.0;
        }
      }
    }

    public double Variance 
    { 
      get 
      {
        double variance = 0.0;
        double mean = this.Mean;
        foreach (double v in this.list)
        {
          double difference = v - mean;
          variance += difference * difference;
        }
        return variance / this.list.Count;
      } 
    }

    public double Sd { get { return System.Math.Sqrt(this.Variance); } }

    public Range Range { get; set; }

    public void Add(double value)
    {
      if(this.list.Count >= this.Size)
      {
        this.sum -= this.list[0];
        this.list.RemoveAt(0);
      }
      this.list.Add(value);
      this.sum += value;
    }

    private double sum;
    private System.Collections.Generic.List<double> list;
  }
}
