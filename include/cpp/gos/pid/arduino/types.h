#ifndef GOS_PID_ARDUINO_TYPES_H_
#define GOS_PID_ARDUINO_TYPES_H_

#include <gos/pid/toolkit/types.h>
#include <gos/pid/toolkit/statistics.h>
#include <gos/pid/toolkit/window.h>

namespace gos {
namespace pid {
namespace arduino {
namespace types {

typedef uint16_t Unsigned;
typedef float Real;

typedef ::gos::pid::toolkit::type::range<Real> Range;

typedef ::gos::pid::toolkit::Statistics<Real> Statistics;
typedef ::gos::pid::toolkit::statistics::window<Real> Window;

} // namespace types
} // namespace arduino
} // namespace pid
} // namespace gos

#endif
