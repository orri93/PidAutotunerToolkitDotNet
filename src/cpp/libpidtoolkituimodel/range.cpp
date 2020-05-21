#include <gos/pid/ui/model/range.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Range::Range(QObject* parent) :
  Ptu(parent),
  from_(0.0),
  to_(10.0) {
}

Range::Range(const double& from, const double& to, QObject* parent) :
  Ptu(parent),
  from_(from),
  to_(to) {
}

Range::Range(const Range& range) :
  from_(range.from_),
  to_(range.to_) {
}

Range& Range::operator=(const Range& range) {
  return set(range);
}

Range& Range::set(const Range& range) {
  if (this != &range) {
    setFrom(range.from_);
    setTo(range.to_);
  }
  return *this;
}

void Range::set(const double& from, const double& to) {
  setFrom(from);
  setTo(to);
}

const double& Range::from() const { return from_; }
const double& Range::to() const { return to_; }

void Range::setFrom(const double& value) {
  if (from_ != value) {
    from_ = value;
    emit fromChanged();
  }
}
void Range::setTo(const double& value) {
  if (to_ != value) {
    to_ = value;
    emit toChanged();
  }
}

Range make_range(const double& from, const double& to) {
  return Range(from, to);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Range& range,
  const Range& default) {
  return read(settings, key, range, default.from_, default.to_);
}

QSettings* read(
  QSettings * settings,
  const QString & key,
  Range & range,
  const double& from,
  const double& to) {
  QVariant value;
  value = settings->value(key + KEY_BB_RANGE_FROM, from);
  range.setFrom(value.toDouble());
  value = settings->value(key + KEY_BB_RANGE_TO, to);
  range.setTo(value.toDouble());
  return settings;
}

QSettings* write(QSettings* settings, const QString& key, const Range& range) {
  settings->setValue(key + KEY_BB_RANGE_FROM, range.from_);
  settings->setValue(key + KEY_BB_RANGE_TO, range.to_);
  return settings;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptum::Range& lhs, const gptum::Range& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptum::Range& lhs, const gptum::Range& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptum::Range& first, const gptum::Range& second) {
  return (
    first.from_ == second.from_ &&
    first.to_ == second.to_) ? 0 : 1;
}
