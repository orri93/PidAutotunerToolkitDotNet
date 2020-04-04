using System;
using System.Collections.Generic;
using System.Text;

namespace PidToolkit.AutoTune
{
  public class Tuner
  {
    public Tuner()
    {
      this.terms = new Terms();
      this.status = new Status();
      this.internals = new Internals();
      this.parameters = new Parameters();
      this.variables = new Variables();
      this.settings = new Settings();
      this.originaloutput = 0.0;
      this.originalstep = 0.0;
      this.output = 0.0;

      this.lastInputArray = new double[InitialLastInputArraySize];
      this.peakArray = new double[InitialPeakArraySize];

      CalculateTimes();
    }

    public Tuner(Parameters parameters) : this()
    {
      this.Parameters = parameters;
    }

    public Tuner(Settings settings) : this()
    {
      this.settings = settings;
    }

    public Tuner(Parameters parameters, Settings settings) : this()
    {
      this.Parameters = parameters;
      this.settings = settings;
    }

    public bool IsCompleted { get; private set; }

    public Settings Settings
    {
      get { return this.settings; }
      set
      {
        int lastlookback = this.settings.Lookback;
        this.settings = value;
        if (this.settings.Lookback != lastlookback)
        {
          CalculateTimes();
        }
      }
    }

    public Parameters Parameters
    {
      get { return this.parameters; }
      set
      {
        if (value.MaximumLookbacCount + 1 > this.lastInputArray.Length)
        {
          int size = this.lastInputArray.Length;
          double[] copy = new double[size];
          Array.Copy(this.lastInputArray, 0, copy, 0, size);
          this.lastInputArray = new double[value.MaximumLookbacCount + 1];
          Array.Copy(copy, 0, this.lastInputArray, 0, size);
        }
        int lastlookback = this.settings.Lookback;
        this.parameters = value;
        if (this.settings.Lookback != lastlookback)
        {
          CalculateTimes();
        }
      }
    }

    public double[] LastInputArray { get { return this.lastInputArray; } }

    public double[] PeakArray { get { return this.peakArray; } }

    public Variables Variables { get { return this.variables; } }

    public Internals Internals { get { return this.internals; } }

    public Status Status { get { return this.status; } }

    public Terms Terms { get { return this.terms; } }

    public double Ku { get { return this.ku; } }

    public double Pu { get { return this.pu; } }

    public double Execute(
      bool autotune,
      uint tick,
      double input,
      double output,
      double step = 30.0)
    {
      this.variables.JustEvaled = false;
      if (this.variables.PeakCount > this.parameters.CompletePeakCount && autotune)
      {
        CalculateTerms(step);
        this.IsCompleted = true;
        return this.originaloutput;
      }
      if ((tick - this.variables.LastTime) < this.internals.SampleTime)
      {
        return RestrictOutput();
      }
      this.variables.LastTime = tick;
      double v = input;
      this.variables.JustEvaled = true;

      if (!autotune)
      {
        this.variables.PeakType = 0;
        this.variables.PeakCount = 0;
        this.variables.JustChanged = false;
        this.variables.AbsMax = v;
        this.variables.AbsMin = v;
        this.variables.Setpoint = v;
        originaloutput = output;
        this.output = originaloutput + step;
      }
      else
      {
        if (v > this.variables.AbsMax) this.variables.AbsMax = v;
        if (v < this.variables.AbsMin) this.variables.AbsMin = v;
      }

      if (v > this.variables.Setpoint + this.settings.NoiseBand)
      {
        this.output = this.originaloutput - step;
      }
      else if (v < this.variables.Setpoint - this.settings.NoiseBand)
      {
        this.output = this.originaloutput + step;
      }

      this.variables.IsMax = true;
      this.variables.IsMin = true;

      for (int i = this.internals.LookbackNumber - 1; i >= 0; i--)
      {
        double val = this.lastInputArray[i];
        if (this.variables.IsMax) this.variables.IsMax = v > val;
        if (this.variables.IsMin) this.variables.IsMin = v < val;
        this.lastInputArray[i + 1] =
          this.lastInputArray[i];
      }
      this.lastInputArray[0] = v;

      if (this.internals.LookbackNumber < this.parameters.MinimumLookbacCount)
      {
        // we don't want to trust the maximum or minimums until
        // the inputs array has been filled
        return RestrictOutput();
      }

      if (this.variables.IsMax)
      {
        if (this.variables.PeakType == 0)
        {
          this.variables.PeakType = 1;
        }
        if (this.variables.PeakType == -1)
        {
          this.variables.PeakType = 1;
          this.variables.JustChanged = true;
          this.variables.Peak2 = this.variables.Peak1;
        }
        this.variables.Peak1 = tick;
        this.peakArray[this.variables.PeakCount] = v;
      }
      else if (this.variables.IsMin)
      {
        if (this.variables.PeakType == 0)
        {
          this.variables.PeakType = -1;
        }
        if (this.variables.PeakType == 1)
        {
          this.variables.PeakType = -1;
          this.variables.PeakCount++;
          this.variables.JustChanged = true;
        }
        if (this.variables.PeakCount < InitialPeakArraySize)
          this.peakArray[this.variables.PeakCount] = v;
      }

      if (this.variables.JustChanged && this.variables.PeakCount > 2)
      {
        // We've transitioned.  check if we can auto-tune based on the last peaks
        double avgSeparation =
          (Math.Abs(this.peakArray[this.variables.PeakCount - 1] -
          this.peakArray[this.variables.PeakCount - 2]) +
          Math.Abs(this.peakArray[this.variables.PeakCount - 2] -
          this.peakArray[this.variables.PeakCount - 3])) / 2.0;
        if (avgSeparation < 0.05 *
          (this.variables.AbsMax - this.variables.AbsMin))
        {
          CalculateTerms(step);
          this.IsCompleted = true;
          return originaloutput;
        }
      }
      this.variables.JustChanged = false;
      CalculateTerms(step);
      return RestrictOutput();
    }

    private void CalculateTerms(double step)
    {
      this.ku = 4.0 * (2.0 * step) / 
        ((this.variables.AbsMax - this.variables.AbsMin) * Math.PI);
      this.pu = (double)(this.variables.Peak1 - this.variables.Peak2) / 1000.0;
      switch (this.settings.Type)
      {
        case ControlType.PID:
          this.terms.P = 0.6 * ku;
          this.terms.I = 1.2 * ku / pu;
          this.terms.D = 0.075 * ku * pu;
          break;
        case ControlType.PI:
          this.terms.P = 0.3 * ku;
          this.terms.I = 0.48 * ku / pu;
          this.terms.D = 0.0;
          break;
      }
    }

    private void CalculateTimes()
    {
      if (this.settings.Lookback < 1)
      {
        this.settings.Lookback = 1;
      }
      if (this.settings.Lookback < this.parameters.LookbackThreshold)
      {
        this.internals.LookbackNumber =
          this.parameters.LowLookbackFactor * this.settings.Lookback;
        this.internals.SampleTime = this.parameters.LowLookbackSampleTime;
      }
      else
      {
        this.internals.LookbackNumber = this.parameters.MaximumLookbacCount;
        this.internals.SampleTime =
          this.parameters.HihgLookbackFactor * this.settings.Lookback;
      }
    }

    private double RestrictOutput()
    {
      this.status.OutputLow = this.output < this.settings.Range.Lowest;
      this.status.OutputHigh = this.output > this.settings.Range.Highest;
      if(!this.status.OutputLow && !this.status.OutputHigh)
      {
        return this.output;
      }
      else if(this.status.OutputLow)
      {
        return this.settings.Range.Lowest;
      }
      else
      {
        return this.settings.Range.Highest;
      }
    }

    private const int InitialLastInputArraySize = 101;
    private const int InitialPeakArraySize = 10;

    private double ku;
    private double pu;
    private double output;
    private double originalstep;
    private double originaloutput;
    private double[] lastInputArray;
    private double[] peakArray;

    private Internals internals;
    private Parameters parameters;
    private Variables variables;
    private Settings settings;
    private Status status;
    private Terms terms;
  }
}
