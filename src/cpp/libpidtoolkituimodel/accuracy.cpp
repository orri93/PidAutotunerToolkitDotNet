#include <gos/pid/ui/model/accuracy.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Accuracy::Accuracy(QObject* parent) :
  Format(parent),
  restriction_(gptum::Restriction::Enum::Undefined) {
}

Accuracy::Accuracy(
  const gptum::Restriction::Enum& restriction,
  const Range& range,
  const int& precision,
  QObject* parent) :
  Format(precision, parent),
  restriction_(restriction),
  range_(range) {
}

Accuracy::Accuracy(
  const int& precision,
  QObject* parent) :
  Format(precision, parent),
  restriction_(gptum::Restriction::Enum::None) {
}


Accuracy::Accuracy(const Accuracy& accuracy) :
  Format(accuracy),
  restriction_(accuracy.restriction_),
  range_(accuracy.range_) {
}

Accuracy& Accuracy::operator=(const Accuracy& accuracy) {
  return set(accuracy);
}

Accuracy& Accuracy::set(const Accuracy& accuracy) {
  if (this != &accuracy) {
    Format::set(dynamic_cast<const Format&>(accuracy));
    setRestriction(accuracy.restriction_);
    setRange(accuracy.range_);
  }
  return *this;
}

void Accuracy::set(
  const gptum::Restriction::Enum& restriction,
  const Range& range,
  const int& precision) {
  setRestriction(restriction);
  setRange(range);
  setPrecision(precision);
}

void Accuracy::set(const int& precision) {
  setRestriction(gptum::Restriction::Enum::None);
  Format::set(precision);
}

Range* Accuracy::range() { return &range_; }

void Accuracy::setRange(const Range* value) {
  if (value != nullptr) {
    setRange(*value);
  }
}

void Accuracy::setRange(const Range& value) {
  if (range_ != value) {
    range_ = value;
    emit rangeChanged();
  }
}


void Accuracy::setRestriction(const gptum::Restriction::Enum& value) {
  if (restriction_ != value) {
    restriction_ = value;
    emit restrictionChanged();
  }
}

Accuracy make_accuracy(
  const gptum::Restriction::Enum& restriction,
  const Range& range,
  const int& precision) {
  return Accuracy(restriction, range, precision);
}

Accuracy make_accuracy(const int& precision) {
  return Accuracy(precision);
}

QSettings* read(QSettings* settings, const QString& key, Accuracy& accuracy) {
  Accuracy default = make_accuracy(
    gptum::Restriction::Enum::None,
    Range(),
    DEFAULT_BB_ACCURACY_PRECISION);
  return read(settings, key, accuracy, default);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Accuracy& default) {
  QVariant value;
  gptum::Restriction::EnumerateModel& enumeratemodel =
    gptum::Restriction::enumerateModel();
  QString defaulttext = enumeratemodel.toString(default.restriction_);
  value = settings->value(key + KEY_BB_ACCURACY_RESTRICTION, defaulttext);
  gptum::Restriction::Enum restriction = enumeratemodel.parse(value.toString());
  accuracy.setRestriction(restriction);
  settings = gptum::read(
    settings,
    key + KEY_BB_ACCURACY_RANGE,
    accuracy.range_,
    default.range_);
  settings = gptum::read(
    settings,
    key,
    dynamic_cast<Format&>(accuracy),
    default.precision_);
  return settings;
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const int& precision) {
  Accuracy default = make_accuracy(
    gptum::Restriction::Enum::None,
    Range(),
    precision);
  return read(settings, key, accuracy, default);
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Accuracy& accuracy) {
  gptum::Restriction::EnumerateModel& enumeratemodel =
    gptum::Restriction::enumerateModel();
  settings->setValue(
    key + KEY_BB_ACCURACY_RESTRICTION,
    enumeratemodel.toString(accuracy.restriction_));
  write(settings, key + KEY_BB_ACCURACY_RANGE, accuracy.range_);
  write(settings, key, dynamic_cast<const Format&>(accuracy));
  return settings;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptum::Accuracy& lhs, const gptum::Accuracy& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptum::Accuracy& lhs, const gptum::Accuracy& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptum::Accuracy& first, const gptum::Accuracy& second) {
  return (
    compare(
      dynamic_cast<const gptum::Format&>(first),
      dynamic_cast<const gptum::Format&>(second)) == 0 &&
    compare(first.range_, second.range_) == 0 &&
    first.restriction_ == second.restriction_) ? 0 : 1;
}