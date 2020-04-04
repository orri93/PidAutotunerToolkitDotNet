namespace PidToolkit.AutoTune
{
  public class Settings
  {
    public Settings ()
    {
      this.Type = ControlType.PID;
      this.NoiseBand = 0.5;
      this.Lookback = 10;
      this.Range = new Range();
    }

    public ControlType Type { get; set; }

    public double NoiseBand { get; set; }

    public int Lookback { get; set; }

    public Range Range { get; set; }
  }
}
