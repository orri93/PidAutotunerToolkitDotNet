#ifndef GOS_PID_TUNING_BLACK_BOX_NOTIFY_H_
#define GOS_PID_TUNING_BLACK_BOX_NOTIFY_H_

#include <memory>
#include <gos/pid/arduino/types.h>

namespace gos {
namespace pid {
namespace tuning {

class Nofity {
public:
  virtual ~Nofity() {}

  virtual void notifyForce(const ::gos::pid::arduino::types::Unsigned& value) = 0;
  virtual void notifyKp(const ::gos::pid::arduino::types::Real& kp) = 0;
  virtual void notifyKi(const ::gos::pid::arduino::types::Real& ki) = 0;
  virtual void notifyKd(const ::gos::pid::arduino::types::Real& kd) = 0;
};

typedef std::unique_ptr<Nofity> NotifyPointer;

} // namespace tuning
} // namespace pid
} // namespace gos

#endif
