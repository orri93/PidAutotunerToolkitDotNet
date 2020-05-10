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

#include <gos/pid/toolkit/exception.h>
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
namespace gpt = ::gos::pid::toolkit;

namespace gptt = ::gos::pid::tuning::types;

namespace gpa = ::gos::pid::arduino;
namespace gpam = ::gos::pid::arduino::modbus;
namespace gpat = ::gos::pid::arduino::types;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptut = ::gos::pid::toolkit::ui::types;
namespace gptutc = ::gos::pid::toolkit::ui::types::configuration;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

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
 // qmlRegisterType<gptu::Range>(
  //  GOS_QML_TYPE_RANGE_URI, 1, 0, GOS_QML_TYPE_RANGE_NAME);

  qRegisterMetaType<::gos::pid::toolkit::ui::Range*>(
    "::gos::pid::toolkit::ui::Range*");
  qRegisterMetaType<::gos::pid::toolkit::ui::configuration::BlackBox*>(
    "::gos::pid::toolkit::ui::configuration::BlackBox*");
  qRegisterMetaType<::gos::pid::toolkit::ui::Configuration*>(
    "::gos::pid::toolkit::ui::Configuration*");

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
    configuration.setMode(gptutc::mode::write);
    setter(value);
  } else {
    configuration.setMode(gptutc::mode::write);
    setter(value);
    configuration.setMode(gptutc::mode::normal);
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
  /* Status items */
  status_(gptu::types::status::undefined),
  isInitialize_(false),
  /* Controller input items */
  setpoint_(0.0),
  manual_(0),
  /* Controller settings items */
  force_(0),
  /* Controller tuning items */
  kp_(0.0F),
  ki_(0.0F),
  kd_(0.0F),
  /* Controller output items */
  temperature_(0.0),
  output_(0.0),
  integral_(0.0F) {
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
      gptuc::BlackBox& ref = configuration_->blackBox();
      blackBoxForDialog_ = std::make_unique<gptuc::BlackBox>(ref);
      if (blackBoxForDialog_) {
        status_ = gptu::types::status::disconnected;
        isInitialize_ = true;
        emit isInitializeChanged();
        qInfo() << "Initialize completed";
        return isInitialize_;
      } else {
        qCritical() << "Failed to Black Box Settings for Dialog";
      }
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
          setTemperature(input.Temperature);
          setOutput(input.Output);
          float x = static_cast<float>(count_);
          outputsList_.append(QPointF(x, static_cast<double>(input.Output)));
          temperatureList_.append(QPointF(x, static_cast<double>(
            input.Temperature)));
          setpointsList_.append(QPointF(x, setpoint_));
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
      xySeries->replace(outputsList_);
    }
    if (temperature) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(temperature);
      xySeries->replace(temperatureList_);
    }
    if (setpoints) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(setpoints);
      xySeries->replace(setpointsList_);
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
  emit blackBoxChanged();
  emit isCompletedChanged();
  emit completed();
}

void Orchestration::applyBlackBoxDialog() {
  if (blackBoxForDialog_ && configuration_) {
    gptuc::BlackBox& ref = configuration_->blackBox();
    if (&ref != blackBoxForDialog_.get()) {
      if (::compare(ref, *blackBoxForDialog_) != 0) {
        ref = *blackBoxForDialog_;
        configuration_->setMode(gptutc::mode::write);
        configuration_->write(true);
        configuration_->setMode(gptutc::mode::normal);
      }
    }
  }
}

void Orchestration::rejectBlackBoxDialog() {
  if (blackBoxForDialog_ && configuration_) {
    gptuc::BlackBox& ref = configuration_->blackBox();
    if (::compare(ref, *blackBoxForDialog_) != 0) {
      *blackBoxForDialog_ = ref;
      emit blackBoxChanged();
    }
  }
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

/* Configuration Access */
Configuration* Orchestration::configuration() {
  if (configuration_) {
    return configuration_.get();
  }
  return nullptr;
}

gptu::configuration::BlackBox* Orchestration::blackBox() {
  if (blackBoxForDialog_) {
    return blackBoxForDialog_.get();
  } else {
    qWarning() << "Undefined Black Box from Orchestration";
    return nullptr;
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
const bool& Orchestration::isInitialize() const {
  return isInitialize_;
}
const bool& Orchestration::isCompleted() const {
  return iscompleted_;
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

/* Controller input items */
const int& Orchestration::manual() const {
  return manual_;
}
const double& Orchestration::setpoint() const {
  return setpoint_;
}

/* Controller settings items */
const int& Orchestration::force() const {
  return force_;
}
const int Orchestration::forceIndex() const {
  return gptum::mode::index(force_);
}

/* Controller tuning items */
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

/* Controller output items */
const double& Orchestration::temperature() const {
  return temperature_;
}
const QString Orchestration::temperatureText() const {
  return gptu::formatting::real::format(temperature_);
}
const double& Orchestration::output() const {
  return output_;
}
const float& Orchestration::integral() const {
  return integral_;
}
const QString Orchestration::integralText() const {
  return gptu::formatting::real::format(integral_);
}

/* Other items */

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

/* Controller input items */
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

/* Controller settings items */
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

/* Controller tuning items */
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

/* Controller output items */

/* Other items */

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

/* Controller input items */

/* Controller settings items */

/* Controller tuning items */

/* Controller output items */
void Orchestration::setTemperature(const gpat::Real& value) {
  double asdouble = static_cast<double>(value);
  if (temperature_ != asdouble) {
    temperature_ = asdouble;
    emit temperatureChanged();
  }
}
void Orchestration::setOutput(const gpat::Unsigned& value) {
  double asdouble = static_cast<double>(value);
  if (output_ != asdouble) {
    output_ = asdouble;
    emit outputChanged();
  }
}
void Orchestration::setIntegral(const float& value) {
  if (integral_ != value) {
    integral_ = value;
    emit integralChanged();
    emit integralTextChanged();
  }
}


/* Other items */

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
  QString separator = blackBoxForDialog_->separator();
  QString outputfile = blackBoxForDialog_->file();
  std::string stdseparator = separator.toStdString();
  std::string stdoutputfile = outputfile.toStdString();
  bool isinternal = blackBoxForDialog_->internalVariables();
  gpa::types::Real lkp = static_cast<gpa::types::Real>(blackBoxForDialog_->kp());
  gpa::types::Real lki = static_cast<gpa::types::Real>(blackBoxForDialog_->ki());
  gpa::types::Real lkd = static_cast<gpa::types::Real>(blackBoxForDialog_->kd());
  gp::tuning::setting::window::size = blackBoxForDialog_->windowSize();
  gp::tuning::setting::stable::duration::minutes = 
    blackBoxForDialog_->stableDuration();
  gp::tuning::setting::output::file::path = stdoutputfile;
  switch (tuningState_) {
  case gp::tuning::types::TuningState::undefined:
    setLastError("Undefined tuning state");
    break;
  case gp::tuning::types::TuningState::initialize:
    tuningInitialized_ = std::make_unique<gp::tuning::types::Initialized>();
    if (tuningInitialized_) {
      tuningInitialized_->Setpoint = 
        static_cast<gpa::types::Real>(blackBoxForDialog_->setpoint());
      tuningInitialized_->Manual =
        static_cast<gpa::types::Unsigned>(blackBoxForDialog_->manual());
      tuningInitialized_->Kp = lkp;
      tuningInitialized_->Ki = lki;
      tuningInitialized_->Kd = lkd;
      tuningVariables_ = std::make_unique<gp::tuning::types::Variables>();
      tuningBlackBoxVariables_ =
        std::make_unique<gp::tuning::black::box::Variables>();
      if (tuningVariables_ && tuningBlackBoxVariables_) {
        gp::tuning::setting::parameters.Sd = blackBoxForDialog_->sd();
        gptu::Range* kprp = blackBoxForDialog_->kpRange();
        if (kprp != nullptr) {
          gp::tuning::setting::parameters.Kp.lowest =
            static_cast<gpa::types::Real>(kprp->minimum());
          gp::tuning::setting::parameters.Kp.highest = 
            static_cast<gpa::types::Real>(kprp->maximum());
        }
        gptu::Range* kirp = blackBoxForDialog_->kiRange();
        if (kirp != nullptr) {
          gp::tuning::setting::parameters.Ki.lowest =
            static_cast<gpa::types::Real>(kirp->minimum());
          gp::tuning::setting::parameters.Ki.highest =
            static_cast<gpa::types::Real>(kirp->maximum());
        }
        if (blackBoxForDialog_->isBase()) {
          gp::tuning::setting::parameters.BaseLine =
            static_cast<gpa::types::Real>(blackBoxForDialog_->base());
        } else {
          gp::tuning::setting::parameters.BaseLine = ::boost::none;
        }
        if (lastHolding_) {
          gp::tuning::black::box::load(
            *tuningBlackBoxVariables_,
            *tuningInitialized_,
            *lastHolding_,
            stdseparator,
            isinternal);
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
        stdseparator,
        issuccessful,
        isinternal);
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

