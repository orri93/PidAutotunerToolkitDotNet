using System;
using System.Collections.Generic;
using System.Text;

namespace PidToolkit
{
  public class Range
  {
    public Range()
    {
      this.Lowest = 0.0;
      this.Highest = 255.0;
    }

    public double Lowest { get; set; }

    public double Highest { get; set; }
  }
}
