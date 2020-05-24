#include <gos/pid/ui/model/number.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Number::Number(QObject* parent) :
  QObject(parent),
  restriction_(gptum::Restriction::Enum::None) {
}

Number::Number(
  const gptum::Restriction::Enum& restriction,
  const Range& range,
  QObject* parent) :
  QObject(parent),
  restriction_(restriction),
  range_(range) {
}

Number::Number(const double& from, const double& to, QObject* parent) :
  QObject(parent),
  restriction_(gptum::Restriction::Enum::None),
  range_(from, to) {
}

Number::Number(const Number& number) :
  restriction_(number.restriction_),
  range_(number.range_) {
}

Number& Number::operator=(const Number& number) {
  return set(number);
}

Number& Number::set(const Number& number) {
  if (this != &number) {
    setRestriction(number.restriction_);
    setRange(number.range_);
  }
  return *this;
}

void Number::set(
  const gptum::Restriction::Enum& restriction,
  const Range& range) {
  setRestriction(restriction);
  setRange(range);
}

Range* Number::range() { return &range_; }

void Number::setRange(const Range* value) {
  if (value != nullptr) {
    setRange(*value);
  }
}

void Number::setRange(const Range& value) {
  if (range_ != value) {
    range_ = value;
    emit rangeChanged();
  }
}


void Number::setRestriction(const gptum::Restriction::Enum& value) {
  if (restriction_ != value) {
    restriction_ = value;
    emit restrictionChanged();
  }
}

Number make_number() {
  return Number();
}

Number make_number(
  const gptum::Restriction::Enum& restriction,
  const Range& range) {
  return Number(restriction, range);
}

Number make_number(
  const double& from,
  const double& to) {
  return Number(from, to);
}


QSettings* read(QSettings* settings, const QString& key, Number& number) {
  Number default = make_number(
    gptum::Restriction::Enum::None,
    Range());
  return read(settings, key, number, default);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& number,
  const Number& default) {
  QVariant value;
  gptum::Restriction::EnumerateModel& enumeratemodel =
    gptum::Restriction::enumerateModel();
  QString defaulttext = enumeratemodel.toString(default.restriction_);
  value = settings->value(key + KEY_BB_NUMBER_RESTRICTION, defaulttext);
  gptum::Restriction::Enum restriction = enumeratemodel.parse(value.toString());
  number.setRestriction(restriction);
  settings = gptum::read(
    settings,
    key + KEY_BB_NUMBER_RANGE,
    number.range_,
    default.range_);
  return settings;
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Number& number) {
  gptum::Restriction::EnumerateModel& enumeratemodel =
    gptum::Restriction::enumerateModel();
  settings->setValue(
    key + KEY_BB_NUMBER_RESTRICTION,
    enumeratemodel.toString(number.restriction_));
  write(settings, key + KEY_BB_NUMBER_RANGE, number.range_);
  return settings;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptum::Number& lhs, const gptum::Number& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptum::Number& lhs, const gptum::Number& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptum::Number& first, const gptum::Number& second) {
  return (
    compare(first.range_, second.range_) == 0 &&
    first.restriction_ == second.restriction_) ? 0 : 1;
}
