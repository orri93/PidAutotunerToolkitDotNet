#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <QDebug>

#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>

#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/arduino/modbus/retry.h>

#include <gos/pid/ui/plugin.h>
#include <gos/pid/ui/models.h>
#include <gos/pid/ui/status.h>
#include <gos/pid/ui/formatting.h>

#include <gos/pid/tuning/setting.h>

#include <orchestration.h>

#define GOS_QML_ORCHESTRATION "orchestration"

namespace gp = ::gos::pid;

namespace gptt = ::gos::pid::tuning::types;

namespace gpa = ::gos::pid::arduino;
namespace gpam = ::gos::pid::arduino::modbus;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

namespace orchestration {
typedef std::unique_ptr<Orchestration> OrchestrationPointer;
static OrchestrationPointer _orchestration;
//static PidToolkitPlugin _plugin;
bool create(QQmlContext& context) {

  //_plugin.registerTypes("");

  _orchestration = std::make_unique<Orchestration>(context);
  if (_orchestration) {
    context.setContextProperty(GOS_QML_ORCHESTRATION, _orchestration.get());
    if (_orchestration->initialize(false)) {
      return true;
    } else {
      std::cerr << "Failed to initialize the Orchestration" << std::endl;
    }
  } else {
    std::cerr << "Out of memory when creating the Orchestration" << std::endl;
  }
  return false;
}
namespace handle {
template<typename T> void general(
  Configuration& configuration,
  std::function<void(const T&)>& setter,
  const bool& watcher,
  const T& value) {
  qDebug() << "Setting configuration to 'write' mode";
  if (watcher) {
    configuration.setMode(configuration::mode::write);
    setter(value);
  } else {
    configuration.setMode(configuration::mode::write);
    setter(value);
    configuration.setMode(configuration::mode::normal);
  }
}
}
}

Orchestration::Orchestration(QQmlContext& context, QObject* parent) :
  Items(parent),
  context_(context),
  count_(0),
  watcher_(false),
  isLastMessageError_(false),
  tuningRound_(0),
  isNotifyHandedOver_(false),
  tuningState_(gp::tuning::types::TuningState::undefined),
  status_(gptu::types::status::undefined),
  manual_(0),
  setpoint_(0.0),
  kp_(0.0),
  ki_(0.0),
  kd_(0.0),
  force_(0),
  integral_(NAN) {
  qRegisterMetaType<QAbstractSeries*>();
  qRegisterMetaType<QAbstractAxis*>();
}

Orchestration::~Orchestration() {
  if (isNotifyHandedOver_) {
    recoverNotify();
  }
  switch (status_) {
  case gptu::types::status::connected:
    gpam::master::disconnect();
    status_ = gptu::types::status::disconnected;
    break;
  }
  if (logfile_) {
    logfile_->flush();
    logfile_->close();
  }
  gpam::master::shutdown();
}

bool Orchestration::initialize(const bool& watcher) {
  watcher_ = watcher;
  intervalmodel_ = gptum::interval::create();
  context_.setContextProperty(GOS_QML_MODEL_INTERVAL, intervalmodel_);
  tuningmodel_ = gptum::tuning::create();
  context_.setContextProperty(GOS_QML_MODEL_TUNING, tuningmodel_);
  modemodel_ = gptum::mode::create();
  context_.setContextProperty(GOS_QML_MODEL_MODE, modemodel_);
  portmodel_ = gptum::port::create();
  context_.setContextProperty(GOS_QML_MODEL_PORT, portmodel_);
  baudmodel_ = gptum::baud::create();
  context_.setContextProperty(GOS_QML_MODEL_BAUD, baudmodel_);
  configuration_ = std::make_unique<Configuration>(this);
  if (configuration_) {
    QSettings* settings = configuration_->initialize(watcher);
    if (settings != nullptr) {
      applyConfiguration();
      status_ = gptu::types::status::disconnected;
      return true;
    } else {
      qCritical() << "Failed to initialize configuration";
    }
  } else {
    qCritical() << "Failed to create configuration";
  }
  return false;
}

int Orchestration::update(
  QAbstractSeries* output,
  QAbstractSeries* temperature,
  QAbstractSeries* setpoints) {
  switch (status_) {
  case gptu::types::status::connected:
  {
    gpam::types::registry::Input input;
    gpam::types::result result =
      gpam::master::retry::read::input(input);
    if (result == gpam::types::result::success) {
      logging(input);
      if (isTuning()) {
        executetuning(input, true);
      }
      if (input.Output >= 0 && input.Output <= 255) {
        if (input.Temperature >= 0.0 && input.Temperature <= 300.0) {
          float x = static_cast<float>(count_);
          outputs_.append(QPointF(x, static_cast<double>(input.Output)));
          temperature_.append(QPointF(x, static_cast<double>(
            input.Temperature)));
          setpoints_.append(QPointF(x, setpoint_));
          count_++;
        }
      }
      setIntegral(input.Integral);
    } else {
      if (isTuning()) {
        executetuning(input, false);
      }
    }
  }
  break;
  }
  if (count_ > 2) {
    if (output) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(output);
      xySeries->replace(outputs_);
    }
    if (temperature) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(temperature);
      xySeries->replace(temperature_);
    }
    if (setpoints) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(setpoints);
      xySeries->replace(setpoints_);
    }
  }
  return count_;
}

bool Orchestration::connectDisconnect() {
  bool bret = false;
  gpam::types::result result;
  switch (status_) {
  case gptu::types::status::connected:
    setStatus(gptu::types::status::disconnecting);
    result = gpam::master::disconnect();
    if (result == gpam::types::result::success) {
      result = gpam::master::shutdown();
      if (result == gpam::types::result::success) {
        setLastMessage("Disconnected successfully");
        bret = true;
      } else {
        setLastError("Shutdown failed");
      }
      setStatus(gptu::types::status::disconnected);
    } else {
      setLastError("Disconnecting failed" + QString::fromStdString(
        gpam::master::report::error::last()));
      setStatus(gptu::types::status::connected);
    }
    break;
  case gptu::types::status::disconnected:
    setStatus(gptu::types::status::connecting);
    result = gpam::master::initialize(
      serialPort_.toStdString().c_str(),
      serialBaud_,
      slaveId_);
    if (result == gpam::types::result::success) {
      result = gpam::master::connect();
      if (result == gpam::types::result::success) {
        lastHolding_ = std::make_unique<gpam::types::registry::Holding>();
        result = gpam::master::retry::read::holding(*lastHolding_);
        if (result == gpam::types::result::success) {
          manual_ = lastHolding_->Manual;
          setpoint_ = static_cast<double>(lastHolding_->Setpoint);
          kp_ = static_cast<double>(lastHolding_->Kp);
          ki_ = static_cast<double>(lastHolding_->Ki);
          kd_ = static_cast<double>(lastHolding_->Kd);
          force_ = static_cast<int>(lastHolding_->Force);
          emit manualChanged();
          emit setpointChanged();
          emit kpChanged();
          emit kiChanged();
          emit kdChanged();
          if (applyIntervalToController()) {
            writeInterval(static_cast<gpa::types::Unsigned>(interval()));
          }
          setStatus(gptu::types::status::connected);
          bret = true;
          setLastMessage("Connected successfully");
        } else {
          setLastError("Reading initial holdings failed: " +
            QString::fromStdString(gpam::master::report::error::last()));
          setStatus(gptu::types::status::disconnected);
        }
      } else {
        setLastError("Connecting failed: " +
          QString::fromStdString(gpam::master::report::error::last()));
        setStatus(gptu::types::status::disconnected);
      }
    } else {
      setLastError("Initializing Modbus Master failed: " +
        QString::fromStdString(gpam::master::report::error::last()));
      setStatus(gptu::types::status::disconnected);
    }
    break;
  default:
    break;
  }
  return bret;
}

bool Orchestration::startStopLogging() {
  if (logfile_) {
    if (logfile_->is_open()) {
      std::cout << "Closing the logging file" << std::endl;
      logfile_->flush();
      logfile_->close();
    }
    logfile_.reset(nullptr);
    emit isLoggingChanged();
    return true;
  } else {
    logfile_ = std::make_unique<std::ofstream>("pid.csv", std::ios::out);
    if (logfile_->is_open()) {
      start_ = gptu::types::Clock::now();
      std::cout << "Logging file opened successful" << std::endl;
      emit isLoggingChanged();
      return true;
    } else {
      std::cerr << "Failed to open a logging file" << std::endl;
      logfile_.reset(nullptr);
      return false;
    }
  }
}

void Orchestration::panelCompleted() {
  qDebug() << "Panel Completed";
  notify();
  iscompleted_ = true;
}

const QString Orchestration::configurationModeText() const {
  return configuration_->modeText();
}

/* Tuning Notify interface */
void Orchestration::notifyForce(const gpa::types::Unsigned& value) {
  gpa::types::Unsigned lf = static_cast<gpa::types::Unsigned>(force_);
  if (lf != value && value > 0 && value <= 3) {
    force_ = static_cast<int>(value);
    emit forceChanged();
  }
}
void Orchestration::notifyKp(const gpa::types::Real& kp) {
  if (kp_!= kp) {
    kp_ = kp;
    emit kpChanged();
  }
}
void Orchestration::notifyKi(const gpa::types::Real& ki) {
  if (ki_ != ki) {
    ki_ = ki;
    emit kiChanged();
  }
}
void Orchestration::notifyKd(const gpa::types::Real& kd) {
  if (kd_ != kd) {
    kd_ = kd;
    emit kdChanged();
  }
}

/* Tuning items */
const gp::tuning::types::TuningState& Orchestration::tuningState() const {
  return tuningState_;
}
const QString Orchestration::tuningStateText() const {
  switch (tuningState_) {
  case gp::tuning::types::TuningState::undefined:
    return "Undefined";
  case gp::tuning::types::TuningState::initialize:
    return "Initialize";
  case gp::tuning::types::TuningState::reach:
    return "Reaching";
  case gp::tuning::types::TuningState::over:
    return "Over";
  case gp::tuning::types::TuningState::under:
    return "Under";
  case gp::tuning::types::TuningState::balance:
    return "Stable";
  case gp::tuning::types::TuningState::cooldown:
    return "Cool down";
  case gp::tuning::types::TuningState::completed:
    return "Completed";
  default:
    return "Unknown";
  }
}

/* Status items */
const gp::toolkit::ui::item::Connection::Status Orchestration::status() const {
  return gp::toolkit::ui::status::convert(status_);
}
const QString Orchestration::statusText() const {
  return QString::fromStdString(gp::toolkit::ui::types::to::string(status_));
}
const bool Orchestration::isConnected() const {
  return status_ == gp::toolkit::ui::types::status::connected;
}
const QString& Orchestration::lastMessage() const {
  return lastMessage_;
}
const bool& Orchestration::isLastMessageError() const {
  return isLastMessageError_;
}

/* Logging items */
const bool Orchestration::isLogging() const {
  if (logfile_) {
    return logfile_->is_open();
  } else {
    return false;
  }
}

/* Other items */
const int& Orchestration::manual() const {
  return manual_;
}
const double& Orchestration::setpoint() const {
  return setpoint_;
}
const float& Orchestration::kp() const { return kp_; }
const float& Orchestration::ki() const { return ki_; }
const float& Orchestration::kd() const { return kd_; }
const QString Orchestration::kpText() const {
#ifdef GOS_PID_TOOLKIT_UI_NOT_USE_FORMATTING_FOR_K
  return QString::number(kp_);
#else
  return gptu::formatting::real::format(kp_);
#endif
}
const QString Orchestration::kiText() const {
#ifdef GOS_PID_TOOLKIT_UI_NOT_USE_FORMATTING_FOR_K
  return QString::number(ki_);
#else
  return gptu::formatting::real::format(ki_);
#endif
}
const QString Orchestration::kdText() const {
#ifdef GOS_PID_TOOLKIT_UI_NOT_USE_FORMATTING_FOR_K
  return QString::number(kd_);
#else
  return gptu::formatting::real::format(kd_);
#endif
}
const int& Orchestration::force() const {
  return force_;
}
const int Orchestration::forceIndex() const {
  return gptum::mode::index(force_);
}
const float& Orchestration::integral() const {
  return integral_;
}
const QString Orchestration::integralText() const {
  return QString::number(integral_);
}

/* Communication items */
void Orchestration::setSerialPortIndex(const int& value) {
  return setSerialPort(gptum::port::value(value));
}
void Orchestration::setSerialBaudIndex(const int& value) {
  return setSerialBaud(gptum::baud::value(value));
}

/* Timers items */
void Orchestration::setInterval(const int& value) {
  if (applyInterval(value)) {
    std::function<void(const int&)> setter = std::bind(
      &Configuration::setInterval, configuration_.get(), std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    if (applyIntervalToController() && isConnected()) {
      writeInterval(static_cast<gpa::types::Unsigned>(interval()));
    }
    emit intervalChanged();
  }
}

void Orchestration::setIntervalIndex(const int& value) {
  setInterval(model::interval::value(value));
}

void Orchestration::setApplyIntervalToController(const bool& value) {
  if (applyApplyIntervalToController(value)) {
    std::function<void(const bool&)> setter = std::bind(
      &Configuration::setApplyIntervalToController,
      configuration_.get(),
      std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    if (applyIntervalToController() && isConnected()) {
      writeInterval(static_cast<gpa::types::Unsigned>(interval()));
    }
    emit applyIntervalToControllerChanged();
  }
}

/* Tuning items */
void Orchestration::setTuning(const gptt::TuningMode& value) {
  gptt::TuningMode saved = tuning_;
  if (applyTuning(value)) {
    std::function<void(const gptt::TuningMode&)> setter = std::bind(
      &Configuration::setTuning, configuration_.get(), std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    if (isTuning()) {
      if (handoverNotify()) {
        setLastMessage("Notify Handed Over");
        setTuningState(gp::tuning::types::TuningState::initialize);
        emit tuningChanged();
      } else {
        setLastError("Failed to hand over notify");
        setTuningState(gp::tuning::types::TuningState::undefined);
        tuning_ = saved;
      }
    } else {
      if (recoverNotify()) {
        setTuningState(gp::tuning::types::TuningState::undefined);
      } else {
        throw std::runtime_error("Failed to recover tuning notifier");
      }
      emit tuningChanged();
    }
  }
}
void Orchestration::setTuningIndex(const int& value) {
  setTuning(gptum::tuning::value(value));
}

/* Tuning items */
void Orchestration::setTuningState(const gp::tuning::types::TuningState& state) {
  if (tuningState_ != state) {
    tuningState_ = state;
    emit tuningStateChanged();
  }
}


/* Other items */
void Orchestration::setManual(const int& manual) {
  bool result;
  if (manual_ != manual && manual >= 0 && manual <= 255) {
    switch (status_) {
    case gptu::types::status::connected:
      result = writeManual(static_cast<gpa::types::Unsigned>(manual));
      if (result) {
        qDebug() << "Successfully set Manual to " << manual;
      } else {
        qWarning() << "Failed to set Manual to " << manual << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptu::types::status::connecting:
      break;
    default:
      qDebug() << "Not connected when Manual changed from "
        << manual_ << " to " << manual;
      break;
    }
    manual_ = manual;
    emit manualChanged();
  }
}

void Orchestration::setSetpoint(const double& setpoint) {
  bool result;
  if (setpoint_ != setpoint && setpoint >= 0.0 && setpoint <= 300.0) {
    switch (status_) {
    case gptu::types::status::connected:
      result = writeSetpoint(static_cast<gpa::types::Real>(setpoint));
      if (result) {
        qDebug() << "Successfully set Setpoint to " << setpoint;
      } else {
        qWarning() << "Failed to set Setpoint to " << setpoint << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptu::types::status::connecting:
      break;
    default:
      qDebug() << "Not connected when Setpoint changed from "
        << setpoint_ << " to " << setpoint;
      break;
    }
    setpoint_ = setpoint;
    emit setpointChanged();
  }
}

void Orchestration::setKp(const float& value) {
  bool result;
  if (kp_ != value && value >= 0.0 && value <= 100.0) {
    switch (status_) {
    case gptu::types::status::connected:
      result = writeKp(static_cast<gpa::types::Real>(value));
      if (result) {
        qDebug() << "Successfully set Kp to " << value;
      } else {
        qWarning() << "Failed to set Kp to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptu::types::status::connecting:
      break;
    default:
      qDebug() << "Not connected when Kp changed from "
        << kp_ << " to " << value;
      break;
    }
    kp_ = value;
    emit kpChanged();
    emit kpTextChanged();
  }
}

void Orchestration::setKi(const float& value) {
  bool result;
  if (ki_ != value && value >= 0.0 && value <= 100.0) {
    switch (status_) {
    case gptu::types::status::connected:
      result = writeKi(static_cast<gpa::types::Real>(value));
      if (result) {
        qDebug() << "Successfully set Ki to " << value;
      } else {
        qWarning() << "Failed to set Ki to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptu::types::status::connecting:
      break;
    default:
      qDebug() << "Not connected when Ki changed from "
        << ki_ << " to " << value;
      break;
    }
    ki_ = value;
    emit kiChanged();
    emit kiTextChanged();
  }
}

void Orchestration::setKd(const float& value) {
  bool result;
  if (kd_ != value && value >= 0.0 && value <= 100.0) {
    switch (status_) {
    case gptu::types::status::connected:
      result = writeKd(static_cast<gpa::types::Real>(value));
      if (result) {
        qDebug() << "Successfully set Kd to " << value;
      } else {
        qWarning() << "Failed to set Kd to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptu::types::status::connecting:
      break;
    default:
      qDebug() << "Not connected when Kd changed from "
        << kd_ << " to " << value;
      break;
    }
    kd_ = value;
    emit kdChanged();
    emit kdTextChanged();
  }
}

void Orchestration::setKpText(const QString& value) {
  bool ok;
  float kp = value.toFloat(&ok);
  if (ok && std::isfinite(kp) && kp != kp_) {
    setKp(kp);
  }
}

void Orchestration::setKiText(const QString& value) {
  bool ok;
  float ki = value.toFloat(&ok);
  if (ok && std::isfinite(ki) && ki != ki_) {
    setKi(ki);
  }
}

void Orchestration::setKdText(const QString& value) {
  bool ok;
  float kd = value.toFloat(&ok);
  if (ok && std::isfinite(kd) && kd != kd_) {
    setKd(kd);
  }
}

void Orchestration::setForce(const int& value) {
  bool result;
  if (force_ != value && value > 0 && value <= 3) {
    switch (status_) {
    case gptu::types::status::connected:
      result = writeForce(static_cast<gpa::types::Unsigned>(value));
      if (result) {
        qDebug() << "Successfully set Force to " << value;
      } else {
        qWarning() << "Failed to set Force to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptu::types::status::connecting:
      break;
    default:
      qDebug() << "Not connected when Force changed from "
        << force_ << " to " << value;
      break;
    }
    force_ = value;
    emit forceChanged();
  }
}

void Orchestration::setForceIndex(const int& value) {
  int force = gptum::mode::mode(value);
  if (force >= 0) {
    setForce(force);
  }
}

void Orchestration::onConfigurationModeTextChanged() {
  qDebug() << " Configuration Mode Text Changed";
  emit configurationModeTextChanged();
}

void Orchestration::onCommunicationConfigurationChanged() {
  qDebug() << " Communication Configuration Changed";
}

void Orchestration::onModbusConfigurationChanged() {
  qDebug() << " Modbus Configuration Changed";
}

void Orchestration::onTimersConfigurationChanged() {
  qDebug() << " Timers Configuration Changed";
  setInterval(configuration_->interval());
  setApplyIntervalToController(configuration_->applyIntervalToController());
}

void Orchestration::onTuningConfigurationChanged() {
  qDebug() << " Tuning Configuration Changed";
  setTuning(configuration_->tuning());
}

void Orchestration::applyConfiguration() {
  serialPort_ = configuration_->serialPort();
  serialBaud_ = configuration_->serialBaud();
  slaveId_= configuration_->slaveId();
  interval_ = configuration_->interval();
  applyIntervalToController_ = configuration_->applyIntervalToController();
  tuning_ = configuration_->tuning();
}

void Orchestration::connectConfiguration() {
  QObject::connect(
    configuration_.get(),
    &Configuration::modeTextChanged,
    this,
    &Orchestration::onConfigurationModeTextChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::serialPortChanged,
    this,
    &Orchestration::onCommunicationConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::serialBaudChanged,
    this,
    &Orchestration::onCommunicationConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::slaveIdChanged,
    this,
    &Orchestration::onModbusConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::intervalChanged,
    this,
    &Orchestration::onTimersConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::applyIntervalToControllerChanged,
    this,
    &Orchestration::onTimersConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::tuningChanged,
    this,
    &Orchestration::onTuningConfigurationChanged);
}

/* Communication items */
void Orchestration::setSerialPort(const QString& value) {
  if (applySerialPort(value)) {
    std::function<void(const QString&)> setter = std::bind(
      &Configuration::setSerialPort,
      configuration_.get(),
      std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    emit serialPortChanged();
  }
}
void Orchestration::setSerialBaud(const int& value) {
  if (applySerialBaud(value)) {
    std::function<void(const int&)> setter = std::bind(
      &Configuration::setSerialBaud,
      configuration_.get(),
      std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    emit serialBaudChanged();
  }
}

/* Status items */
void Orchestration::setStatus(const gptu::types::status& status) {
  if (status_ != status) {
    status_ = status;
    emit statusChanged();
  }
}
void Orchestration::setLastMessage(const QString& message, const bool isLastMessageError) {
  isLastMessageError_ = isLastMessageError;
  if (lastMessage_ != message) {
    lastMessage_ = message;
    emit lastMessageChanged();
  }
}
void Orchestration::setLastError(const QString& message) {
  setLastMessage(message, true);
}

/* Other items */
void Orchestration::setIntegral(const float& value) {
  if (integral_ != value) {
    integral_ = value;
    emit integralChanged();
    emit integralTextChanged();
  }
}

bool Orchestration::writeManual(const gpa::types::Unsigned& manual) {
  return gpam::master::retry::write::manual(manual) ==
    gpam::types::result::success;
}

bool Orchestration::writeSetpoint(const gpa::types::Real& setpoint) {
  return gpam::master::retry::write::setpoint(setpoint) ==
    gpam::types::result::success;
}

bool Orchestration::writeKp(const gpa::types::Real& kp) {
  return gpam::master::retry::write::kp(kp) ==
    gpam::types::result::success;
}

bool Orchestration::writeKi(const gpa::types::Real& ki) {
  return gpam::master::retry::write::ki(ki) ==
    gpam::types::result::success;
}

bool Orchestration::writeKd(const gpa::types::Real& kd) {
  return gpam::master::retry::write::kd(kd) ==
    gpam::types::result::success;
}

bool Orchestration::writeForce(const gpa::types::Unsigned& force) {
  return gpam::master::retry::write::force(force) ==
    gpam::types::result::success;
}

bool Orchestration::writeInterval(const gpa::types::Unsigned& interval) {
  return gpam::master::retry::write::interval(interval) ==
    gpam::types::result::success;
}

void Orchestration::notify() {
  emit statusChanged();
  emit lastMessageChanged();
  emit serialPortChanged();
  emit serialBaudChanged();
  emit slaveIdChanged();
  emit configurationModeTextChanged();
  emit intervalChanged();
  emit applyIntervalToControllerChanged();
  emit forceChanged();
  emit tuningChanged();
}

bool Orchestration::initializemodbus() {
  gpam::types::result result;
  std::string serialport = serialPort_.toStdString();
  result = gpam::master::initialize(
    serialport.c_str(),
    serialBaud_,
    slaveId_);
  if (result == gpam::types::result::success) {
    applyConfiguration();
    connectConfiguration();
    return true;
  } else {
    qWarning() << "Failed to initialize Modbus Master";
  }
  return false;
}

void Orchestration::logging(const gpam::types::registry::Input& input) {
  if (logfile_) {
    if (logfile_->is_open()) {
      gptu::types::Duration duration = gptu::types::Clock::now() - start_;
      gptu::types::Duration seconds =
        std::chrono::duration_cast<std::chrono::seconds>(duration);
      (*logfile_)
        << seconds.count() << ","
        << input.Output << ","
        << input.Temperature << ","
        << setpoint_ << std::endl;
      logfile_->flush();
    }
  }
}

void Orchestration::executetuning(
  const gpam::types::registry::Input& input,
  const bool& issuccessful) {
  const bool IsInternal = true;
  const std::string Separator = ",";
  gpa::types::Real lkp = static_cast<gpa::types::Real>(kp_);
  gpa::types::Real lki = static_cast<gpa::types::Real>(ki_);
  gpa::types::Real lkd = static_cast<gpa::types::Real>(kd_);
  gp::tuning::setting::window::size = 15;
  gp::tuning::setting::stable::duration::minutes = 10;
  gp::tuning::setting::output::file::path = "black-box-tuning.csv";
  switch (tuningState_) {
  case gp::tuning::types::TuningState::undefined:
    setLastError("Undefined tuning state");
    break;
  case gp::tuning::types::TuningState::initialize:
    tuningInitialized_ = std::make_unique<gp::tuning::types::Initialized>();
    if (tuningInitialized_) {
      tuningInitialized_->Setpoint = static_cast<gpa::types::Real>(setpoint_);
      tuningInitialized_->Manual = static_cast<gpa::types::Unsigned>(manual_);
      tuningInitialized_->Kp = lkp;
      tuningInitialized_->Ki = lki;
      tuningInitialized_->Kd = lkd;
      tuningVariables_ = std::make_unique<gp::tuning::types::Variables>();
      tuningBlackBoxVariables_ =
        std::make_unique<gp::tuning::black::box::Variables>();
      if (tuningVariables_ && tuningBlackBoxVariables_) {
        gp::tuning::setting::parameters.Sd = 0.125F;
        gp::tuning::setting::parameters.Kp.lowest = lkp * 0.25F;
        gp::tuning::setting::parameters.Kp.highest = lkp * 1.75F;
        gp::tuning::setting::parameters.Ki.lowest = lki * 0.25F;
        gp::tuning::setting::parameters.Ki.highest = lki * 1.75F;
        if (lastHolding_) {
          gp::tuning::black::box::load(
            *tuningBlackBoxVariables_,
            *tuningInitialized_,
            *lastHolding_,
            Separator,
            IsInternal);
          gp::tuning::black::box::initialize(
            *tuningVariables_,
            *tuningBlackBoxVariables_,
            gp::tuning::setting::parameters,
            tuningInitialized_->Kp.get(),
            tuningInitialized_->Ki.get());
          if (writeForce(GOT_PI_FORCE_AUTO)) {
            force_ = GOT_PI_FORCE_AUTO;
            emit forceChanged();
            tuningRound_ = 0;
            tuningStart_ = gptu::types::Clock::now();
            setTuningState(gp::tuning::types::TuningState::reach);
          } else {
            setLastError("Failed to force for tuning");
          }
        } else {
          setLastError("Last holding is undefined");
        }
      } else {
        setLastError("Out of memory for tuning");
      }
    } else {
      setLastError("Out of memory for tuning");
    }
    break;
  case gp::tuning::types::TuningState::reach:
  case gp::tuning::types::TuningState::over:
  case gp::tuning::types::TuningState::under:
  case gp::tuning::types::TuningState::balance:
  case gp::tuning::types::TuningState::cooldown:
    break;
  default:
    setLastError("Unknown tuning state");
    break;
  }
  gptu::types::Time time = gptu::types::Clock::now();
  gptu::types::Duration duration = time - tuningStart_;
  std::chrono::milliseconds dms =
    std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  double elapsed = static_cast<double>(dms.count()) / 1000.0;
  if (tuningVariables_ && tuningBlackBoxVariables_) {
    switch (tuningState_) {
    case gp::tuning::types::TuningState::undefined:
      setLastError("Undefined tuning state again");
      break;
    case gp::tuning::types::TuningState::initialize:
      setLastError("Initialize state repeated");
      break;
    case gp::tuning::types::TuningState::reach:
    case gp::tuning::types::TuningState::over:
    case gp::tuning::types::TuningState::under:
    case gp::tuning::types::TuningState::balance:
    case gp::tuning::types::TuningState::cooldown:
      gp::tuning::black::box::cycle(
        tuningRound_,
        *tuningVariables_,
        *tuningBlackBoxVariables_,
        tuningBestEvaluation_,
        gp::tuning::setting::parameters,
        input,
        elapsed,
        time,
        Separator,
        issuccessful,
        IsInternal);
      break;
    default:
      setLastError("Unknown tuning state again");
      break;
    }
    switch (tuningState_) {
    case gp::tuning::types::TuningState::undefined:
      setLastError("Undefined tuning state the third time");
      break;
    case gp::tuning::types::TuningState::initialize:
      setLastError("Initialize state repeated again");
      break;
    case gp::tuning::types::TuningState::reach:
      if (tuningBlackBoxVariables_->IsOver) {
        setLastMessage("Tuning Setpoint Reached");
        setTuningState(gp::tuning::types::TuningState::over);
      }
    case gp::tuning::types::TuningState::over:
      if (tuningBlackBoxVariables_->IsUnder) {
        setLastMessage("Tuning Under");
        setTuningState(gp::tuning::types::TuningState::under);
      }
    case gp::tuning::types::TuningState::under:
      if (tuningBlackBoxVariables_->IsStable) {
        setLastMessage("Tuning Stable");
        setTuningState(gp::tuning::types::TuningState::balance);
      }
    case gp::tuning::types::TuningState::balance:
      if (tuningBlackBoxVariables_->IsCooling) {
        setLastMessage("Tuning Cooling Down");
        setTuningState(gp::tuning::types::TuningState::cooldown);
      }
    case gp::tuning::types::TuningState::cooldown:
      if (tuningBlackBoxVariables_->IsRoundStarting) {
        setTuningState(gp::tuning::types::TuningState::reach);
      }
      break;
    default:
      setLastError("Unknown tuning state the third time");
      break;
    }
  }
}

bool Orchestration::handoverNotify() {
  if (!isNotifyHandedOver_) {
    gp::tuning::NotifyPointer notify(this);
    if (notify) {
      isNotifyHandedOver_ = gp::tuning::black::box::notify::handover(notify);
      if (isNotifyHandedOver_) {
        return true;
      } else {
        setLastError("Failed to hand over notify");
      }
    } else {
      setLastError("Failed to create notify for hand over");
    }
  } else {
    setLastError("Notify has already been handed over");
  }
  return false;
}

bool Orchestration::recoverNotify() {
  if (isNotifyHandedOver_) {
    gp::tuning::NotifyPointer notify;
    isNotifyHandedOver_ = !(gp::tuning::black::box::notify::recover(notify));
    if (!isNotifyHandedOver_) {
      gp::tuning::Nofity* pointer = notify.release();
      return true;
    } else {
      setLastError("Failed to recover notify");
    }
  } else {
    setLastError("Notify has not yet been handed over");
  }
  return false;
}


} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

