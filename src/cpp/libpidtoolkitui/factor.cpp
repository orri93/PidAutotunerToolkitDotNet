#include <gos/pid/ui/factor.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;
namespace gptumo = ::gos::pid::toolkit::ui::model::operation;
namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Factor::Factor(QObject* parent) :
  gptuc::Base(parent),
  isIncluded_(false),
  value_(0.0),
  operation_(gptut::operation::undefined),
  isReverse_(false),
  reverse_(0.0) {
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

const bool& Factor::isIncluded() const {
  return isIncluded_;
}
const double& Factor::value() const {
  return value_;
}
const gptut::operation& Factor::operation() const {
  return operation_;
}
const int Factor::operationIndex() const {
  return gptumo::index(operation_);
}
const bool& Factor::isReverse() const {
  return isReverse_;
}
const double& Factor::reverse() const {
  return reverse_;
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
void Factor::setOperation(const gptut::operation& value) {
  if (operation_ != value) {
    operation_ = value;
    emit operationIndexChanged();
  }
}
void Factor::setOperationIndex(const int& value) {
  setOperation(gptumo::operation(value));
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

QSettings* read(QSettings* settings, const QString& key, Factor& factor) {

  QVariant value;

  value = settings->value(
    key + KEY_BB_FACTOR_IS_INCLUDED,
    DEFAULT_BB_FACTOR_IS_INCLUDED);
  factor.setIsIncluded(value.toBool());
  value = settings->value(
    key + KEY_BB_FACTOR_VALUE,
    DEFAULT_BB_FACTOR_VALUE);
  factor.setValue(value.toDouble());
  value = settings->value(
    key + KEY_BB_FACTOR_OPERATION,
    DEFAULT_BB_FACTOR_OPERATION);
  factor.setOperation(gptumo::parse(value.toString()));
  value = settings->value(
    key + KEY_BB_FACTOR_IS_REVERSE,
    DEFAULT_BB_FACTOR_IS_REVERSE);
  factor.setIsReverse(value.toBool());
  value = settings->value(
    key + KEY_BB_FACTOR_REVERSE,
    DEFAULT_BB_FACTOR_REVERSE);
  factor.setReverse(value.toDouble());

  return settings;
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Factor& factor) {
  settings->setValue(
    key + KEY_BB_FACTOR_IS_INCLUDED,
    factor.isIncluded_);
  settings->setValue(
    key + KEY_BB_FACTOR_VALUE,
    factor.value_);
  settings->setValue(
    key + KEY_BB_FACTOR_OPERATION,
    gptumo::to::string(factor.operation_));
  settings->setValue(
    key + KEY_BB_FACTOR_IS_REVERSE,
    factor.isReverse_);
  settings->setValue(
    key + KEY_BB_FACTOR_REVERSE,
    factor.isIncluded_);
  return settings;
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptu::Factor& lhs, const gptu::Factor& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptu::Factor& lhs, const gptu::Factor& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptu::Factor& first, const gptu::Factor& second) {
  return(
    first.isIncluded_ == second.isIncluded_ &&
    first.value_ == second.value_ &&
    first.operation_ == second.operation_ &&
    first.isReverse_ == second.isReverse_ &&
    first.reverse_ == second.reverse_) ? 0 : 1;
}
