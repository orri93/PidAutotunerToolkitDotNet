#ifndef GOS_PID_TOOLKIT_STATISTICS_H_
#define GOS_PID_TOOLKIT_STATISTICS_H_

#include <cmath>

#include <memory>
#include <vector>

#include <gos/pid/toolkit/types.h>
#include <gos/pid/toolkit/utilities.h>

namespace gos {
namespace pid {
namespace toolkit {

template<typename T>
class Statistics {
public:
  typedef ::std::vector<T> Vector;

  Statistics() : sum_(0) {
  }

  virtual ~Statistics() {
  }

#ifdef GOS_PID_TOOLKIT_STATISTICS_SUPPORT_RANGE
  void setrange(const T& lowest, const T& highest) {
    range_ = std::make_unique<::gos::pid::toolkit::type::range<T>>(
      lowest,
      highest);
  }
  ::gos::pid::toolkit::type::range<T>& getrange() {
    return *range_;
  }
#endif

  virtual void add(const T& value) {
#ifdef GOS_PID_TOOLKIT_STATISTICS_SUPPORT_RANGE
    if (range_) {
      if (::gos::pid::toolkit::utilities::isinside<T>(range_, value)) {
        this->vector_.push_back(value);
        this->sum_ += value;
      }
    } else {
      this->vector_.push_back(value);
      this->sum_ += value;
    }
#else
    this->vector_.push_back(value);
    this->sum_ += value;
#endif
  }

  void clear() {
    this->sum_ = T(0);
    this->vector_.clear();
  }

  size_t count() const {
    return static_cast<size_t>(vector_.size());
  }

  const Vector& vector() const {
    return vector_;
  }

  const T& sum() const {
    return sum_;
  }

  T mean() const {
    return sum_ / static_cast<T>(vector_.size());
  }

  T median() {
    VectorSizeType size = this->vector_.size();
    if (size > 1) {
      size_t medianindex = size / static_cast<T>(2);
      Vector sorted(vector_);
      ::std::sort(sorted.begin(), sorted.end());
      if (size % 2 == 0) {
        return (sorted[medianindex - 1] + sorted[medianindex]) /
          static_cast<T>(2);
      } else {
        return sorted[medianindex];
      }
    } else if (size == 1) {
      return *(this->vector_.begin());
    } else {
      return 0.0;
    }
  }

  T variance() const {
    T diff;
    T variance = 0.0;
    T mean = this->mean();
    for (auto v : this->vector_) {
      diff = v - mean;
      variance += diff * diff;
    }
    return variance / this->vector_.size();
  }

  T sd() const {
    if (T == double) {
      return ::sqrt(variance());
    } else if (T == float) {
      return ::sqrtf(variance())
    } else {
      return static_cast<T>(::sqrt(static_cast<double>(variance())));
    }
  }

protected:
#ifdef GOS_PID_TOOLKIT_STATISTICS_SUPPORT_RANGE
  typedef std::unique_ptr<::gos::pid::toolkit::type::range<T>> RangePointer;
  RangePointer range_;
#endif
  Vector vector_;
  T sum_;
};

} // namespace toolkit
} // namespace pid
} // namespace gos
#endif
