#include <QDebug>

#include <gos/pid/toolkit/exception.h>

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
  Ptu(parent),
  serialBaud_(0),
  slaveId_(0) {
}

Modbus::Modbus(const Modbus& modbus) :
  /* Modbus output items */
  serialPort_(modbus.serialPort_),
  serialBaud_(modbus.serialBaud_),
  /* Modbus configuration */
  slaveId_(modbus.slaveId_) {
}

Modbus& Modbus::set(const Modbus& modbus) {
  if (this != &modbus) {
    /* Modbus output items */
    serialPort_ = modbus.serialPort_;
    serialBaud_ = modbus.serialBaud_;
    /* Modbus configuration */
    slaveId_ = modbus.slaveId_;
  }
  return *this;
}

/* Modbus output items */
const QString& Modbus::serialPort() const { return serialPort_; }
const int& Modbus::serialBaud() const { return serialBaud_; }

/* Modbus configuration */
const int& Modbus::slaveId() const { return slaveId_; }

/* Other items */

/* Communication items */
bool Modbus::applySerialPort(const QString& value) {
  if (serialPort_ != value) {
    serialPort_ = value;
    return true;
  }
  return false;
}
bool Modbus::applySerialBaud(const int& value) {
  if (serialBaud_ != value) {
    serialBaud_ = value;
    return true;
  }
  return false;
}
/* Modbus items */
bool Modbus::applySlaveId(const int& value) {
  if (slaveId_ != value) {
    slaveId_ = value;
    return true;
  }
  return false;
}

/* Communication configuration */
void Modbus::setSerialPort(const QString& value) {
  if (applySerialPort(value)) {
    emit serialPortChanged();
  }
}
void Modbus::setSerialBaud(const int& value) {
  if (applySerialBaud(value)) {
    emit serialBaudChanged();
  }
}
/* Modbus items */
void Modbus::setSlaveId(const int& value) {
  if (applySlaveId(value)) {
    emit slaveIdChanged();
  }
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
