namespace PidToolkit.AutoTune
{
  public class Parameters
  {
    public Parameters()
    {
      this.CompletePeakCount = 10;
      this.MinimumLookbacCount = 9;
      this.MaximumLookbacCount = 100;
      this.LookbackThreshold = 25;
      this.LowLookbackFactor = 4;
      this.LowLookbackSampleTime = 250;
      this.HihgLookbackFactor = 10;
    }

    public int CompletePeakCount { get; set; }

    public int LookbackThreshold { get; set; }

    public int MinimumLookbacCount { get; set; }

    public int MaximumLookbacCount { get; set; }

    public int LowLookbackFactor { get; set; }

    public int LowLookbackSampleTime { get; set; }

    public int HihgLookbackFactor { get; set; }

  }
}
