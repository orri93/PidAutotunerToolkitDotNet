#ifndef GOS_PID_ARDUINO_AUTOTUNING_OUTPUT_H_
#define GOS_PID_ARDUINO_AUTOTUNING_OUTPUT_H_
struct AutotuningOutput {
  int Result;
  bool TuningCompleted;
  double Kp;
  double Ki;
  double Kd;
  double Ku;
  double Pu;
  int LookbackNumber;
  int SampleTime;
};
#endif
