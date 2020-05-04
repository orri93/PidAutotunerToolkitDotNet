#include <sstream>
#include <iostream>
#include <iomanip>
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

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/floatvalidator.h>

#include <orchestration.h>

#include <model/interval.h>
#include <model/tuning.h>
#include <model/mode.h>

#define GOS_QML_ORCHESTRATION "orchestration"
#define GOS_QML_FLOAT_VALIDATOR "FloatValidator"

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
bool create(QQmlContext& context) {
  qmlRegisterType<gptu::validator::Float>(
    GOS_QML_FLOAT_VALIDATOR, 1, 0, GOS_QML_FLOAT_VALIDATOR);

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

std::unique_ptr<std::ofstream> _file;

gptu::types::Time _start;

gptu::types::status _status = gptu::types::status::undefined;

namespace real {
QString format(const float& real, const int& precision) {
  std::stringstream stream;
  stream << std::setprecision(precision) << real;
  return QString::fromStdString(stream.str());
}
float parse(const QString& string) {
  return static_cast<float>(string.toDouble());
}
}

Orchestration::Orchestration(QQmlContext& context, QObject* parent) :
  Items(parent),
  context_(context),
  count_(0),
  watcher_(false),
  isConnected_(false),
  lastErrorNumber_(0),
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
  if (isConnected_) {
    gpam::master::disconnect();
  }
  gpam::master::shutdown();
}

bool Orchestration::initialize(const bool& watcher) {
  watcher_ = watcher;
  QVariant intervalmodel = gptum::interval::create();
  context_.setContextProperty("intervalModel", intervalmodel);
  QVariant tuningmodel = gptum::tuning::create();
  context_.setContextProperty("tuningModel", tuningmodel);
  QVariant modemodel = gptum::mode::create();
  context_.setContextProperty("modeModel", modemodel);
  configuration_ = std::make_unique<Configuration>(this);
  if (configuration_) {
    QSettings* settings = configuration_->initialize(watcher);
    if (settings != nullptr) {
      applyConfiguration();
      return initializemodbus();
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
  if (_status == gptu::types::status::connected) {
    gpam::types::registry::Input input;
    gpam::types::result result =
      gpam::master::retry::read::input(input);
    if (result == gpam::types::result::success) {
      if (_file) {
        if (_file->is_open()) {
          gptu::types::Duration duration = gptu::types::Clock::now() - _start;
          gptu::types::Duration seconds =
            std::chrono::duration_cast<std::chrono::seconds>(duration);
          (*_file)
            << seconds.count() << ","
            << input.Output << ","
            << input.Temperature << ","
            << setpoint_ << std::endl;
          _file->flush();
        }
      }
      std::cout << "Getting " << input.Output << " as output and "
        << input.Temperature << " as temperature" << std::endl;
      std::cout << "Updating with " << count_ << " points" << std::endl;
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
    }
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
  gptu::types::status saved = _status;
  gpam::types::result result;
  if (isConnected_) {
    _status = gptu::types::status::disconnecting;
    result = gpam::master::disconnect();
    if (result == gpam::types::result::success) {
      std::cout << "Disconnected successfully" << std::endl;
      setIsConnected(false);
      setStatusString("Disconnected");
      _status = gptu::types::status::idle;
      return true;
    } else {
      _status = saved;
      std::cerr << "Disconnecting failed" << std::endl;
      setLastErrorString(QString::fromStdString(
        gpam::master::report::error::last()));
      setLastErrorNumber(gpam::master::report::error::errorno());
      return false;
    }
  } else {
    _status = gptu::types::status::connecting;
    result = gpam::master::connect();
    if (result == gpam::types::result::success) {
      gpam::types::registry::Holding holding;
      result = gpam::master::retry::read::holding(holding);
      if (result == gpam::types::result::success) {
        setManual(holding.Manual);
        setSetpoint(static_cast<double>(holding.Setpoint));
        setKp(static_cast<float>(holding.Kp));
        setKi(static_cast<float>(holding.Ki));
        setKd(static_cast<float>(holding.Kd));
        setForce(static_cast<int>(holding.Force));
        setIsConnected(true);
        setStatusString("Connected");
        if (applyIntervalToController()) {
          writeInterval(static_cast<gpa::types::Unsigned>(interval()));
        }
        _status = gptu::types::status::connected;
        return true;
      }
    } else {
      setLastErrorString(QString::fromStdString(
        gpam::master::report::error::last()));
      setLastErrorNumber(
        gpam::master::report::error::errorno());
    }
    _status = saved;
    return false;
  }
}

bool Orchestration::startStopLogging() {
  if (_file) {
    if (_file->is_open()) {
      std::cout << "Closing the logging file" << std::endl;
      _file->flush();
      _file->close();
    }
    _file.reset(nullptr);
    emit isLoggingChanged();
    return true;
  } else {
    _file = std::make_unique<std::ofstream>("pid.csv", std::ios::out);
    if (_file->is_open()) {
      _start = gptu::types::Clock::now();
      std::cout << "Logging file opened successful" << std::endl;
      emit isLoggingChanged();
      return true;
    } else {
      std::cerr << "Failed to open a logging file" << std::endl;
      _file.reset(nullptr);
    }
  }
  return false;
}

void Orchestration::panelCompleted() {
  qDebug() << "Panel Completed";
  notify();
  iscompleted_ = true;
}

const QString Orchestration::configurationModeText() const {
  return configuration_->modeText();
}

const bool& Orchestration::isConnected() const {
  return isConnected_;
}
const bool Orchestration::isLogging() const {
  if (_file) {
    return _file->is_open();
  } else {
    return false;
  }
}
const QString& Orchestration::statusString() const {
  return statusString_;
}
const QString& Orchestration::lastErrorString() const {
  return lastErrorString_;
}
const errno_t& Orchestration::lastErrorNumber() const {
  return lastErrorNumber_;
}
const int& Orchestration::manual() const {
  return manual_;
}
const double& Orchestration::setpoint() const {
  return setpoint_;
}
const float& Orchestration::kp() const { return kp_; }
const float& Orchestration::ki() const { return ki_; }
const float& Orchestration::kd() const { return kd_; }
const QString Orchestration::kpText() const { return QString::number(kp_); }
const QString Orchestration::kiText() const { return QString::number(ki_); }
const QString Orchestration::kdText() const { return QString::number(kd_); }
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

void Orchestration::setInterval(const int& value) {
  if (applyInterval(value)) {
    std::function<void(const int&)> setter = std::bind(
      &Configuration::setInterval, configuration_.get(), std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    if (applyIntervalToController() && 
      _status == gptu::types::status::connected) {
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
    emit applyIntervalToControllerChanged();
  }
}

void Orchestration::setManual(const int& manual) {
  bool result;
  if (manual_ != manual && manual >= 0 && manual <= 255) {
    switch (_status) {
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
    switch (_status) {
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
    switch (_status) {
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
    switch (_status) {
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
    switch (_status) {
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
    switch (_status) {
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

void Orchestration::setTuning(const gptt::TuningMode& value) {
  if (applyTuning(value)) {
    std::function<void(const gptt::TuningMode&)> setter = std::bind(
      &Configuration::setTuning, configuration_.get(), std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    emit tuningChanged();
  }
}

void Orchestration::setTuningIndex(const int& value) {
  setTuning(gptum::tuning::value(value));
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

void Orchestration::setIsConnected(const bool& value) {
  if (isConnected_ != value) {
    isConnected_ = value;
    emit isConnectedChanged();
  }
}

void Orchestration::setStatusString(const QString& value) {
  if (statusString_ != value) {
    statusString_ = value;
    emit statusStringChanged();
  }
}

void Orchestration::setLastErrorString(const QString& value) {
  if (lastErrorString_ != value) {
    lastErrorString_ = value;
    emit lastErrorStringChanged();
  }
}

void Orchestration::setLastErrorNumber(const errno_t& value) {
  if (lastErrorNumber_ != value) {
    lastErrorNumber_ = value;
    emit lastErrorNumberChanged();
  }
}

void Orchestration::notify() {
  emit configurationModeTextChanged();
  emit intervalChanged();
  emit applyIntervalToControllerChanged();
  emit forceChanged();
  emit tuningChanged();
}

bool Orchestration::initializemodbus() {
  gpam::types::result result;
  QString serialPort = configuration_->serialPort();
  std::string serialport = serialPort.toStdString();
  int serialbaud = configuration_->serialBaud();
  int slaveid = configuration_->slaveId();
  result = gpam::master::initialize(
    serialport.c_str(),
    serialbaud,
    slaveid);
  if (result == gpam::types::result::success) {
    applyConfiguration();
    connectConfiguration();
    _status = gptu::types::status::idle;
    return true;
  } else {
    std::cerr << "Failed to initialize Modbus Master: "
      << gpam::master::report::error::last << std::endl;
  }
  return false;
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

