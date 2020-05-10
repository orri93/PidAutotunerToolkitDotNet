#ifndef GOS_PID_TUNING_UI_CONFIGURATION_BLACK_BOX_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_BLACK_BOX_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QFileSystemWatcher>
#include <QDebug>

#include <gos/pid/tuning/blackbox.h>
#include <gos/pid/ui/configuration.h>
#include <gos/pid/ui/range.h>

#define GOS_QML_TYPE_BLACK_BOX_NAME "BlackBoxSetting"
#define GOS_QML_TYPE_BLACK_BOX_URI GOS_QML_TYPE_BLACK_BOX_NAME

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace configuration { class BlackBox; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::configuration::BlackBox& lhs,
  const ::gos::pid::toolkit::ui::configuration::BlackBox& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::configuration::BlackBox& lhs,
  const ::gos::pid::toolkit::ui::configuration::BlackBox& rhs);

int compare(
  const ::gos::pid::toolkit::ui::configuration::BlackBox& first,
  const ::gos::pid::toolkit::ui::configuration::BlackBox& second);


namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class BlackBox : public ::gos::pid::toolkit::ui::configuration::Base {
  Q_OBJECT

  /* PID configuration */
  Q_PROPERTY(double kp READ kp WRITE setKp NOTIFY kpChanged)
  Q_PROPERTY(double ki READ ki WRITE setKi NOTIFY kiChanged)
  Q_PROPERTY(double kd READ kd WRITE setKd NOTIFY kdChanged)

  /* Tuning configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::Range* kpRange READ kpRange WRITE setKpRange NOTIFY kpRangeChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::Range* kiRange READ kiRange WRITE setKiRange NOTIFY kiRangeChanged)

  /* Controller configuration  */
  Q_PROPERTY(double base READ base WRITE setBase NOTIFY baseChanged)
  Q_PROPERTY(bool isBase READ isBase WRITE setIsBase NOTIFY isBaseChanged)
  Q_PROPERTY(double setpoint READ setpoint WRITE setSetpoint NOTIFY setpointChanged)
  Q_PROPERTY(quint16 manual READ manual WRITE setManual NOTIFY manualChanged)

  /* Timers configuration */
  Q_PROPERTY(int stableDuration READ stableDuration WRITE setStableDuration NOTIFY stableDurationChanged)

  /* Logging configuration */
  Q_PROPERTY(bool internalVariables READ internalVariables WRITE setInternalVariables NOTIFY internalVariablesChanged)
  Q_PROPERTY(QString separator READ separator WRITE setSeparator NOTIFY separatorChanged)
  Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged)
  Q_PROPERTY(QString tuningFile READ tuningFile WRITE setTuningFile NOTIFY tuningFileChanged)

  /* Other configuration */
  Q_PROPERTY(int windowSize READ windowSize WRITE setWindowSize NOTIFY windowSizeChanged)
  Q_PROPERTY(double sd READ sd WRITE setSd NOTIFY sdChanged);

  friend bool (::operator==) (const BlackBox&, const BlackBox&);
  friend bool (::operator!=) (const BlackBox&, const BlackBox&);
  friend int(::compare) (const BlackBox&, const BlackBox&);

public:

  explicit BlackBox(QObject* parent = nullptr);

  BlackBox(const BlackBox& blackBox);

  BlackBox& operator=(const BlackBox& blackBox);

  QSettings* read(QSettings* settings);
  QSettings* write(QSettings* settings);

  /* PID configuration */
  const double& kp() const;
  const double& ki() const;
  const double& kd() const;

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::Range* kpRange();
  ::gos::pid::toolkit::ui::Range* kiRange();

  /* Controller configuration  */
  const double& base() const;
  const bool& isBase() const;
  const double& setpoint() const;
  const quint16& manual() const;

  /* Timers configuration */
  const int& stableDuration() const;

  /* Logging configuration */
  const bool& internalVariables() const;
  const QString& separator() const;
  const QString& file() const;
  const QString& tuningFile() const;

  /* Other configuration */
  const int& windowSize() const;
  const double& sd() const;

signals:
  /* PID configuration */
  void kpChanged();
  void kiChanged();
  void kdChanged();
  /* Tuning configuration */
  void kpRangeChanged();
  void kiRangeChanged();
  /* Controller configuration  */
  void baseChanged();
  void isBaseChanged();
  void setpointChanged();
  void manualChanged();
  /* Timers configuration */
  void stableDurationChanged();
  /* Logging configuration */
  void internalVariablesChanged();
  void separatorChanged();
  void fileChanged();
  void tuningFileChanged();
  /* Other configuration */
  void windowSizeChanged();
  void sdChanged();

public slots:
  /* PID configuration */
  void setKp(const double& value);
  void setKi(const double& value);
  void setKd(const double& value);

  /* Tuning configuration */
  void setKpRange(::gos::pid::toolkit::ui::Range* value);
  void setKiRange(::gos::pid::toolkit::ui::Range* values);
  void setKpRange(const double& minimum, const double& maximum);
  void setKiRange(const double& minimum, const double& maximum);

  /* Controller configuration  */
  void setBase(const double& value);
  void setIsBase(const bool& value);
  void setSetpoint(const double& value);
  void setManual(const quint16& value);

  /* Timers configuration */
  void setStableDuration(const int& value);

  /* Logging configuration */
  void setInternalVariables(const bool& value);
  void setSeparator(const QString&);
  void setFile(const QString&);
  void setTuningFile(const QString&);

  /* Other configuration */
  void setWindowSize(const int& value);
  void setSd(const double& value);

protected:
  void create();

  void handle(std::function<void()>& changed);
  void handle(std::function<void()>& changed, std::function<void()>& write);
  void handle(
    std::vector<std::function<void()>>& changed,
    std::function<void()>& write);

  /* PID configuration */
  double kp_;
  double ki_;
  double kd_;

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::Range kpRange_;
  ::gos::pid::toolkit::ui::Range kiRange_;

  /* Controller configuration  */
  double base_;
  bool isBase_;
  double setpoint_;
  quint16 manual_;

  /* Timers configuration */
  int stableDuration_;

  /* Logging configuration */
  bool internalVariables_;
  QString separator_;
  QString file_;
  QString tuningFile_;

  /* Other configuration */
  int windowSize_;
  double sd_;
};

typedef std::unique_ptr<BlackBox> BlackBoxPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
