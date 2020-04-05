#ifndef GOS_PID_TOOLKIT_TUNE_INTERNALS_H_
#define GOS_PID_TOOLKIT_TUNE_INTERNALS_H_

namespace gos {
namespace pid {
namespace toolkit {
namespace tune {

struct Internals {
  int LookbackNumber;
  int SampleTime;
};

} // namespace tune
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
