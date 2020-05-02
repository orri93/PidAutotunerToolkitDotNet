#include <cmath>

#include <gos/pid/ui/fvalidator.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

FloatValidator::FloatValidator(QObject* parent) :
  QValidator(parent) {
}

QValidator::State FloatValidator::validate(QString& input, int& pos) const {
  Q_UNUSED(pos)
  if (input.isEmpty()) {
    return Acceptable;
  }
  bool ok;
  float f = input.toFloat(&ok);
  return (ok && std::isfinite(f)) ? Acceptable : Invalid;
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
