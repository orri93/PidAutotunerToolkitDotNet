#ifndef GOS_PID_TUNING_UI_CONFIGURATION_CONTROLLER_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_CONTROLLER_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QDebug>

#include <gos/pid/ui/model/number.h>
#include <gos/pid/ui/model/ptu.h>

#define GOS_QML_TYPE_CONTROLLER_NAME "ControllerSetting"
#define GOS_QML_TYPE_CONTROLLER_URI GOS_QML_TYPE_CONTROLLER_NAME

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace configuration { class Controller; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::configuration::Controller& lhs,
  const ::gos::pid::toolkit::ui::configuration::Controller& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::configuration::Controller& lhs,
  const ::gos::pid::toolkit::ui::configuration::Controller& rhs);

int compare(
  const ::gos::pid::toolkit::ui::configuration::Controller& first,
  const ::gos::pid::toolkit::ui::configuration::Controller& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Controller : public ::gos::pid::toolkit::ui::model::Ptu {
  Q_OBJECT

  /* Controller output items */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Number* temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Number* integral READ integral WRITE setIntegral NOTIFY integralChanged)

  friend bool (::operator==) (const Controller&, const Controller&);
  friend bool (::operator!=) (const Controller&, const Controller&);
  friend int(::compare) (const Controller&, const Controller&);

public:

  explicit Controller(QObject* parent = nullptr);

  Controller(const Controller& controller);

  Controller& operator=(const Controller& controller);

  Controller& set(const Controller& controller);

  QSettings* read(QSettings* settings);
  QSettings* write(QSettings* settings);

  /* Controller output items */
  ::gos::pid::toolkit::ui::model::Number* temperature();
  ::gos::pid::toolkit::ui::model::Number* integral();

signals:
  /* Controller output items */
  void temperatureChanged();
  void integralChanged();

public slots:
  /* Controller output items */
  void setTemperature(::gos::pid::toolkit::ui::model::Number* number);
  void setIntegral(::gos::pid::toolkit::ui::model::Number* number);

protected:
  void create();

  /* Controller output items */
  ::gos::pid::toolkit::ui::model::Number temperature_;
  ::gos::pid::toolkit::ui::model::Number integral_;
};

typedef std::unique_ptr<Controller> ControllerPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
