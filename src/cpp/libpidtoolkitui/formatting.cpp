#include <sstream>
#include <iomanip>

#include <gos/pid/ui/formatting.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace formatting {

namespace real {
QString format(const float& real, const int& precision) {
  std::stringstream stream;
  stream << std::setprecision(precision) << real;
  return QString::fromStdString(stream.str());
}
float parse(const QString& string) {
  return static_cast<float>(string.toDouble());
}
} // namespace real

} // namespace formatting
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos