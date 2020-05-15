#ifndef GOS_PID_TUNING_UI_CONFIGURATION_UI_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_UI_H_

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QDebug>

#include <gos/pid/ui/configuration.h>
#include <gos/pid/ui/number.h>

#define GOS_QML_TYPE_UI_NAME "Ui"
#define GOS_QML_TYPE_UI_URI GOS_QML_TYPE_UI_NAME 

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace configuration { class Ui; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::configuration::Ui& lhs,
  const ::gos::pid::toolkit::ui::configuration::Ui& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::configuration::Ui& lhs,
  const ::gos::pid::toolkit::ui::configuration::Ui& rhs);

int compare(
  const ::gos::pid::toolkit::ui::configuration::Ui& first,
  const ::gos::pid::toolkit::ui::configuration::Ui& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Ui : public ::gos::pid::toolkit::ui::configuration::Base {
  Q_OBJECT

  /* Controller input items */
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* setpoint READ setpoint WRITE setSetpoint NOTIFY setpointChanged)

  /* Controller output items */
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* integral READ integral WRITE setIntegral NOTIFY integralChanged)

  /* PID configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* kp READ kp WRITE setKp NOTIFY kpChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* ki READ ki WRITE setKi NOTIFY kiChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* kd READ kd WRITE setKd NOTIFY kdChanged)

  /* Tuning configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::Range* kpTuning READ kpTuning WRITE setKpTuning NOTIFY kpTuningChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::Range* kiTuning READ kiTuning WRITE setKiTuning NOTIFY kiTuningChanged)

  /* Evaluation configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* factor READ factor WRITE setFactor NOTIFY factorChanged)

  /* Other UI configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* sd READ sd WRITE setSd NOTIFY sdChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::Number* chart READ chart WRITE setChart NOTIFY chartChanged)

  friend bool(::operator==) (const Ui&, const Ui&);
  friend bool(::operator!=) (const Ui&, const Ui&);
  friend int(::compare) (const Ui&, const Ui&);

public:

  explicit Ui(QObject* parent = nullptr);

  Ui(const Ui& ui);

  Ui& operator=(const Ui& ui);

  Ui& set(const Ui& ui);

  QSettings* read(QSettings* settings);
  QSettings* write(QSettings* settings);

  /* Controller input items */
  ::gos::pid::toolkit::ui::Number* setpoint();

  /* Controller output items */
  ::gos::pid::toolkit::ui::Number* temperature();
  ::gos::pid::toolkit::ui::Number* integral();

  /* PID configuration */
  ::gos::pid::toolkit::ui::Number* kp();
  ::gos::pid::toolkit::ui::Number* ki();
  ::gos::pid::toolkit::ui::Number* kd();

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::Range* kpTuning();
  ::gos::pid::toolkit::ui::Range* kiTuning();

  /* Evaluation configuration */
  ::gos::pid::toolkit::ui::Number* factor();

  /* Other UI configuration */
  ::gos::pid::toolkit::ui::Number* sd();
  ::gos::pid::toolkit::ui::Number* chart();

signals:
  /* Controller input items */
  void setpointChanged();

  /* Controller output items */
  void temperatureChanged();
  void integralChanged();

  /* PID configuration */
  void kpChanged();
  void kiChanged();
  void kdChanged();

  /* Tuning configuration */
  void kpTuningChanged();
  void kiTuningChanged();

  /* Evaluation configuration */
  void factorChanged();

  /* Other UI configuration */
  void sdChanged();
  void chartChanged();

public slots:
  /* Controller input items */
  void setSetpoint(::gos::pid::toolkit::ui::Number* number);

  /* Controller output items */
  void setTemperature(::gos::pid::toolkit::ui::Number* number);
  void setIntegral(::gos::pid::toolkit::ui::Number* number);

  /* PID configuration */
  void setKp(::gos::pid::toolkit::ui::Number* number);
  void setKi(::gos::pid::toolkit::ui::Number* number);
  void setKd(::gos::pid::toolkit::ui::Number* number);

  /* Tuning configuration */
  void setKpTuning(::gos::pid::toolkit::ui::Range* range);
  void setKiTuning(::gos::pid::toolkit::ui::Range* range);

  /* Evaluation configuration */
  void setFactor(::gos::pid::toolkit::ui::Number* number);

  /* Other UI configuration */
  void setSd(::gos::pid::toolkit::ui::Number* number);
  void setChart(::gos::pid::toolkit::ui::Number* number);

protected:
  void create();

  /* Controller input items */
  ::gos::pid::toolkit::ui::Number setpoint_;

  /* Controller output items */
  ::gos::pid::toolkit::ui::Number temperature_;
  ::gos::pid::toolkit::ui::Number integral_;

  /* PID configuration */
  ::gos::pid::toolkit::ui::Number kp_;
  ::gos::pid::toolkit::ui::Number ki_;
  ::gos::pid::toolkit::ui::Number kd_;

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::Range kpTuning_;
  ::gos::pid::toolkit::ui::Range kiTuning_;

  /* Evaluation configuration */
  ::gos::pid::toolkit::ui::Number factor_;

  /* Other UI configuration */  
  ::gos::pid::toolkit::ui::Number sd_;
  ::gos::pid::toolkit::ui::Number chart_;
};

typedef std::unique_ptr<Ui> UiPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
