#ifndef GOS_PID_TUNING_UI_ORCHESTRATION_H_
#define GOS_PID_TUNING_UI_ORCHESTRATION_H_

#include <memory>

#include <QTimer>
#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>

#include <gos/pid/arduino/types.h>

#include <gos/pid/tuning/types.h>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/ptu.h>

#include <gos/pid/ui/view/model/blackbox.h>
#include <gos/pid/ui/view/model/modbus.h>
#include <gos/pid/ui/view/model/tuning.h>

#include <configuration.h>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

namespace orchestration {
bool create(QApplication& application, QQmlApplicationEngine& engine);
}

class Orchestration : public ::gos::pid::toolkit::ui::model::Ptu {
  Q_OBJECT
public:
  explicit Orchestration(QObject* parent = nullptr);

  /* Configuration Access */
  Q_PROPERTY(Configuration* configuration READ configuration NOTIFY configurationChanged)
  Q_PROPERTY(Configuration* settings READ settings NOTIFY settingsChanged)

  /* View Models */
  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::Modbus* modbus READ modbus NOTIFY modbusChanged)
  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::Tuning* tuning READ tuning NOTIFY tuningChanged)

  /* Communication items */

  /* Modbus items */

  /* Timers items */
  //Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
  //Q_PROPERTY(int intervalIndex READ intervalIndex WRITE setIntervalIndex)
  //Q_PROPERTY(bool applyIntervalToController READ applyIntervalToController WRITE setApplyIntervalToController NOTIFY applyIntervalToControllerChanged)

  /* Tuning items */
  //Q_PROPERTY(::gos::pid::tuning::types::TuningMode tuning READ tuning WRITE setTuning NOTIFY tuningChanged)
  //Q_PROPERTY(int tuningIndex READ tuningIndex WRITE setTuningIndex)
  //Q_PROPERTY(QString tuningText READ tuningText)
  //Q_PROPERTY(bool isTuning READ isTuning)
  //Q_PROPERTY(::gos::pid::tuning::types::TuningState tuningState READ tuningState NOTIFY tuningStateChanged)
  //Q_PROPERTY(QString tuningStateText READ tuningStateText)

  /* Status items */
  //Q_PROPERTY(::gos::pid::toolkit::ui::model::Status::Enum status READ status NOTIFY statusChanged)
  //Q_PROPERTY(bool isInitialize READ isInitialize NOTIFY isInitializeChanged)
  //Q_PROPERTY(bool isCompleted READ isCompleted NOTIFY isCompletedChanged)
  //Q_PROPERTY(bool isConnected READ isConnected)
  //Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY lastMessageChanged)
  //Q_PROPERTY(bool isLastMessageError READ isLastMessageError)

  /* Logging items */
  Q_PROPERTY(bool isLogging READ isLogging NOTIFY isLoggingChanged)

  /* Controller input items */

  /* Controller settings items */

  /* Controller tuning items */

  /* Controller output items */

  /* Other items */

  bool initialize(const bool& watcher = true);

  Q_INVOKABLE int update(
    QAbstractSeries* output,
    QAbstractSeries* temperature,
    QAbstractSeries* setpoints);
  Q_INVOKABLE bool connectDisconnect();
  Q_INVOKABLE bool startStopLogging();
  Q_INVOKABLE void panelCompleted();
  //Q_INVOKABLE void applyBlackBoxDialog();
  //Q_INVOKABLE void rejectBlackBoxDialog();
  Q_INVOKABLE void applySettings();
  Q_INVOKABLE void rejecSettings();

  //const QString configurationModeText() const;

  /* Tuning Notify interface */
  //void notifyForce(const ::gos::pid::arduino::types::Unsigned& value);
  //void notifyKp(const ::gos::pid::arduino::types::Real& kp);
  //void notifyKi(const ::gos::pid::arduino::types::Real& ki);
  //void notifyKd(const ::gos::pid::arduino::types::Real& kd);

  /* Configuration Access */
  Configuration* configuration();
  Configuration* settings();
  //::gos::pid::toolkit::ui::configuration::BlackBox* blackBox();
  //::gos::pid::toolkit::ui::configuration::Ui* ui();

  /* View Models */
  ::gos::pid::toolkit::ui::view::model::Modbus* modbus();
  ::gos::pid::toolkit::ui::view::model::Tuning* tuning();

  /* Tuning items */
  //const ::gos::pid::tuning::types::TuningState& tuningState() const;
  //const QString tuningStateText() const;

  /* Status items */
  //const ::gos::pid::toolkit::ui::model::Status::Enum status() const;
  //const bool& isInitialize() const;
  //const bool& isCompleted() const;
  //const bool isConnected() const;
  //const QString& lastMessage() const;
  //const bool& isLastMessageError() const;

  /* Logging items */
  const bool isLogging() const;

  /* Controller input items */
  //const int& manual() const;
  //const double& setpoint() const;

  /* Controller settings items */
  //const int& force() const;
  //const int forceIndex() const;

  /* Controller tuning items */
  //const float& kp() const;
  //const float& ki() const;
  //const float& kd() const;
  //const QString kpText() const;
  //const QString kiText() const;
  //const QString kdText() const;

  /* Controller output items */
  //const double& temperature() const;
  //const QString temperatureText() const;
  //const double& output() const;
  //const float& integral() const;
  //const QString integralText() const;

  /* Other items */

signals:
  void completed();

  /* Configuration Access */
  void configurationChanged();
  void settingsChanged();

  //void configurationModeTextChanged();
  /* Communication items */
  //void serialPortChanged();
  //void serialBaudChanged();
  /* Modbus items */
  //void slaveIdChanged();
  /* Timers items */
  //void intervalChanged();
  //void applyIntervalToControllerChanged();
  /* Tuning items */
  /*tuningChanged*/
  //void tuningStateChanged();
  /* Status items */
  //void statusChanged();
  //void isInitializeChanged();
  //void isCompletedChanged();
  //void lastMessageChanged();
  /* Logging items */
  void isLoggingChanged();
  /* Controller input items */
  //void manualChanged();
  //void setpointChanged();
  /* Controller settings items */
  //void forceChanged();
  /* Controller tuning items */
  //void kpChanged();
  //void kiChanged();
  //void kdChanged();
  //void kpTextChanged();
  //void kiTextChanged();
  //void kdTextChanged();
  /* Controller output items */
  //void temperatureChanged();
  //void outputChanged();
  //void integralChanged();
  //void integralTextChanged();

  /* Other items */

  /* View Models */
  void tuningChanged();
  void modbusChanged();

Q_SIGNALS:
//  void quit();
//  void exit(int retCode);

public Q_SLOTS:
  void shutdown();
//  bool close();

public slots:
  /* Configuration Access */
  //void setBlackBox(::gos::pid::toolkit::ui::configuration::BlackBox* blackBox);

  /* Communication items */
  /* Timers items */
  //void setInterval(const int& value);
  //void setApplyIntervalToController(const bool& value);
  /* Tuning items */
  //void setTuning(const ::gos::pid::tuning::types::TuningMode& value);
  //void setTuningIndex(const int& value);
  /* Controller input items */
  /* Controller settings items */
  /* Controller tuning items */
  /* Controller output items */

  /* Other items */

private slots:
  //void onConfigurationModeTextChanged();
  //void onCommunicationConfigurationChanged();
  //void onModbusConfigurationChanged();
  //void onTimersConfigurationChanged();
  //void onTuningConfigurationChanged();

private:
  typedef QVector<QPointF> VectorList;
  typedef std::unique_ptr<Configuration> ConfigurationPointer;
  typedef std::unique_ptr<std::ofstream> OutputFilePointer;

  typedef std::unique_ptr<::gos::pid::toolkit::ui::view::model::Modbus> ModbusPointer;
  typedef std::unique_ptr<::gos::pid::toolkit::ui::view::model::Tuning> TuningPointer;

  bool applyConfiguration();
  //void connectConfiguration();

  /* Communication items */

  /* Status items */
  //void setStatus(const ::gos::pid::toolkit::ui::model::Status::Enum& status);
  //void setLastMessage(const QString& message, const bool isLastMessageError = false);
  //void setLastError(const QString& message);

  /* Tuning items */
  //void setTuningState(const ::gos::pid::tuning::types::TuningState& state);

  /* Controller input items */

  /* Controller settings items */

  /* Controller tuning items */

  /* Controller output items */

  /* Timers items */

  /* Controller input items */

  /* Controller settings items */

  /* Controller tuning items */

  /* Other items */

  void notify();

  //bool initializemodbus();

  void logging(const ::gos::pid::arduino::modbus::types::registry::Input& input);
  //void executetuning(
  //  const ::gos::pid::arduino::modbus::types::registry::Input& input,
  //  const bool& issuccessful);
  //bool handoverNotify();
  //bool recoverNotify();

  VectorList setpointsList_;
  VectorList temperatureList_;
  VectorList outputsList_;
  int count_;

  ModbusPointer modbus_;
  TuningPointer tuning_;
  ConfigurationPointer configuration_;
  ConfigurationPointer settings_;
  //::gos::pid::toolkit::ui::configuration::BlackBoxPointer blackBoxForDialog_;
  //::gos::pid::toolkit::ui::configuration::UiPointer uiForDialog_;
  bool watcher_;

  /* Modbus items */
  //::gos::pid::arduino::modbus::types::registry::HoldingPointer lastHolding_;

  /* Timing items */
  ::gos::pid::toolkit::ui::types::Time start_;

  /* Tuning items */
  //int tuningRound_;
  //bool isNotifyHandedOver_;
  //::gos::pid::toolkit::ui::types::Time tuningStart_;
  //::gos::pid::tuning::types::TuningState tuningState_;
  //::gos::pid::tuning::types::InitializedPointer tuningInitialized_;
  //::gos::pid::tuning::types::VariablesPointer tuningVariables_;
  //::gos::pid::tuning::types::EvaluationPointer tuningBestEvaluation_;
  //::gos::pid::tuning::black::box::VariablesPointer tuningBlackBoxVariables_;

  /* Status items */
  //::gos::pid::toolkit::ui::model::Status::Enum status_;
  //bool isInitialize_;
  QString lastMessage_;
  bool isLastMessageError_;

  /* Logging items */
  OutputFilePointer logfile_;

  /* Controller input items */

  /* Controller settings items */

  /* Controller tuning items */

  /* Controller output items */

  /* Other items */

  /* Models */
  //QVariant operationmodel_;
  //QVariant intervalmodel_;
  //QVariant tuningmodel_;
  //QVariant modemodel_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
