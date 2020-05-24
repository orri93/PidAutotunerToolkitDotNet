#include <gos/pid/ui/model/accuracy.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Accuracy::Accuracy(QObject* parent) :
  QObject(parent),
  number_(this),
  format_(this) {
}

Accuracy::Accuracy(
  const gptum::Number& number,
  const gptum::Format& format,
  QObject* parent) :
  number_(number),
  format_(format) {
}

Accuracy::Accuracy(
  const gptum::Format& format,
  QObject* parent) :
  format_(format) {
}

Accuracy::Accuracy(const Accuracy& accuracy) :
  number_(accuracy.number_),
  format_(accuracy.format_) {
}

Accuracy& Accuracy::operator=(const Accuracy& accuracy) {
  return set(accuracy);
}

Accuracy& Accuracy::set(const Accuracy& accuracy) {
  if (this != &accuracy) {
    setNumber(accuracy.number_);
    setFormat(accuracy.format_);
  }
  return *this;
}

void Accuracy::set(
  const gptum::Number& number,
  const gptum::Format& format) {
  setNumber(number);
  setFormat(format);
}

void Accuracy::set(const gptum::Format& format) {
  setNumber(make_number());
  setFormat(format);
}

Number* Accuracy::number() { return &number_; }
Format* Accuracy::format() { return &format_; }

void Accuracy::setNumber(const Number* number) {
  if (number != nullptr) {
    setNumber(*number);
  }
}

void Accuracy::setFormat(const Format* format) {
  if (format != nullptr) {
    setFormat(*format);
  }
}

void Accuracy::setNumber(const Number& number) {
  if (number_ != number) {
    number_ = number;
    emit numberChanged();
  }
}

void Accuracy::setFormat(const Format& format) {
  if (format_ != format) {
    format_ = format;
    emit formatChanged();
  }
}

Accuracy make_accuracy(const Number& number, const Format& format) {
  return Accuracy(number, format);
}

Accuracy make_accuracy(const Format& format) {
  return Accuracy(format);
}

QSettings* read(QSettings* settings, const QString& key, Accuracy& accuracy) {
  Accuracy default = make_accuracy(
    make_number(),
    make_format(DEFAULT_BB_ACCURACY_PRECISION));
  return read(settings, key, accuracy, default);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Accuracy& default) {
  gptum::read(
    settings,
    key + KEY_BB_ACCURACY_NUMBER,
    accuracy.number_,
    default.number_);
  gptum::read(
    settings,
    key + KEY_BB_ACCURACY_FORMAT,
    accuracy.format_,
    default.format_);
  return settings;
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Format& format) {
  Accuracy default = make_accuracy(format);
  return read(settings, key, accuracy, default);
}

QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Number& number,
  const Format& format) {
  Accuracy default = make_accuracy(number, format);
  return read(settings, key, accuracy, default);
}

QSettings* write(
  QSettings* settings,
  const QString& key,
  const Accuracy& accuracy) {
  gptum::write(settings, key + KEY_BB_ACCURACY_NUMBER, accuracy.number_);
  gptum::write(settings, key + KEY_BB_ACCURACY_FORMAT, accuracy.format_);
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
    compare(first.number_, second.number_) == 0 &&
    compare(first.format_, second.format_) == 0) ? 0 : 1;
}
