#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>

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

#include <orchestration.h>

namespace gpa = ::gos::pid::arduino;
namespace gpam = ::gos::pid::arduino::modbus;

namespace gptu = ::gos::pid::toolkit::ui;

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

std::unique_ptr<std::ofstream> _file;

typedef std::chrono::steady_clock Clock;
typedef Clock::duration Duration;
typedef Clock::time_point Time;

Time _start;

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

Orchestration::Orchestration(QQuickView* appViewer, QObject* parent) :
  QObject(parent),
  appViewer_(appViewer),
  count_(0),
  isConnected_(false),
  lastErrorNumber_(0),
  refreshInterval_(1000),
  refreshFrequency_(1.0),
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

bool Orchestration::initialize(QQmlContext* context) {
  gpam::types::result result;
  configuration_ = std::make_unique<Configuration>(this);
  if (configuration_) {
    QSettings* settings = configuration_->read();
    if (settings != nullptr) {
      QString serialPort = configuration_->serialPort();
      std::string serialport = serialPort.toStdString();
      int serialbaud = configuration_->serialBaud();
      int slaveid = configuration_->slaveId();
      result = gpam::master::initialize(
        serialport.c_str(),
        serialbaud,
        slaveid);
      if (result == gpam::types::result::success) {
        setRefreshInterval(configuration_->refreshInterval());
        refreshFrequency_ = 1.0 / (refreshInterval_ / 1000.0);
        _status = gptu::types::status::idle;
        return true;
      }
    } else {
      qCritical() << "Failed to create configuration";
    }
  } else {
    qCritical() << "Failed to create configuration";
  }
  return false;
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
      _start = Clock::now();
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

bool Orchestration::isConnected() { return isConnected_; }
bool Orchestration::isLogging() {
  if (_file) {
    return _file->is_open();
  } else {
    return false;
  }
}
QString Orchestration::statusString() { return statusString_; }
QString Orchestration::lastErrorString() { return lastErrorString_; }
errno_t Orchestration::lastErrorNumber() { return lastErrorNumber_; }
int Orchestration::refreshInterval() { return refreshInterval_; }
double Orchestration::refreshFrequency() { return refreshFrequency_; }
int Orchestration::manual() { return manual_; }
double Orchestration::setpoint() { return setpoint_; }
float Orchestration::kp() { return kp_; }
float Orchestration::ki() { return ki_; }
float Orchestration::kd() { return kd_; }
QString Orchestration::kpText() { return QString::number(kp_); }
QString Orchestration::kiText() { return QString::number(ki_); }
QString Orchestration::kdText() { return QString::number(kd_); }
int Orchestration::force() { return force_; }
QString Orchestration::forceText() {
  switch (force_) {
  case 0:
    return QStringLiteral(u"Off");
  case 1:
    return QStringLiteral(u"Idle");
  case 2:
    return QStringLiteral(u"Manual");
  case 3:
    return QStringLiteral(u"Automatic");
  default:
    return QStringLiteral(u"Unknown");
  }
}
float Orchestration::integral() {
  return integral_;
}
QString Orchestration::integralText() {
  return QString::number(integral_);
}

void Orchestration::setRefreshFrequency(const double& value) {
  if (refreshFrequency_ != value && value >= 0.1 && value <= 10) {
    refreshFrequency_ = value;
    setRefreshInterval(static_cast<int>(1000.0 / refreshFrequency_));
    emit refreshFrequencyChanged();
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
    emit forceTextChanged();
  }
}

void Orchestration::setForceText(const QString& value) {
  const Qt::CaseSensitivity Cis = Qt::CaseInsensitive;
  if (value.compare(QStringLiteral(u"Idle"), Cis) == 0) {
    setForce(1);
  } else if (value.compare(QStringLiteral(u"Manual"), Cis) == 0) {
    setForce(2);
  } else if (value.compare(QStringLiteral(u"Automatic"), Cis) == 0) {
    setForce(3);
  }
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
          Duration duration = Clock::now() - _start;
          Duration seconds =
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

void Orchestration::setRefreshInterval(const int& value) {
  if (refreshInterval_ != value) {
    refreshInterval_ = value;
    emit refreshIntervalChanged();
  }
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

