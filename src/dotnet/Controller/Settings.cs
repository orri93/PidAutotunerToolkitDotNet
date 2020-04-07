namespace PidToolkit.Controller
{
  public class Settings
  {
    public Settings()
    {
      this.Type = ControlType.PID;
      this.Range = new Range();
    }

    public ControlType Type { get; set; }

    public double Setpoint;

    public double Time;

    public Range Range { get; set; }
  }
}
