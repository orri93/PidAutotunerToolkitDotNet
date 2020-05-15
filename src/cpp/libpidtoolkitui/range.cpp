#include <gos/pid/ui/range.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Range::Range(QObject* parent) :
  gptuc::Base(parent),
  minimum_(0.0),
  maximum_(10.0) {
}

Range::Range(const double& minimum, const double& maximum, QObject* parent) :
  gptuc::Base(parent),
  minimum_(minimum),
  maximum_(maximum) {
}

Range::Range(const Range& range) :
  minimum_(range.minimum_),
  maximum_(range.maximum_) {
}

Range& Range::operator=(const Range& range) {
  return set(range);
}

Range& Range::set(const Range& range) {
  if (this != &range) {
    setMinimum(range.minimum_);
    setMaximum(range.maximum_);
  }
  return *this;
}

void Range::set(const double& minimum, const double& maximum) {
  setMinimum(minimum);
  setMaximum(maximum);
}

const double& Range::minimum() const {
  return minimum_;
}
const double& Range::maximum() const {
  return maximum_;
}

void Range::setMinimum(const double& value) {
  if (minimum_ != value) {
    minimum_ = value;
    emit minimumChanged();
  }
}
void Range::setMaximum(const double& value) {
  if (maximum_ != value) {
    maximum_ = value;
    emit maximumChanged();
  }
}

Range make_range(const double& minimum, const double& maximum) {
  return Range(minimum, maximum);
}

QSettings* read(QSettings* settings, const QString& key, Range& range) {
  return read(
    settings,
    key,
    range,
    DEFAULT_BB_RANGE_MINIMUM,
    DEFAULT_BB_RANGE_MAXIMUM);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Range& range,
  const double& minimum,
  const double& maximum) {
  QVariant value;
  value = settings->value(key + KEY_BB_RANGE_MINIMUM, minimum);
  range.setMinimum(value.toDouble());
  value = settings->value(key + KEY_BB_RANGE_MAXIMUM, maximum);
  range.setMaximum(value.toDouble());
  return settings;
}

QSettings* write(QSettings* settings, const QString& key, const Range& range) {
  settings->setValue(key + KEY_BB_RANGE_MINIMUM, range.minimum_);
  settings->setValue(key + KEY_BB_RANGE_MAXIMUM, range.maximum_);
  return settings;
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptu::Range& lhs, const gptu::Range& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptu::Range& lhs, const gptu::Range& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptu::Range& first, const gptu::Range& second) {
  return (
    first.minimum_ == second.minimum_ &&
    first.maximum_ == second.maximum_) ? 0 : 1;
}