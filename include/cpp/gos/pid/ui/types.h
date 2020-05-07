#ifndef GOS_PID_TUNING_UI_LIB_TYPES_H_
#define GOS_PID_TUNING_UI_LIB_TYPES_H_

#include <chrono>
#include <string>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace types {

enum class status {
  undefined,
  connecting,
  connected,
  disconnecting,
  disconnected,
  unknown
};

typedef std::chrono::steady_clock Clock;
typedef Clock::duration Duration;
typedef Clock::time_point Time;

namespace to {
std::string string(const status& status);
} // namespace to

} // namespace types
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
