#ifndef GOS_PID_TUNING_UI_ORCHESTRATION_H_
#define GOS_PID_TUNING_UI_ORCHESTRATION_H_

#include <memory>

#include <QTimer>
#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtQml/QQmlContext>

#include <gos/pid/arduino/types.h>

#include <gos/pid/tuning/types.h>
#include <gos/pid/tuning/blackbox.h>
#include <gos/pid/tuning/notify.h>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/items.h>

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

namespace orchestration {
bool create(QQmlContext& context);
}

class Orchestration : public Items, public virtual ::gos::pid::tuning::Nofity {
  Q_OBJECT
public:
  explicit Orchestration(QQmlContext& context, QObject* parent = nullptr);
  ~Orchestration();

  Q_PROPERTY(QString configurationModeText READ configurationModeText NOTIFY configurationModeTextChanged)

  /* Configuration Access */
  Q_PROPERTY(Configuration* configuration READ configuration)
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::BlackBox* blackBox READ blackBox NOTIFY blackBoxChanged)

  /* Communication items */
  Q_PROPERTY(QString serialPort READ serialPort NOTIFY serialPortChanged)
  Q_PROPERTY(int serialPortIndex READ serialPortIndex WRITE setSerialPortIndex)
  Q_PROPERTY(int serialBaud READ serialBaud NOTIFY serialBaudChanged)
  Q_PROPERTY(int serialBaudIndex READ serialBaudIndex WRITE setSerialBaudIndex)

  /* Modbus items */
  Q_PROPERTY(int slaveId READ slaveId NOTIFY slaveIdChanged)

  /* Timers items */
  Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
  Q_PROPERTY(int intervalIndex READ intervalIndex WRITE setIntervalIndex)
  Q_PROPERTY(bool applyIntervalToController READ applyIntervalToController WRITE setApplyIntervalToController NOTIFY applyIntervalToControllerChanged)

  /* Tuning items */
  Q_PROPERTY(::gos::pid::tuning::types::TuningMode tuning READ tuning WRITE setTuning NOTIFY tuningChanged)
  Q_PROPERTY(int tuningIndex READ tuningIndex WRITE setTuningIndex)
  Q_PROPERTY(QString tuningText READ tuningText)
  Q_PROPERTY(bool isTuning READ isTuning)
  Q_PROPERTY(::gos::pid::tuning::types::TuningState tuningState READ tuningState NOTIFY tuningStateChanged)
  Q_PROPERTY(QString tuningStateText READ tuningStateText)

  /* Status items */
  Q_PROPERTY(::gos::pid::toolkit::ui::item::Connection::Status status READ status NOTIFY statusChanged)
  Q_PROPERTY(bool isInitialize READ isInitialize NOTIFY isInitializeChanged)
  Q_PROPERTY(bool isCompleted READ isCompleted NOTIFY isCompletedChanged)
  Q_PROPERTY(QString statusText READ statusText)
  Q_PROPERTY(bool isConnected READ isConnected)
  Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY lastMessageChanged)
  Q_PROPERTY(bool isLastMessageError READ isLastMessageError)

  /* Logging items */
  Q_PROPERTY(bool isLogging READ isLogging NOTIFY isLoggingChanged)

  /* Controller input items */
  Q_PROPERTY(int manual READ manual WRITE setManual NOTIFY manualChanged)
  Q_PROPERTY(double setpoint READ setpoint WRITE setSetpoint NOTIFY setpointChanged)

  /* Controller settings items */
  Q_PROPERTY(int force READ force WRITE setForce NOTIFY forceChanged)
  Q_PROPERTY(int forceIndex READ forceIndex WRITE setForceIndex)

  /* Controller tuning items */
  Q_PROPERTY(float kp READ kp WRITE setKp NOTIFY kpChanged)
  Q_PROPERTY(float ki READ ki WRITE setKi NOTIFY kiChanged)
  Q_PROPERTY(float kd READ kd WRITE setKd NOTIFY kdChanged)
  Q_PROPERTY(QString kpText READ kpText WRITE setKpText NOTIFY kpTextChanged)
  Q_PROPERTY(QString kiText READ kiText WRITE setKiText NOTIFY kiTextChanged)
  Q_PROPERTY(QString kdText READ kdText WRITE setKdText NOTIFY kdTextChanged)

  /* Controller output items */
  Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
  Q_PROPERTY(QString temperatureText READ temperatureText)
  Q_PROPERTY(double output READ output NOTIFY outputChanged)
  Q_PROPERTY(float integral READ integral NOTIFY integralChanged)
  Q_PROPERTY(QString integralText READ integralText NOTIFY integralTextChanged)

  /* Other items */

  bool initialize(const bool& watcher = true);

  Q_INVOKABLE int update(
    QAbstractSeries* output,
    QAbstractSeries* temperature,
    QAbstractSeries* setpoints);
  Q_INVOKABLE bool connectDisconnect();
  Q_INVOKABLE bool startStopLogging();
  Q_INVOKABLE void panelCompleted();
  Q_INVOKABLE void applyBlackBoxDialog();
  Q_INVOKABLE void rejectBlackBoxDialog();

  const QString configurationModeText() const;

  /* Tuning Notify interface */
  void notifyForce(const ::gos::pid::arduino::types::Unsigned& value);
  void notifyKp(const ::gos::pid::arduino::types::Real& kp);
  void notifyKi(const ::gos::pid::arduino::types::Real& ki);
  void notifyKd(const ::gos::pid::arduino::types::Real& kd);

  /* Configuration Access */
  Configuration* configuration();
  gos::pid::toolkit::ui::configuration::BlackBox* blackBox();

  /* Tuning items */
  const ::gos::pid::tuning::types::TuningState& tuningState() const;
  const QString tuningStateText() const;

  /* Status items */
  const ::gos::pid::toolkit::ui::item::Connection::Status status() const;
  const bool& isInitialize() const;
  const bool& isCompleted() const;
  const QString statusText() const;
  const bool isConnected() const;
  const QString& lastMessage() const;
  const bool& isLastMessageError() const;

  /* Logging items */
  const bool isLogging() const;

  /* Controller input items */
  const int& manual() const;
  const double& setpoint() const;

  /* Controller settings items */
  const int& force() const;
  const int forceIndex() const;

  /* Controller tuning items */
  const float& kp() const;
  const float& ki() const;
  const float& kd() const;
  const QString kpText() const;
  const QString kiText() const;
  const QString kdText() const;

  /* Controller output items */
  const double& temperature() const;
  const QString temperatureText() const;
  const double& output() const;
  const float& integral() const;
  const QString integralText() const;

  /* Other items */

signals:
  void completed();

  void blackBoxChanged();

  void configurationModeTextChanged();
  /* Communication items */
  void serialPortChanged();
  void serialBaudChanged();
  /* Modbus items */
  void slaveIdChanged();
  /* Timers items */
  void intervalChanged();
  void applyIntervalToControllerChanged();
  /* Tuning items */
  void tuningChanged();
  void tuningStateChanged();
  /* Status items */
  void statusChanged();
  void isInitializeChanged();
  void isCompletedChanged();
  void lastMessageChanged();
  /* Logging items */
  void isLoggingChanged();
  /* Controller input items */
  void manualChanged();
  void setpointChanged();
  /* Controller settings items */
  void forceChanged();
  /* Controller tuning items */
  void kpChanged();
  void kiChanged();
  void kdChanged();
  void kpTextChanged();
  void kiTextChanged();
  void kdTextChanged();
  /* Controller output items */
  void temperatureChanged();
  void outputChanged();
  void integralChanged();
  void integralTextChanged();

  /* Other items */

Q_SIGNALS:
//  void quit();
//  void exit(int retCode);

public Q_SLOTS:
//  bool close();

public slots:
  /* Configuration Access */
  //void setBlackBox(::gos::pid::toolkit::ui::configuration::BlackBox* blackBox);

  /* Communication items */
  void setSerialPortIndex(const int& value);
  void setSerialBaudIndex(const int& value);
  /* Timers items */
  void setInterval(const int& value);
  void setIntervalIndex(const int& value);
  void setApplyIntervalToController(const bool& value);
  /* Tuning items */
  void setTuning(const ::gos::pid::tuning::types::TuningMode& value);
  void setTuningIndex(const int& value);
  /* Controller input items */
  void setManual(const int& value);
  void setSetpoint(const double& value);
  /* Controller settings items */
  void setForce(const int& value);
  void setForceIndex(const int& value);
  /* Controller tuning items */
  void setKp(const float& value);
  void setKi(const float& value);
  void setKd(const float& value);
  void setKpText(const QString& value);
  void setKiText(const QString& value);
  void setKdText(const QString& value);
  /* Controller output items */

  /* Other items */

private slots:
  void onConfigurationModeTextChanged();
  void onCommunicationConfigurationChanged();
  void onModbusConfigurationChanged();
  void onTimersConfigurationChanged();
  void onTuningConfigurationChanged();

private:
  typedef QVector<QPointF> VectorList;
  typedef std::unique_ptr<Configuration> ConfigurationPointer;
  typedef std::unique_ptr<std::ofstream> OutputFilePointer;

  void applyConfiguration();
  void connectConfiguration();

  /* Communication items */
  void setSerialPort(const QString& value);
  void setSerialBaud(const int& value);

  /* Status items */
  void setStatus(const ::gos::pid::toolkit::ui::types::status& status);
  void setLastMessage(const QString& message, const bool isLastMessageError = false);
  void setLastError(const QString& message);

  /* Tuning items */
  void setTuningState(const ::gos::pid::tuning::types::TuningState& state);

  /* Controller input items */

  /* Controller settings items */

  /* Controller tuning items */

  /* Controller output items */
  void setTemperature(const ::gos::pid::arduino::types::Real& value);
  void setOutput(const ::gos::pid::arduino::types::Unsigned& value);
  void setIntegral(const float& value);

  /* Timers items */
  bool writeInterval(const ::gos::pid::arduino::types::Unsigned& interval);

  /* Controller input items */
  bool writeManual(const ::gos::pid::arduino::types::Unsigned& manual);
  bool writeSetpoint(const ::gos::pid::arduino::types::Real& setpoint);

  /* Controller settings items */
  bool writeForce(const ::gos::pid::arduino::types::Unsigned& force);

  /* Controller tuning items */
  bool writeKp(const ::gos::pid::arduino::types::Real& kp);
  bool writeKi(const ::gos::pid::arduino::types::Real& ki);
  bool writeKd(const ::gos::pid::arduino::types::Real& kd);

  /* Other items */

  void notify();

  bool initializemodbus();

  void logging(const ::gos::pid::arduino::modbus::types::registry::Input& input);
  void executetuning(
    const ::gos::pid::arduino::modbus::types::registry::Input& input,
    const bool& issuccessful);
  bool handoverNotify();
  bool recoverNotify();

  QQmlContext& context_;
  VectorList setpointsList_;
  VectorList temperatureList_;
  VectorList outputsList_;
  int count_;

  ConfigurationPointer configuration_;
  ::gos::pid::toolkit::ui::configuration::BlackBoxPointer blackBoxForDialog_;
  bool watcher_;

  /* Modbus items */
  ::gos::pid::arduino::modbus::types::registry::HoldingPointer lastHolding_;

  /* Timing items */
  ::gos::pid::toolkit::ui::types::Time start_;

  /* Tuning items */
  int tuningRound_;
  bool isNotifyHandedOver_;
  ::gos::pid::toolkit::ui::types::Time tuningStart_;
  ::gos::pid::tuning::types::TuningState tuningState_;
  ::gos::pid::tuning::types::InitializedPointer tuningInitialized_;
  ::gos::pid::tuning::types::VariablesPointer tuningVariables_;
  ::gos::pid::tuning::types::EvaluationPointer tuningBestEvaluation_;
  ::gos::pid::tuning::black::box::VariablesPointer tuningBlackBoxVariables_;

  /* Status items */
  ::gos::pid::toolkit::ui::types::status status_;
  bool isInitialize_;
  QString lastMessage_;
  bool isLastMessageError_;

  /* Logging items */
  OutputFilePointer logfile_;

  /* Controller input items */
  int manual_;
  double setpoint_;

  /* Controller settings items */
  int force_;

  /* Controller tuning items */
  float kp_;
  float ki_;
  float kd_;

  /* Controller output items */
  double temperature_;
  double output_;
  float integral_;

  /* Other items */

  /* Models */
  QVariant intervalmodel_;
  QVariant tuningmodel_;
  QVariant modemodel_;
  QVariant portmodel_;
  QVariant baudmodel_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
