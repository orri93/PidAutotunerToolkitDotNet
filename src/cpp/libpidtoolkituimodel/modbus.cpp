#include <QDebug>

#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/arduino/modbus/retry.h>

#include <gos/pid/ui/model/modbus.h>

namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;

namespace gpa = ::gos::pid::arduino;
namespace gpam = ::gos::pid::arduino::modbus;
namespace gpat = ::gos::pid::arduino::types;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Modbus::Modbus(QObject* parent) :
  Ptum(parent),
  isLastMessageError_(false),
  /* Status items */
  status_(gptum::Status::Enum::Undefined),
  //isInitialize_(false),
  /* Controller input items */
  setpoint_(0.0),
  manual_(0),
  /* Controller settings items */
  force_(0),
  /* Controller tuning items */
  kp_(0.0),
  ki_(0.0),
  kd_(0.0),
  /* Controller output items */
  temperature_(0.0),
  output_(0.0),
  integral_(0.0) {
}

Modbus::~Modbus() {
  shutdown();
}

bool Modbus::initialize() {
  status_ = gptum::Status::Enum::Disconnected;
  //isInitialize_ = true;
  //emit isInitializeChanged();
  qInfo() << "Initialize Modbus completed";
  //return isInitialize_;
  gpam::types::result result;
  std::string serialport = serialPort_.toStdString();
  result = gpam::master::initialize(
    serialport.c_str(),
    serialBaud_,
    slaveId_);
  if (result == gpam::types::result::success) {
    // TODO: Find out what these two do?
    //applyConfiguration();
    //connectConfiguration();
    return true;
  } else {
    qWarning() << "Failed to initialize Modbus Master";
  }
  return false;

}

void Modbus::shutdown() {
  switch (status_) {
  case gptum::Status::Enum::Connected:
    gpam::master::disconnect();
    status_ = gptum::Status::Enum::Disconnected;
    break;
  }
  gpam::master::shutdown();
}

bool Modbus::connectDisconnect() {
  bool bret = false;
  gpam::types::result result;
  switch (status_) {
  case gptum::Status::Enum::Connected:
    setStatus(gptum::Status::Enum::Disconnecting);
    result = gpam::master::disconnect();
    if (result == gpam::types::result::success) {
      result = gpam::master::shutdown();
      if (result == gpam::types::result::success) {
        setLastMessage("Disconnected successfully");
        bret = true;
      } else {
        setLastError("Shutdown failed");
      }
      setStatus(gptum::Status::Enum::Disconnected);
    } else {
      setLastError("Disconnecting failed" + QString::fromStdString(
        gpam::master::report::error::last()));
      setStatus(gptum::Status::Enum::Connected);
    }
    break;
  case gptum::Status::Enum::Disconnected:
    setStatus(gptum::Status::Enum::Connecting);
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
          //if (applyIntervalToController()) {
          //  writeInterval(static_cast<gpa::types::Unsigned>(interval()));
          //}
          setStatus(gptum::Status::Enum::Connected);
          bret = true;
          setLastMessage("Connected successfully");
        } else {
          setLastError("Reading initial holdings failed: " +
            QString::fromStdString(gpam::master::report::error::last()));
          setStatus(gptum::Status::Enum::Disconnected);
        }
      } else {
        setLastError("Connecting failed: " +
          QString::fromStdString(gpam::master::report::error::last()));
        setStatus(gptum::Status::Enum::Disconnected);
      }
    } else {
      setLastError("Initializing Modbus Master failed: " +
        QString::fromStdString(gpam::master::report::error::last()));
      setStatus(gptum::Status::Enum::Disconnected);
    }
    break;
  default:
    break;
  }
  return bret;
}

/* Status items */
const gptum::Status::Enum Modbus::status() const { return status_; }
//const bool& Modbus::isInitialize() const { return isInitialize_; }
//const bool& Modbus::isCompleted() const { return iscompleted_; }
const bool Modbus::isConnected() const {
return status_ == gptum::Status::Enum::Connected;
}
const QString& Modbus::lastMessage() const { return lastMessage_; }
const bool& Modbus::isLastMessageError() const { return isLastMessageError_; }

/* Controller input items */
const int& Modbus::manual() const { return manual_; }
const double& Modbus::setpoint() const { return setpoint_; }

/* Controller settings items */
const int& Modbus::force() const { return force_; }

/* Controller tuning items */
const double& Modbus::kp() const { return kp_; }
const double& Modbus::ki() const { return ki_; }
const double& Modbus::kd() const { return kd_; }

/* Controller output items */
const double& Modbus::temperature() const {
  return temperature_;
}
const double& Modbus::output() const {
  return output_;
}
const double& Modbus::integral() const {
  return integral_;
}
/* Other items */

/* Communication items */
void Modbus::setSerialPort(const QString& value) {
  // Todo if connected ask user if want to disconnect and connect again
  if (applySerialPort(value)) {
    qDebug() << "Setting serial port to " << value;
    emit serialPortChanged();
  }
}
void Modbus::setSerialBaud(const int& value) {
  // Todo if connected ask user if want to disconnect and connect again
  if (applySerialBaud(value)) {
    qDebug() << "Setting serial baud to " << value;
    emit serialBaudChanged();
  }
}
/* Timers items */
void Modbus::setInterval(const int& value) {
  if (applyInterval(value)) {
    if (isConnected()) {
      writeInterval(static_cast<gpa::types::Unsigned>(interval()));
    }
    emit intervalChanged();
  }
}
/* Controller input items */
void Modbus::setManual(const int& manual) {
  bool result;
  if (manual_ != manual && manual >= 0 && manual <= 255) {
    switch (status_) {
    case gptum::Status::Enum::Connected:
      result = writeManual(static_cast<gpa::types::Unsigned>(manual));
      if (result) {
        qDebug() << "Successfully set Manual to " << manual;
      } else {
        qWarning() << "Failed to set Manual to " << manual << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptum::Status::Enum::Connecting:
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
void Modbus::setSetpoint(const double& setpoint) {
  bool result;
  if (setpoint_ != setpoint && setpoint >= 0.0 && setpoint <= 300.0) {
    switch (status_) {
    case gptum::Status::Enum::Connected:
      result = writeSetpoint(static_cast<gpa::types::Real>(setpoint));
      if (result) {
        qDebug() << "Successfully set Setpoint to " << setpoint;
      } else {
        qWarning() << "Failed to set Setpoint to " << setpoint << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptum::Status::Enum::Connecting:
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
void Modbus::setForce(const int& value) {
  bool result;
  if (force_ != value && value > 0 && value <= 3) {
    switch (status_) {
    case gptum::Status::Enum::Connected:
      result = writeForce(static_cast<gpa::types::Unsigned>(value));
      if (result) {
        qDebug() << "Successfully set Force to " << value;
      } else {
        qWarning() << "Failed to set Force to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptum::Status::Enum::Connecting:
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

void Modbus::setKp(const double& value) {
  bool result;
  if (kp_ != value && value >= 0.0 && value <= 100.0) {
    switch (status_) {
    case gptum::Status::Enum::Connected:
      result = writeKp(static_cast<gpa::types::Real>(value));
      if (result) {
        qDebug() << "Successfully set Kp to " << value;
      } else {
        qWarning() << "Failed to set Kp to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptum::Status::Enum::Connecting:
      break;
    default:
      qDebug() << "Not connected when Kp changed from "
        << kp_ << " to " << value;
      break;
    }
    kp_ = value;
    emit kpChanged();
  }
}
void Modbus::setKi(const double& value) {
  bool result;
  if (ki_ != value && value >= 0.0 && value <= 100.0) {
    switch (status_) {
    case gptum::Status::Enum::Connected:
      result = writeKi(static_cast<gpa::types::Real>(value));
      if (result) {
        qDebug() << "Successfully set Ki to " << value;
      } else {
        qWarning() << "Failed to set Ki to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptum::Status::Enum::Connecting:
      break;
    default:
      qDebug() << "Not connected when Ki changed from "
        << ki_ << " to " << value;
      break;
    }
    ki_ = value;
    emit kiChanged();
  }
}
void Modbus::setKd(const double& value) {
  bool result;
  if (kd_ != value && value >= 0.0 && value <= 100.0) {
    switch (status_) {
    case gptum::Status::Enum::Connected:
      result = writeKd(static_cast<gpa::types::Real>(value));
      if (result) {
        qDebug() << "Successfully set Kd to " << value;
      } else {
        qWarning() << "Failed to set Kd to " << value << " error is " <<
          QString::fromStdString(gpam::master::report::error::last());
      }
      break;
    case gptum::Status::Enum::Connecting:
      break;
    default:
      qDebug() << "Not connected when Kd changed from "
        << kd_ << " to " << value;
      break;
    }
    kd_ = value;
    emit kdChanged();
  }
}

/* Communication items */

/* Status items */
void Modbus::setStatus(const gptum::Status::Enum& status) {
  if (status_ != status) {
    status_ = status;
    emit statusChanged();
  }
}
void Modbus::setLastMessage(const QString& message, const bool isLastMessageError) {
  isLastMessageError_ = isLastMessageError;
  if (lastMessage_ != message) {
    lastMessage_ = message;
    emit lastMessageChanged();
  }
}
void Modbus::setLastError(const QString& message) {
  setLastMessage(message, true);
}
/* Controller input items */

/* Controller settings items */

/* Controller tuning items */

/* Controller output items */
void Modbus::setTemperature(const gpat::Real& value) {
  double asdouble = static_cast<double>(value);
  if (temperature_ != asdouble) {
    temperature_ = asdouble;
    emit temperatureChanged();
  }
}
void Modbus::setOutput(const gpat::Unsigned& value) {
  double asdouble = static_cast<double>(value);
  if (output_ != asdouble) {
    output_ = asdouble;
    emit outputChanged();
  }
}
void Modbus::setIntegral(const float& value) {
  if (integral_ != value) {
    integral_ = value;
    emit integralChanged();
  }
}

/* Other items */

bool Modbus::writeManual(const gpa::types::Unsigned& manual) {
  return gpam::master::retry::write::manual(manual) ==
    gpam::types::result::success;
}

bool Modbus::writeSetpoint(const gpa::types::Real& setpoint) {
  return gpam::master::retry::write::setpoint(setpoint) ==
    gpam::types::result::success;
}

bool Modbus::writeKp(const gpa::types::Real& kp) {
  return gpam::master::retry::write::kp(kp) ==
    gpam::types::result::success;
}

bool Modbus::writeKi(const gpa::types::Real& ki) {
  return gpam::master::retry::write::ki(ki) ==
    gpam::types::result::success;
}

bool Modbus::writeKd(const gpa::types::Real& kd) {
  return gpam::master::retry::write::kd(kd) ==
    gpam::types::result::success;
}

bool Modbus::writeForce(const gpa::types::Unsigned& force) {
  return gpam::master::retry::write::force(force) ==
    gpam::types::result::success;
}

bool Modbus::writeInterval(const gpa::types::Unsigned& interval) {
  return gpam::master::retry::write::interval(interval) ==
    gpam::types::result::success;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
