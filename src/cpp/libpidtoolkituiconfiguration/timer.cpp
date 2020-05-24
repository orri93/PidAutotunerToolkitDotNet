#include <algorithm>

#include <gos/pid/ui/configuration/timer.h>

/* Timer configuration group */
#define GROUP_TIMER "Timer"
#define KEY_INTERVAL "Interval"
#define KEY_APPLY_TO_CONTROLLER "ApplyToController"
#define DEFAULT_INTERVAL 250
#define DEFAULT_APPLY_TO_CONTROLLER false

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Timer::Timer(QObject* parent) :
  gptum::Ptu(parent)
  /* QObject(parent) */ {
}

Timer::Timer(const Timer& timer) :
  /* Timers configuration */
  interval_(timer.interval_),
  applyIntervalToController_(timer.applyIntervalToController_) {
}

Timer& Timer::operator=(const Timer& timer) {
  return set(timer);
}

Timer& Timer::set(const Timer& timer) {
  if (this != &timer) {
    /* Timer output items */
    this->interval_ = timer.interval_;
    this->applyIntervalToController_ = timer.applyIntervalToController_;
  }
  return *this;
}

QSettings* Timer::read(QSettings* settings) {
  QVariant value;

  /* Timer configuration group */
  settings->beginGroup(GROUP_TIMER);

  value = settings->value(KEY_INTERVAL, DEFAULT_INTERVAL);
  setInterval(value.toInt());
  value = settings->value(KEY_APPLY_TO_CONTROLLER, DEFAULT_APPLY_TO_CONTROLLER);
  setApplyIntervalToController(value.toBool());

  /* TIMER configuration group */
  settings->endGroup();

  return settings;
}

QSettings* Timer::write(QSettings* settings) {

  /* Timer configuration group */
  settings->beginGroup(GROUP_TIMER);
  settings->setValue(KEY_INTERVAL, interval_);
  settings->setValue(KEY_APPLY_TO_CONTROLLER, applyIntervalToController_);
  /* TIMER configuration group */
  settings->endGroup();

  return settings;
}

/* Timer output items */
const int& Timer::interval() const  { return interval_; }
const bool& Timer::applyIntervalToController() const {
  return applyIntervalToController_;
}

/* Timers configuration */
bool Timer::applyInterval(const int& value) {
  if (interval_ != value) {
    interval_ = value;
    return true;
  } else {
    return false;
  }
}
bool Timer::applyApplyIntervalToController(const bool& value) {
  if (applyIntervalToController_ != value) {
    applyIntervalToController_ = value;
    return true;
  } else {
    return false;
  }
}

/* Timers configuration */
void Timer::setInterval(const int& value) {
  if (applyInterval(value)) {
    emit intervalChanged();
  }
}
void Timer::setApplyIntervalToController(const bool& value) {
  if (applyApplyIntervalToController(value)) {
    emit applyIntervalToControllerChanged();
  }
}


} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptuc::Timer& lhs, const gptuc::Timer& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptuc::Timer& lhs, const gptuc::Timer& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptuc::Timer& first, const gptuc::Timer& second) {
  return (
    /* Timer output items */
    first.interval_ == second.interval_ &&
    first.applyIntervalToController_ == second.applyIntervalToController_) ?
    0 : 1;
}
