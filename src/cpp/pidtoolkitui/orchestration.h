#ifndef GOS_PID_TUNING_UI_ORCHESTRATION_H_
#define GOS_PID_TUNING_UI_ORCHESTRATION_H_

#include <memory>

#include <QTimer>
#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtQml/QQmlContext>

#include <gos/pid/arduino/types.h>

#include <gos/pid/tuning/types.h>

#include <configuration.h>

#include <items.h>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Orchestration : public Items {
  Q_OBJECT
public:
  explicit Orchestration(QQuickView& appViewer, QObject* parent = nullptr);
  ~Orchestration();

  Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)
  Q_PROPERTY(bool isLogging READ isLogging NOTIFY isLoggingChanged)
  Q_PROPERTY(QString statusString READ statusString NOTIFY statusStringChanged)
  Q_PROPERTY(QString lastErrorString READ lastErrorString NOTIFY lastErrorStringChanged)
  Q_PROPERTY(errno_t lastErrorNumber READ lastErrorNumber NOTIFY lastErrorNumberChanged)
  Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
  Q_PROPERTY(int intervalIndex READ intervalIndex WRITE setIntervalIndex)
  Q_PROPERTY(bool applyIntervalToController READ applyIntervalToController WRITE setApplyIntervalToController)
  Q_PROPERTY(int manual READ manual WRITE setManual NOTIFY manualChanged)
  Q_PROPERTY(double setpoint READ setpoint WRITE setSetpoint NOTIFY setpointChanged)
  Q_PROPERTY(float kp READ kp WRITE setKp NOTIFY kpChanged)
  Q_PROPERTY(float ki READ ki WRITE setKi NOTIFY kiChanged)
  Q_PROPERTY(float kd READ kd WRITE setKd NOTIFY kdChanged)
  Q_PROPERTY(QString kpText READ kpText WRITE setKpText NOTIFY kpTextChanged)
  Q_PROPERTY(QString kiText READ kiText WRITE setKiText NOTIFY kiTextChanged)
  Q_PROPERTY(QString kdText READ kdText WRITE setKdText NOTIFY kdTextChanged)
  Q_PROPERTY(int force READ force WRITE setForce NOTIFY forceChanged)
  Q_PROPERTY(int forceIndex READ forceIndex WRITE setForceIndex)
  Q_PROPERTY(float integral READ integral NOTIFY integralChanged)
  Q_PROPERTY(QString integralText READ integralText NOTIFY integralTextChanged)
  Q_PROPERTY(::gos::pid::tuning::types::TuningMode tuning READ tuning WRITE setTuning NOTIFY tuningChanged)
  Q_PROPERTY(int tuningIndex READ tuningIndex WRITE setTuningIndex)

  bool initialize();

  Q_INVOKABLE int update(
    QAbstractSeries* output,
    QAbstractSeries* temperature,
    QAbstractSeries* setpoints);
  Q_INVOKABLE bool connectDisconnect();
  Q_INVOKABLE bool startStopLogging();
  Q_INVOKABLE void panelCompleted();

  const bool& isConnected() const;
  const bool isLogging() const;
  const QString& statusString() const;
  const QString& lastErrorString() const;
  const errno_t& lastErrorNumber() const;
  const int intervalIndex() const;
  const int& manual() const;
  const double& setpoint() const;
  const float& kp() const;
  const float& ki() const;
  const float& kd() const;
  const QString kpText() const;
  const QString kiText() const;
  const QString kdText() const;
  const int& force() const;
  const int forceIndex() const;
  const float& integral() const;
  const QString integralText() const;
  const int tuningIndex() const;

signals:
  /* Communication configuration */
  void isConnectedChanged();
  void isLoggingChanged();
  void statusStringChanged();
  void lastErrorStringChanged();
  void lastErrorNumberChanged();
  void intervalChanged();
  void manualChanged();
  void setpointChanged();
  void kpChanged();
  void kiChanged();
  void kdChanged();
  void kpTextChanged();
  void kiTextChanged();
  void kdTextChanged();
  void forceChanged();
  void integralChanged();
  void integralTextChanged();
  void tuningChanged();

Q_SIGNALS:
//  void quit();
//  void exit(int retCode);

public Q_SLOTS:
//  bool close();

public slots:
  void setInterval(const int& value);
  void setIntervalIndex(const int& value);
  void setApplyIntervalToController(const bool& value);
  void setManual(const int& value);
  void setSetpoint(const double& value);
  void setKp(const float& value);
  void setKi(const float& value);
  void setKd(const float& value);
  void setKpText(const QString& value);
  void setKiText(const QString& value);
  void setKdText(const QString& value);
  void setForce(const int& value);
  void setForceIndex(const int& value);
  void setTuning(const ::gos::pid::tuning::types::TuningMode& value);
  void setTuningIndex(const int& value);

private slots:
  void onCommunicationConfigurationChanged();
  void onModbusConfigurationChanged();
  void onTimersConfigurationChanged();
  void onTuningConfigurationChanged();

private:
  typedef QVector<QPointF> VectorList;
  typedef std::unique_ptr<Configuration> ConfigurationPointer;

  void applyConfiguration();
  void connectConfiguration();

  void setIntegral(const float& value);

  bool writeManual(const ::gos::pid::arduino::types::Unsigned& manual);
  bool writeSetpoint(const ::gos::pid::arduino::types::Real& setpoint);
  bool writeKp(const ::gos::pid::arduino::types::Real& kp);
  bool writeKi(const ::gos::pid::arduino::types::Real& ki);
  bool writeKd(const ::gos::pid::arduino::types::Real& kd);
  bool writeForce(const ::gos::pid::arduino::types::Unsigned& force);

  void setIsConnected(const bool& value);
//void setIsLogging(const bool& value);
  void setStatusString(const QString& value);
  void setLastErrorString(const QString& value);
  void setLastErrorNumber(const errno_t& value);

  QQuickView& appViewer_;
  VectorList setpoints_;
  VectorList temperature_;
  VectorList outputs_;
  int count_;

  ConfigurationPointer configuration_;

  bool ispanelcompleted_;

  bool isConnected_;
  QString statusString_;
  QString lastErrorString_;
  errno_t lastErrorNumber_;
  int manual_;
  double setpoint_;
  float kp_;
  float ki_;
  float kd_;
  int force_;
  float integral_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
