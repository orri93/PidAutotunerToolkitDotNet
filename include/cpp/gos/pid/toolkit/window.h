/*****************************************************************//**
 * \file   window.h
 * \brief  The Statistical Window include file.
 * 
 * \author SigurdssonGO
 * \date   May 2020
 *********************************************************************/
#ifndef GOS_PID_TOOLKIT_WINDOW_H_
#define GOS_PID_TOOLKIT_WINDOW_H_

#include <cmath>

#include <memory>
#include <vector>

#include <gos/pid/toolkit/statistics.h>

#define GOS_PID_TOOLKIT_WINDOW_DEFUALT_SIZE 10


namespace gos {
namespace pid {
namespace toolkit {
namespace statistics {


template<typename T>
class window : public virtual ::gos::pid::toolkit::Statistics<T> {
public:

  window() : size_(GOS_PID_TOOLKIT_WINDOW_DEFUALT_SIZE) {
  }

  window(const size_t& size) : size_(size) {
  }

  void set(const size_t& size) {
    size_ = size;
  }

  const size_t& size() const {
    return size_;
  }

  void add(const T& value) {
    if (static_cast<size_t>(this->vector_.size()) >= this->size_) {
      this->sum_ -= *(this->vector_.begin());
      this->vector_.erase(this->vector_.begin());
    }
    ::gos::pid::toolkit::Statistics<T>::add(value);
  }

private:
  size_t size_;
};

} // namespace statistics
} // namespace toolkit
} // namespace pid 
} // namespace gos
#endif
