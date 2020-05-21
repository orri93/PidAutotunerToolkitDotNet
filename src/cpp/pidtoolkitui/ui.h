#ifndef GOS_PID_TUNING_UI_CONFIGURATION_UI_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_UI_H_

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QDebug>

#include <gos/pid/ui/model/ptu.h>
#include <gos/pid/ui/model/models.h>

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

class Ui : public ::gos::pid::toolkit::ui::model::Ptu {
  Q_OBJECT

  /* Controller input items */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* setpoint READ setpoint WRITE setSetpoint NOTIFY setpointChanged)

  /* Controller output items */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Format* temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Format* integral READ integral WRITE setIntegral NOTIFY integralChanged)

  /* PID configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* kp READ kp WRITE setKp NOTIFY kpChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* ki READ ki WRITE setKi NOTIFY kiChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* kd READ kd WRITE setKd NOTIFY kdChanged)

  /* Tuning configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Range* kpTuning READ kpTuning WRITE setKpTuning NOTIFY kpTuningChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Range* kiTuning READ kiTuning WRITE setKiTuning NOTIFY kiTuningChanged)

  /* Evaluation configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* factor READ factor WRITE setFactor NOTIFY factorChanged)

  /* Other UI configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* sd READ sd WRITE setSd NOTIFY sdChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Accuracy* chart READ chart WRITE setChart NOTIFY chartChanged)

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
  ::gos::pid::toolkit::ui::model::Accuracy* setpoint();

  /* Controller output items */
  ::gos::pid::toolkit::ui::model::Format* temperature();
  ::gos::pid::toolkit::ui::model::Format* integral();

  /* PID configuration */
  ::gos::pid::toolkit::ui::model::Accuracy* kp();
  ::gos::pid::toolkit::ui::model::Accuracy* ki();
  ::gos::pid::toolkit::ui::model::Accuracy* kd();

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::model::Range* kpTuning();
  ::gos::pid::toolkit::ui::model::Range* kiTuning();

  /* Evaluation configuration */
  ::gos::pid::toolkit::ui::model::Accuracy* factor();

  /* Other UI configuration */
  ::gos::pid::toolkit::ui::model::Accuracy* sd();
  ::gos::pid::toolkit::ui::model::Accuracy* chart();

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
  void setSetpoint(::gos::pid::toolkit::ui::model::Accuracy* accuracy);

  /* Controller output items */
  void setTemperature(::gos::pid::toolkit::ui::model::Format* format);
  void setIntegral(::gos::pid::toolkit::ui::model::Format* format);

  /* PID configuration */
  void setKp(::gos::pid::toolkit::ui::model::Accuracy* accuracy);
  void setKi(::gos::pid::toolkit::ui::model::Accuracy* accuracy);
  void setKd(::gos::pid::toolkit::ui::model::Accuracy* accuracy);

  /* Tuning configuration */
  void setKpTuning(::gos::pid::toolkit::ui::model::Range* range);
  void setKiTuning(::gos::pid::toolkit::ui::model::Range* range);

  /* Evaluation configuration */
  void setFactor(::gos::pid::toolkit::ui::model::Accuracy* accuracy);

  /* Other UI configuration */
  void setSd(::gos::pid::toolkit::ui::model::Accuracy* accuracy);
  void setChart(::gos::pid::toolkit::ui::model::Accuracy* accuracy);

protected:
  void create();

  /* Controller input items */
  ::gos::pid::toolkit::ui::model::Accuracy setpoint_;

  /* Controller output items */
  ::gos::pid::toolkit::ui::model::Format temperature_;
  ::gos::pid::toolkit::ui::model::Format integral_;

  /* PID configuration */
  ::gos::pid::toolkit::ui::model::Accuracy kp_;
  ::gos::pid::toolkit::ui::model::Accuracy ki_;
  ::gos::pid::toolkit::ui::model::Accuracy kd_;

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::model::Range kpTuning_;
  ::gos::pid::toolkit::ui::model::Range kiTuning_;

  /* Evaluation configuration */
  ::gos::pid::toolkit::ui::model::Accuracy factor_;

  /* Other UI configuration */  
  ::gos::pid::toolkit::ui::model::Accuracy sd_;
  ::gos::pid::toolkit::ui::model::Accuracy chart_;
};

typedef std::unique_ptr<Ui> UiPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
