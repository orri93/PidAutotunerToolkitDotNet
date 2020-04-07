namespace PidToolkit.Controller
{
  public class Pid
  {
    public Settings Settings
    {
      get { return this.settings; }
      set { this.settings = value; }
    }

    public Terms Tune
    {
      get { return this.tune; }
      set { this.tune = value; }
    }

    public Variables Variables { get { return this.variables; } }

    public Terms Terms { get { return this.terms; } }

    public bool IsHigh { get { return this.high; } }

    public bool IsLow { get { return this.low; } }

    public double Output { get { return this.output; } }

    public void ClearIntegral()
    {
      this.variables.Integral = 0.0;
    }

    public void Initialize()
    {
      this.variables.Error = 0.0;
      this.variables.LastError = 0.0;
      this.variables.Integral = 0.0;
      this.variables.Derivative = 0.0;
    }

    public double Execute(double input)
    {
      this.variables.Error = this.settings.Setpoint - input;
      this.variables.Integral += this.variables.Error * this.settings.Time;
      this.terms.P = this.tune.P * this.variables.Error;
      this.terms.I = this.tune.I * this.variables.Integral;
      switch (this.settings.Type)
      {
        case ControlType.PID:
          this.variables.Derivative = 
            (this.variables.Error - this.variables.LastError) /
            this.settings.Time;
          this.terms.D = this.tune.D * this.variables.Derivative;
          break;
        case ControlType.PI:
          this.variables.Derivative = 0.0;
          this.terms.D = 0.0;
          break;
      }
      this.variables.LastError = this.variables.Error;
      this.output = this.terms.P + this.terms.I + this.terms.D;
      high = output > this.settings.Range.Highest;
      low = output < this.settings.Range.Lowest;
      if(!high && !low)
      {
        return output;
      }
      else if(high)
      {
        return this.settings.Range.Highest;
      }
      else
      {
        return this.settings.Range.Lowest;
      }
    }

    private bool low;
    private bool high;

    private double output;

    private Settings settings;
    private Variables variables;
    private Terms terms;
    private Terms tune;
  }
}
