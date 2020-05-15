#include <gos/pid/ui/number.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Number::Number(QObject* parent) :
  gptu::Range(parent),
  isLimit_(true),
  precision_(0),
  stepSize_(1.0) {
}

Number::Number(const bool& isLimit, QObject* parent) :
  gptu::Range(parent),
  isLimit_(isLimit),
  precision_(0),
  stepSize_(1.0) {
}

Number::Number(
  const double& minimum,
  const double& maximum,
  const int& precision,
  const double& stepSize,
  QObject* parent) :
  gptu::Range(minimum, maximum, parent),
  isLimit_(true),
  precision_(precision),
  stepSize_(stepSize) {
}

Number::Number(
  const int& precision,
  const double& stepSize,
  QObject* parent) :
  gptu::Range(parent),
  isLimit_(false),
  precision_(precision),
  stepSize_(stepSize) {
}


Number::Number(const Number& number) :
  gptu::Range(number),
  isLimit_(number.isLimit_),
  precision_(number.precision_),
  stepSize_(number.stepSize_) {
}

Number& Number::operator=(const Number& number) {
  return set(number);
}

Number& Number::set(const Number& number) {
  if (this != &number) {
    Range::set(number);
    isLimit_ = number.isLimit_;
    setPrecision(number.precision_);
    setStepSize(number.stepSize_);
  }
  return *this;
}

void Number::set(
  const double& minimum,
  const double& maximum,
  const int& precision,
  const double& stepSize) {
  Range::set(minimum, maximum);
  setIsLimit(true);
  setPrecision(precision);
  setStepSize(stepSize);
}

void Number::set(
  const int& precision,
  const double& stepSize) {
  setIsLimit(false);
  setPrecision(precision);
  setStepSize(stepSize);
}

const bool& Number::isLimit() const { return isLimit_; }

const int& Number::precision() const {
  return precision_;
}
const double& Number::stepSize() const {
  return stepSize_;
}

void Number::setPrecision(const int& value) {
  if (precision_ != value) {
    precision_ = value;
    emit precisionChanged();
  }
}
void Number::setStepSize(const double& value) {
  if (stepSize_ != value) {
    stepSize_ = value;
    emit stepSizeChanged();
  }
}

void Number::setIsLimit(const bool& value) {
  if (isLimit_ != value) {
    isLimit_ = value;
    emit isLimitChanged();
  }
}

Number make_number(
  const double& minimum,
  const double& maximum,
  const int& precision,
  const double& stepSize) {
  return Number(minimum, maximum, precision, stepSize);
}

Number make_number(
  const int& precision,
  const double& stepSize) {
  return Number(precision, stepSize);
}

QSettings* read(QSettings* settings, const QString& key, Number& number) {
  return read(
    settings,
    key,
    number,
    DEFAULT_BB_RANGE_MINIMUM,
    DEFAULT_BB_RANGE_MAXIMUM,
    DEFAULT_BB_NUMBER_PRECISION,
    DEFAULT_BB_NUMBER_STEP_SIZE);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& number,
  const double& minimum,
  const double& maximum,
  const int& precision,
  const double& stepSize) {
  QVariant value;
  settings = read(settings, key, dynamic_cast<Range&>(number), minimum, maximum);
  value = settings->value(key + KEY_BB_NUMBER_PRECISION, precision);
  number.setPrecision(value.toInt());
  value = settings->value(key + KEY_BB_NUMBER_STEP_SIZE, stepSize);
  number.setStepSize(value.toDouble());
  number.setIsLimit(true);
  return settings;
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Number& number,
  const int& precision,
  const double& stepSize) {
  QVariant value;
  value = settings->value(key + KEY_BB_NUMBER_PRECISION, precision);
  number.setPrecision(value.toInt());
  value = settings->value(key + KEY_BB_NUMBER_STEP_SIZE, stepSize);
  number.setStepSize(value.toDouble());
  number.setIsLimit(false);
  return settings;
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Number& number) {
  if (number.isLimit_) {
    settings = write(settings, key, dynamic_cast<const Range&>(number));
  }
  settings->setValue(key + KEY_BB_NUMBER_PRECISION, number.precision_);
  settings->setValue(key + KEY_BB_NUMBER_STEP_SIZE, number.stepSize_);
  return settings;
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptu::Number& lhs, const gptu::Number& rhs) {
  return compare(lhs, rhs) == 0;
}

bool operator!=(const gptu::Number& lhs, const gptu::Number& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptu::Number& first, const gptu::Number& second) {
  return (
    compare(
      dynamic_cast<const gptu::Range&>(first),
      dynamic_cast<const gptu::Range&>(second)) &&
    first.precision_ == second.precision_ &&
    first.stepSize_ == second.stepSize_) ? 0 : 1;
}