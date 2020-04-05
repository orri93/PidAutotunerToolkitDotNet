#ifndef GOS_PID_TOOLKIT_TUNE_SETTINGS_H_
#define GOS_PID_TOOLKIT_TUNE_SETTINGS_H_

namespace gos {
namespace pid {
namespace toolkit {
namespace tune {

struct Settings {
  Settings();
  int CompletePeakCount;
  int LookbackThreshold;
  int MinimumLookbacCount;
  int MaximumLookbacCount;
  int LowLookbackFactor;
  int LowLookbackSampleTime;
  int HihgLookbackFactor;
};

} // namespace tune
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
