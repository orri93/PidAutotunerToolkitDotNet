#ifndef GOS_PID_TUNING_UI_LIB_TYPES_H_
#define GOS_PID_TUNING_UI_LIB_TYPES_H_

#include <chrono>
#include <string>

#define GOS_PID_TUNING_COMPARE_PTR(l,r) ( ( (l) != nullptr && (r) != nullptr) ? \
  ( *l == *r ) :  ( (l) == nullptr && (r) == nullptr ) )

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

enum class operation {
  undefined,
  add,
  subtract
};

typedef std::chrono::steady_clock Clock;
typedef Clock::duration Duration;
typedef Clock::time_point Time;

namespace to {
std::string string(const status& status);
} // namespace to

namespace configuration {
enum class mode { normal, write, initializing };
}

namespace compare {
template<typename T> inline bool pointers(const T* l, const T* r) {
  return 
    (l != nullptr && r != nullptr) ?
    (*l == *r) :
    l == nullptr && r == nullptr;
}
}

} // namespace types
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
