namespace PidToolkit
{
  public class Range
  {
    public Range()
    {
      this.Lowest = 0.0;
      this.Highest = 255.0;
      this.ishigh = false;
      this.islow = false;
    }

    public double Lowest { get; set; }

    public double Highest { get; set; }

    public bool IsHigh { get { return this.ishigh; } }

    public bool IsLow { get { return this.islow; } }

    public double Restrict(double value)
    {
      this.ishigh = value > this.Highest;
      this.islow = value < this.Lowest;
      if(!this.ishigh && !this.islow)
      {
        return value;
      }
      else if(this.ishigh)
      {
        return this.Highest;
      }
      else
      {
        return this.Lowest;
      }
    }

    private bool ishigh;
    private bool islow;
  }
}
