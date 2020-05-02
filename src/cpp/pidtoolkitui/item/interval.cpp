#include <item/interval.h>

namespace gptui = ::gos::pid::toolkit::ui::item;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace item {

Interval::Interval(QObject* parent) : QObject(parent), value_(0) {
}
Interval::Interval(const QString& text, const int& value, QObject* parent) :
  QObject(parent), text_(text), value_(value) {
}
Interval::Interval(const Interval& item) :
  QObject(nullptr), text_(item.text_), value_(item.value_) {
}

Interval& Interval::operator=(const Interval& item) {
  if (this != &item) {
    text_ = item.text_;
    value_ = item.value_;
  }
  return *this;
}

const QString& Interval::text() const {
  return text_;
}
const int& Interval::value() const {
  return value_;
}

void Interval::setText(const QString& text) {
  text_ = text;
}
void Interval::setValue(const int& value) {
  value_ = value;
}

} // namespace item
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptui::Interval& lhs, const gptui::Interval& rhs) {
  return lhs.text() == rhs.text() && lhs.value() == rhs.value();
}
bool operator!=(const gptui::Interval& lhs, const gptui::Interval& rhs) {
  return !(lhs == rhs);
}
QDebug operator<< (QDebug debug, gptui::Interval& item) {
  debug << "text: " << item.text() << ", value: " << item.value();
  return debug;
}
