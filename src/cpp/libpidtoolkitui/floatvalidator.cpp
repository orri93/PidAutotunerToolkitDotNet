#include <cmath>

#include <gos/pid/ui/floatvalidator.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace validator {

Float::Float(QObject* parent) :
  QValidator(parent) {
}

QValidator::State Float::validate(QString& input, int& pos) const {
  Q_UNUSED(pos)
  if (input.isEmpty()) {
    return Acceptable;
  }
  bool ok;
  float f = input.toFloat(&ok);
  return (ok && std::isfinite(f)) ? Acceptable : Invalid;
}

} // namespace validator
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
