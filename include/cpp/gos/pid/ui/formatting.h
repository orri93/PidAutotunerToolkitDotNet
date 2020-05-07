#ifndef GOS_PID_TUNING_UI_LIB_FORMATTING_H_
#define GOS_PID_TUNING_UI_LIB_FORMATTING_H_

#include <QString>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace formatting {

namespace real {
QString format(const float& real, const int& precision = 4);
float parse(const QString& string);
}


} // namespace formatting
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif

