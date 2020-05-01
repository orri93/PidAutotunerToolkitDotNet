#ifndef GOS_PID_TOOLKIT_UTILITIES_H_
#define GOS_PID_TOOLKIT_UTILITIES_H_

#include <gos/pid/toolkit/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace utilities {

template<typename T>
T scale(const ::gos::pid::toolkit::type::range<T>& range) {
  return range.highest - range.lowest;
}

template<typename T>
T midpoint(const ::gos::pid::toolkit::type::range<T>& range) {
  return range.lowest + scale(range) / 2;
}

template<typename T> bool isinside(
  const ::gos::pid::toolkit::type::range<T>& range,
  const T& value) {
  return value <= range.highest && value >= range.lowest;
}

template<typename T> bool isinside(
  const ::gos::pid::toolkit::type::range<T>& range,
  const T& value,
  bool& islow,
  bool& ishigh) {
  islow = value < range.lowest;
  ishigh = value > range.highest;
  return !islow && !ishigh;
}

template<typename T>
T restrict(
  const ::gos::pid::toolkit::type::range<T>& range,
  const T& value){
  if (value <= range.highest && value >= range.lowest) {
    return value;
  } else if (value > range.highest) {
    return range.highest;
  } else {
    return range.lowest;
  }
}

template<typename T>
T restrict(
  const ::gos::pid::toolkit::type::range<T>& range,
  const T& value,
  bool& islow,
  bool& ishigh) {
  islow = value < range.lowest;
  ishigh = value > range.highest;
  if (!islow && !ishigh) {
    return value;
  } else if (ishigh) {
    return range.highest;
  } else {
    return range.lowest;
  }
}



} // namespace utilities
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
