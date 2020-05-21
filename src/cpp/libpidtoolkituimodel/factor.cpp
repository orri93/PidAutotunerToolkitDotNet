#include <gos/pid/ui/model/factor.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Factor::Factor(QObject* parent) :
  Ptu(parent),
  isIncluded_(false),
  value_(0.0),
  operation_(Operation::Enum::Undefined),
  isReverse_(false),
  reverse_(0.0) {
}

Factor::Factor(
  const bool& isIncluded,
  const double& value,
  const Operation::Enum& operation,
  const bool& isReverse,
  const double& reverse,
  QObject* parent) :
  Ptu(parent),
  isIncluded_(isIncluded),
  value_(value),
  operation_(operation),
  isReverse_(isReverse),
  reverse_(reverse) {
}

Factor::Factor(const Factor& factor) :
  isIncluded_(factor.isIncluded_),
  value_(factor.value_),
  operation_(factor.operation_),
  isReverse_(factor.isReverse_),
  reverse_(factor.reverse_) {
}

Factor& Factor::operator=(const Factor& factor) {
  return set(factor);
}

Factor& Factor::set(const Factor& factor) {
  if (this != &factor) {
    this->isIncluded_ = factor.isIncluded_;
    this->value_ = factor.value_;
    this->operation_ = factor.operation_;
    this->isReverse_ = factor.isReverse_;
    this->reverse_ = factor.reverse_;
  }
  return *this;
}

void Factor::setIsIncluded(const bool& value) {
  if (isIncluded_ != value) {
    isIncluded_ = value;
    emit isIncludedChanged();
  }
}
void Factor::setValue(const double& value) {
  if (value_ != value) {
    value_ = value;
    emit valueChanged();
  }
}
void Factor::setOperation(const Operation::Enum& value) {
  if (operation_ != value) {
    operation_ = value;
    emit operationChanged();
  }
}
void Factor::setIsReverse(const bool& value) {
  if (isReverse_ != value) {
    isReverse_ = value;
    emit isReverseChanged();
  }
}
void Factor::setReverse(const double& value) {
  if (reverse_ != value) {
    reverse_ = value;
    emit reverseChanged();
  }
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Factor& factor) {
  Factor default = make_factor(
    DEFAULT_BB_FACTOR_IS_INCLUDED,
    DEFAULT_BB_FACTOR_VALUE,
    Operation::Enum::Add,
    DEFAULT_BB_FACTOR_IS_REVERSE,
    DEFAULT_BB_FACTOR_REVERSE);
  return read(settings, key, factor, default);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Factor& factor,
  const Factor& default) {
  QVariant value;
  gptum::Operation::EnumerateModel& enumeratemodel =
    gptum::Operation::enumerateModel();
  value = settings->value(key + KEY_BB_FACTOR_IS_INCLUDED, default.isIncluded_);
  factor.setIsIncluded(value.toBool());
  value = settings->value(key + KEY_BB_FACTOR_VALUE, default.value_);
  factor.setValue(value.toDouble());
  QString defaulttext = enumeratemodel.toString(default.operation_);
  value = settings->value(key + KEY_BB_FACTOR_OPERATION, defaulttext);
  Operation::Enum operation = enumeratemodel.parse(value.toString());
  factor.setOperation(operation);
  value = settings->value(key + KEY_BB_FACTOR_IS_REVERSE, default.isReverse_);
  factor.setIsReverse(value.toBool());
  value = settings->value(key + KEY_BB_FACTOR_REVERSE, default.reverse_);
  factor.setReverse(value.toDouble());
  return settings;
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Factor& factor) {
  gptum::Operation::EnumerateModel& enumeratemodel =
    gptum::Operation::enumerateModel();
  settings->setValue(key + KEY_BB_FACTOR_IS_INCLUDED, factor.isIncluded_);
  settings->setValue(key + KEY_BB_FACTOR_VALUE, factor.value_);
  QString operationtext = enumeratemodel.toString(factor.operation_);
  settings->setValue(key + KEY_BB_FACTOR_OPERATION, operationtext);
  settings->setValue(key + KEY_BB_FACTOR_IS_REVERSE, factor.isReverse_);
  settings->setValue(key + KEY_BB_FACTOR_REVERSE, factor.isIncluded_);
  return settings;
}

Factor make_factor(
  const bool& isIncluded,
  const double& value,
  const Operation::Enum& operation,
  const bool& isReverse,
  const double& reverse) {
  return Factor(isIncluded, value, operation, isReverse, reverse);
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptum::Factor& lhs, const gptum::Factor& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptum::Factor& lhs, const gptum::Factor& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptum::Factor& first, const gptum::Factor& second) {
  return(
    first.isIncluded_ == second.isIncluded_ &&
    first.value_ == second.value_ &&
    first.operation_ == second.operation_ &&
    first.isReverse_ == second.isReverse_ &&
    first.reverse_ == second.reverse_) ? 0 : 1;
}
