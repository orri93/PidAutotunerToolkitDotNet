#ifndef GOS_PID_TOOLKIT_TYPES_H_
#define GOS_PID_TOOLKIT_TYPES_H_

#include <fstream>
#include <ostream>
#include <string>
#include <chrono>
#include <memory>

namespace gos {
namespace pid {
namespace toolkit {
namespace type {

typedef ::std::chrono::steady_clock Clock;
typedef Clock::time_point Time;
typedef Clock::duration Duration;

typedef ::std::unique_ptr<std::ofstream> OutputFileStreamPointer;
typedef ::std::unique_ptr<std::ostream> OutputStreamPointer;

enum class level {
  silent,
  normal,
  verbose
};

template<typename T> struct range {
  T lowest;
  T highest;
};

template<typename T> range<T> make_range(const T& lowest, const T& highest) {
  range<T> range;
  range.lowest = lowest;
  range.highest = highest;
  return range;
}

} // namespace type
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
