#include "pch.h"
#include <gos/pid/arduino/autotuning/arduinobasedautotuning.h>

#include <cstdlib>

ArduinoPidAutotuning::ArduinoPidAutotuning() :
  isMax(false),
  isMin(false),
  input(nullptr),
  output(nullptr),
  setpoint(0.0),
  noiseBand(0.0),
  controlType(0),
  running(false),
  peak1(0),
  peak2(0),
  lastTime(0),
  sampleTime(0),
  nLookBack(0),
  peakType(0),
  peakCount(0),
  justchanged(false),
  justevaled(false),
  absMax(0.0),
  absMin(0.0),
  oStep(0.0),
  outputStart(0.0),
  Ku(0.0),
  Pu(0.0) {
}

void ArduinoPidAutotuning::SetInput(const AutotuningInput& autotuning) {
  autotuningin_.ControlType = autotuning.ControlType;
  autotuningin_.Autotune = autotuning.Autotune;
  autotuningin_.Input = autotuning.Input;
  autotuningin_.Output = autotuning.Output;
  autotuningin_.OutputStep = autotuning.OutputStep;
  autotuningin_.NoiseBand = autotuning.NoiseBand;
  autotuningin_.Lookback = autotuning.Lookback;
  autotuningin_.CurrentTick = autotuning.CurrentTick;
}

void ArduinoPidAutotuning::SetParameters(
  const AutotuningParameters& parameters) {
  autotuningparameters_.MaximumPeakCount = parameters.MaximumPeakCount;
}

void ArduinoPidAutotuning::Initialize() {
  PID_ATune(&(autotuningin_.Input), &(autotuningin_.Output));
}

void ArduinoPidAutotuning::Execute() {
  switch (autotuningin_.ControlType) {
  case ControlType::PID:
    SetControlType(1);
    break;
  case ControlType::PI:
    SetControlType(0);
    break;
  }
  SetOutputStep(autotuningin_.OutputStep);
  SetNoiseBand(autotuningin_.NoiseBand);
  ArduinoCalculation();
  if (autotuningin_.Autotune) {
    autotuningout_.Result = Runtime();
    autotuningout_.TuningCompleted = autotuningout_.Result == 1 && !running;
  }
  FinishUp();
  ArduinoCalculateKpKiKd();
  variable_.AbsMax = absMax;
  variable_.AbsMin = absMin;
  variable_.Peak1 = peak1;
  variable_.Peak2 = peak2;
  variable_.TuningSetpoint = setpoint;
  variable_.StartOutput = outputStart;
  variable_.LastTime = lastTime;
  variable_.PeakCount = peakCount;
  variable_.TuningOutput = *output;
  variable_.PeakType = peakType;
  variable_.JustChanged = justchanged;
  variable_.JustEvaled = justevaled;
  variable_.IsMax = isMax;
  variable_.IsMin = isMin;
  for (int i = 0; i < ARDUINO_BASE_PID_AUTOTUNING_ARRAY_LAST_INPUT_SIZE; i++) {
    arrayvariable_.LastInput[i] = lastInputs[i];
  }
  for (int i = 0; i < ARDUINO_BASE_PID_AUTOTUNING_ARRAY_PEAK_SIZE; i++) {
    arrayvariable_.Peak[i] = peaks[i];
  }
}

void ArduinoPidAutotuning::ArduinoCalculation() {
  SetLookbackSec(autotuningin_.Lookback);
  autotuningout_.LookbackNumber = nLookBack;
  autotuningout_.SampleTime = sampleTime;
}

void ArduinoPidAutotuning::ArduinoCalculateKpKiKd() {
  autotuningout_.Kp = GetKp();
  autotuningout_.Ki = GetKi();
  autotuningout_.Kd = GetKd();
  autotuningout_.Ku = Ku;
  autotuningout_.Pu = Pu;
}

const AutotuningOutput& ArduinoPidAutotuning::GetOutput() const {
  return autotuningout_;
}

const Variables& ArduinoPidAutotuning::GetVariables() const {
  return variable_;
}

const ArrayVariables& ArduinoPidAutotuning::GetArrayVariables() const {
  return arrayvariable_;
}

void ArduinoPidAutotuning::PID_ATune(double* Input, double* Output) {
  input = Input;
  output = Output;
  controlType = 0; //default to PI
  noiseBand = 0.5;
  running = false;
  oStep = 30;
  SetLookbackSec(10);
  lastTime = autotuningin_.CurrentTick;
}

void ArduinoPidAutotuning::Cancel() {
  running = false;
}

int ArduinoPidAutotuning::Runtime() {
  justevaled = false;
  if (peakCount > 9 && running) {
    running = false;
    FinishUp();
    return 1;
  }
  unsigned long now = autotuningin_.CurrentTick;

  if ((now - lastTime) < sampleTime) return false;
  lastTime = now;
  double refVal = *input;
  justevaled = true;
  if (!running) { //initialize working variables the first time around
    peakType = 0;
    peakCount = 0;
    justchanged = false;
    absMax = refVal;
    absMin = refVal;
    setpoint = refVal;
    running = true;
    outputStart = *output;
    *output = outputStart + oStep;
  } else {
    if (refVal > absMax)absMax = refVal;
    if (refVal < absMin)absMin = refVal;
  }

  //oscillate the output base on the input's relation to the setpoint

  if (refVal > setpoint + noiseBand) *output = outputStart - oStep;
  else if (refVal < setpoint - noiseBand) *output = outputStart + oStep;


  //bool isMax=true, isMin=true;
  isMax = true; isMin = true;
  //id peaks
  for (int i = nLookBack - 1; i >= 0; i--) {
    double val = lastInputs[i];
    if (isMax) isMax = refVal > val;
    if (isMin) isMin = refVal < val;
    lastInputs[i + 1] = lastInputs[i];
  }
  lastInputs[0] = refVal;
  if (nLookBack < 9) {  //we don't want to trust the maxes or mins until the inputs array has been filled
    return 0;
  }

  if (isMax) {
    if (peakType == 0)peakType = 1;
    if (peakType == -1) {
      peakType = 1;
      justchanged = true;
      peak2 = peak1;
    }
    peak1 = now;
    peaks[peakCount] = refVal;

  } else if (isMin) {
    if (peakType == 0)peakType = -1;
    if (peakType == 1) {
      peakType = -1;
      peakCount++;
      justchanged = true;
    }

    if (peakCount < 10)peaks[peakCount] = refVal;
  }

  if (justchanged && peakCount > 2) { //we've transitioned.  check if we can autotune based on the last peaks
    double avgSeparation = (abs(peaks[peakCount - 1] - peaks[peakCount - 2]) + abs(peaks[peakCount - 2] - peaks[peakCount - 3])) / 2;
    if (avgSeparation < 0.05 * (absMax - absMin)) {
      FinishUp();
      running = false;
      return 1;

    }
  }
  justchanged = false;
  return 0;
}
void ArduinoPidAutotuning::FinishUp() {
  *output = outputStart;
  //we can generate tuning parameters!
  Ku = 4 * (2 * oStep) / ((absMax - absMin) * 3.14159);
  Pu = (double)(peak1 - peak2) / 1000;
}

double ArduinoPidAutotuning::GetKp() {
  return controlType == 1 ? 0.6 * Ku : 0.4 * Ku;
}

double ArduinoPidAutotuning::GetKi() {
  return controlType == 1 ? 1.2 * Ku / Pu : 0.48 * Ku / Pu;  // Ki = Kc/Ti
}

double ArduinoPidAutotuning::GetKd() {
  return controlType == 1 ? 0.075 * Ku * Pu : 0;  //Kd = Kc * Td
}

void ArduinoPidAutotuning::SetOutputStep(double Step) {
  oStep = Step;
}

double ArduinoPidAutotuning::GetOutputStep() {
  return oStep;
}

void ArduinoPidAutotuning::SetControlType(int Type) //0=PI, 1=PID
{
  controlType = Type;
}
int ArduinoPidAutotuning::GetControlType() {
  return controlType;
}

void ArduinoPidAutotuning::SetNoiseBand(double Band) {
  noiseBand = Band;
}

double ArduinoPidAutotuning::GetNoiseBand() {
  return noiseBand;
}

void ArduinoPidAutotuning::SetLookbackSec(int value) {
  if (value < 1) value = 1;

  if (value < 25) {
    nLookBack = value * 4;
    sampleTime = 250;
  } else {
    nLookBack = 100;
    sampleTime = value * 10;
  }
}

int ArduinoPidAutotuning::GetLookbackSec() {
  return nLookBack * sampleTime / 1000;
}
