#ifndef GOS_PID_TUNING_TYPES_H_
#define GOS_PID_TUNING_TYPES_H_

#include <boost/optional.hpp>

#include <gos/pid/arduino/types.h>

namespace gos {
namespace pid {
namespace tuning {
namespace types {

enum class TuningMode {
  undefined,
  blackbox
};

typedef boost::optional<::gos::pid::arduino::types::Real> OptionalReal;
typedef boost::optional<::gos::pid::arduino::types::Unsigned> OptionalUnsigned;

struct Initialized {
  OptionalReal Kp;
  OptionalReal Ki;
  OptionalReal Kd;
  OptionalReal Setpoint;
  OptionalUnsigned Manual;
};

struct Evaluation {
  ::gos::pid::arduino::types::Real Kp;
  ::gos::pid::arduino::types::Real Ki;
  ::gos::pid::arduino::types::Real Kd;
  ::gos::pid::arduino::types::Real PeakError;
  ::gos::pid::arduino::types::Real StableError;
  ::gos::pid::arduino::types::Real Performance;
};

struct Parameters {
  ::gos::pid::arduino::types::Real Sd;
  ::gos::pid::arduino::types::Range Kp;
  ::gos::pid::arduino::types::Range Ki;
  OptionalReal BaseLine;
};

struct Variables {
  ::gos::pid::arduino::types::Real Kp;
  ::gos::pid::arduino::types::Real Ki;
  ::gos::pid::arduino::types::Real Minimum;
  ::gos::pid::arduino::types::Real Maximum;
  ::gos::pid::arduino::types::Real Mean;
  int Round;
};

typedef std::unique_ptr<Evaluation> EvaluationPointer;

} // namespace types
} // namespace tuning
} // namespace pid
} // namespace gos

#endif
