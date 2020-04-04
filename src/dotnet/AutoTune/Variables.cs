namespace PidToolkit.AutoTune
{
  public class Variables
  {
    public double Setpoint { get; set; }

    public double AbsMax { get; set; }

    public double AbsMin { get; set; }

    public uint LastTime { get; set; }

    public uint Peak1 { get; set; }

    public uint Peak2 { get; set; }

    public int PeakCount { get; set; }

    public int PeakType { get; set; }

    public bool JustChanged { get; set; }

    public bool JustEvaled { get; set; }

    public bool IsMax { get; set; }

    public bool IsMin { get; set; }
  }
}

