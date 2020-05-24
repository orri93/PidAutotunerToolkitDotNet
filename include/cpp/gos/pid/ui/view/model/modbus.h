#ifndef GOS_PID_TUNING_UI_VIEW_MODEL_MODBUS_H_
#define GOS_PID_TUNING_UI_VIEW_MODEL_MODBUS_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/model/modbus.h>

#include <gos/pid/ui/view/model/interface.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace view {
namespace model {

class Modbus :
  public ::gos::pid::toolkit::ui::model::Modbus,
  public virtual ::gos::pid::toolkit::ui::view::model::Interface {
  Q_OBJECT

    /* Communication items */
    //Q_PROPERTY(QString serialPort READ serialPort WRITE setSerialPort NOTIFY serialPortChanged)
    //Q_PROPERTY(int serialBaud READ serialBaud WRITE setSerialBaud NOTIFY serialBaudChanged)

    /* Modbus items */
    //Q_PROPERTY(int slaveId READ slaveId WRITE setSlaveId NOTIFY slaveIdChanged)

    /* Timers items */

    /**
     * @brief The interval (cycle time) for the Arduino Controller.
    */
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

    /* Status items */

    /**
     * @brief The Connection status for the Modbus communication.
    */
    Q_PROPERTY(::gos::pid::toolkit::ui::model::Status::Enum status READ status NOTIFY statusChanged)
    /**
     * @brief A boolean property indicating if the Modbus Master is connected or not.
    */
    Q_PROPERTY(bool isConnected READ isConnected)
    //Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY lastMessageChanged)
    //Q_PROPERTY(bool isLastMessageError READ isLastMessageError)

    /* Controller input items */

    /**
     * @brief The Manual setting for the Arduino Controller.
    */
    Q_PROPERTY(int manual READ manual WRITE setManual NOTIFY manualChanged)
    /**
     * @brief The Setpoint setting for the Arduino Controller.
    */
    Q_PROPERTY(double setpoint READ setpoint WRITE setSetpoint NOTIFY setpointChanged)

    /* Controller settings items */
    Q_PROPERTY(::gos::pid::toolkit::ui::model::Force::Enum force READ force WRITE setForce NOTIFY forceChanged)

    /* Controller tuning items */
    Q_PROPERTY(double kp READ kp WRITE setKp NOTIFY kpChanged)
    Q_PROPERTY(double ki READ ki WRITE setKi NOTIFY kiChanged)
    Q_PROPERTY(double kd READ kd WRITE setKd NOTIFY kdChanged)

    /* Controller output items */
    Q_PROPERTY(double temperature READ temperature NOTIFY temperatureChanged)
    Q_PROPERTY(double output READ output NOTIFY outputChanged)
    Q_PROPERTY(float integral READ integral NOTIFY integralChanged)

public:
  explicit Modbus(
    ::gos::pid::toolkit::ui::model::Force& force,
    QObject* parent = nullptr);
  ~Modbus();

  bool initialize();
  void shutdown();
  bool update(::gos::pid::arduino::modbus::types::registry::Input& input);

  /* Apply View Model interface implementation */
  bool apply(::gos::pid::toolkit::ui::configuration::Interface& configuration);
  void notify();

  Q_INVOKABLE bool connectDisconnect();

  /* Modbus items */
  const bool haveLastHolding() const;
  ::gos::pid::arduino::modbus::types::registry::Holding& lastHolding();

  /* Timers items */
  const int& interval() const;

  /* Status items */
  const ::gos::pid::toolkit::ui::model::Status::Enum status() const;
  //const bool& isInitialize() const;
  //const bool& isCompleted() const;
  const bool isConnected() const;
  const QString& lastMessage() const;
  const bool& isLastMessageError() const;

  /* Controller input items */
  const int& manual() const;
  const double& setpoint() const;

  /* Controller settings items */
  const ::gos::pid::toolkit::ui::model::Force::Enum& force() const;

  /* Controller tuning items */
  const double& kp() const;
  const double& ki() const;
  const double& kd() const;

  /* Controller output items */
  const double& temperature() const;
  const double& output() const;
  const double& integral() const;

  /* Other items */

  /* Timers items */
  virtual bool applyInterval(const int& value);

  /* Timers items */
  bool writeInterval(const ::gos::pid::arduino::types::Unsigned& interval);

  /* Controller settings items */
  bool writeForce(const ::gos::pid::toolkit::ui::model::Force::Enum& force);
  bool writeForceNumber(const ::gos::pid::arduino::types::Unsigned& force);

signals:
  //void completed();
  /* Communication items */
  //void serialPortChanged();
  //void serialBaudChanged();
  /* Modbus items */
  //void slaveIdChanged();
  /* Timers items */
  void intervalChanged();
  /* Status items */
  void statusChanged();
  //void isInitializeChanged();
  //void isCompletedChanged();
  void lastMessageChanged();
  /* Controller input items */
  void manualChanged();
  void setpointChanged();
  /* Controller settings items */
  void forceChanged();
  /* Controller tuning items */
  void kpChanged();
  void kiChanged();
  void kdChanged();
  /* Controller output items */
  void temperatureChanged();
  void outputChanged();
  void integralChanged();

  /* Other items */

public slots:
  /* Communication items */
  void setSerialPort(const QString& value);
  void setSerialBaud(const int& value);
  /* Modbus items */
  void setSlaveId(const int& value);
  /* Timers items */
  void setInterval(const int& value);
  /* Controller input items */
  void setManual(const int& value);
  void setSetpoint(const double& value);
  /* Controller settings items */
  void setForce(const ::gos::pid::toolkit::ui::model::Force::Enum& value);
  /* Controller tuning items */
  void setKp(const double& value);
  void setKi(const double& value);
  void setKd(const double& value);
  /* Controller output items */

  /* Other items */

private slots:

private:

  /* Status items */
  void setStatus(const ::gos::pid::toolkit::ui::model::Status::Enum& status);
  void setLastMessage(const QString& message, const bool isLastMessageError = false);
  void setLastError(const QString& message);

  /* Controller input items */

  /* Controller settings items */

  /* Controller tuning items */

  /* Controller output items */
  void setTemperature(const ::gos::pid::arduino::types::Real& value);
  void setOutput(const ::gos::pid::arduino::types::Unsigned& value);
  void setIntegral(const float& value);

  /* Timers items */

  /* Controller input items */
  bool writeManual(const ::gos::pid::arduino::types::Unsigned& manual);
  bool writeSetpoint(const ::gos::pid::arduino::types::Real& setpoint);

  /* Controller settings items */

  /* Controller tuning items */
  bool writeKp(const ::gos::pid::arduino::types::Real& kp);
  bool writeKi(const ::gos::pid::arduino::types::Real& ki);
  bool writeKd(const ::gos::pid::arduino::types::Real& kd);

  ::gos::pid::toolkit::ui::model::Force& forceModel_;

  /* Modbus items */
  ::gos::pid::arduino::modbus::types::registry::HoldingPointer lastHolding_;

  /* Status items */
  ::gos::pid::toolkit::ui::model::Status::Enum status_;
  //bool isInitialize_;
  QString lastMessage_;
  bool isLastMessageError_;

  /* Timers items */
  int interval_;

  /* Controller input items */
  int manual_;
  double setpoint_;

  /* Controller settings items */
  ::gos::pid::toolkit::ui::model::Force::Enum force_;

  /* Controller tuning items */
  ::gos::pid::toolkit::ui::model::Triplet triplet_;

  /* Controller output items */
  double temperature_;
  double output_;
  double integral_;

  /* Other items */
};

} // namespace model
} // namespace view
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
