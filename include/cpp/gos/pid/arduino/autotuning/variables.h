#ifndef GOS_PID_ARDUINO_AUTOTUNING_VARIABLES_H_
#define GOS_PID_ARDUINO_AUTOTUNING_VARIABLES_H_
struct Variables {
  double AbsMax;
  double AbsMin;
  unsigned int Peak1;
  unsigned int Peak2;
  double TuningSetpoint;
  double StartOutput;
  unsigned int LastTime;
  unsigned int PeakCount;
  double TuningOutput;
  int PeakType;
  bool JustChanged;
  bool JustEvaled;
  bool IsMax;
  bool IsMin;
};
#endif
