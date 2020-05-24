#include <algorithm>

#include <gos/pid/ui/configuration/modbus.h>

/* Communication configuration */
#define GROUP_COMMUNICATION "Communication"
#define KEY_SERIAL_PORT "SerialPort"
#define KEY_SERIAL_BAUD "SerialBaud"
#define DEFAULT_SERIAL_PORT "COM1"
#define DEFAULT_SERIAL_BAUD 9600

/* Modbus configuration */
#define GROUP_MODBUS "Modbus"
#define KEY_SLAVE_ID "SlaveId"
#define DEFAULT_SLAVE_ID 1


/* PID configuration */

/* Tuning configuration */

/* Evaluation configuration */

/* Other MODBUS configuration */

namespace gpt = ::gos::pid::toolkit;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

Modbus::Modbus(QObject* parent) :
  gptum::Modbus(parent) {
}

Modbus::Modbus(const Modbus& modbus) :
  gptum::Modbus(
    dynamic_cast<const gptum::Modbus&>(modbus))
  /* Communication configuration */
  //serialPort_(modbus.serialPort_),
  //serialBaud_(modbus.serialBaud_),
  /* Modbus configuration */
  /* slaveId_(modbus.slaveId_) */ {
}

Modbus& Modbus::operator=(const Modbus& modbus) {
  set(dynamic_cast<const gptum::Modbus&>(modbus));
  return *this;
}

//Modbus& Modbus::set(const Modbus& modbus) {
//  if (this != &modbus) {
//    /* Modbus output items */
//    serialPort_ = modbus.serialPort_;
//    serialBaud_ = modbus.serialBaud_;
//    /* Modbus configuration */
//    slaveId_ = modbus.slaveId_;
//  }
//  return *this;
//}

QSettings* Modbus::read(QSettings* settings) {
  QVariant value;

  /* Communication configuration */
  settings->beginGroup(GROUP_COMMUNICATION);
  value = settings->value(KEY_SERIAL_PORT, DEFAULT_SERIAL_PORT);
  setSerialPort(value.toString());
  value = settings->value(KEY_SERIAL_BAUD, DEFAULT_SERIAL_BAUD);
  setSerialBaud(value.toInt());
  settings->endGroup();

  /* Modbus configuration */
  settings->beginGroup(GROUP_MODBUS);
  value = settings->value(KEY_SLAVE_ID, DEFAULT_SLAVE_ID);
  setSlaveId(value.toInt());
  settings->endGroup();

  return settings;
}

QSettings* Modbus::write(QSettings* settings) {

  /* Communication configuration */
  settings->beginGroup(GROUP_COMMUNICATION);
  settings->setValue(KEY_SERIAL_PORT, serialPort_);
  settings->setValue(KEY_SERIAL_BAUD, serialBaud_);
  settings->endGroup();

  /* Modbus configuration */
  settings->beginGroup(GROUP_MODBUS);
  settings->setValue(KEY_SLAVE_ID, slaveId_);
  settings->endGroup();

  return settings;
}

/* Modbus output items */
//const QString& Modbus::serialPort() const { return serialPort_; }
//const int& Modbus::serialBaud() const { return serialBaud_; }

/* Modbus configuration */
//const int& Modbus::slaveId() const { return slaveId_; }

/* Communication items */
//bool Modbus::applySerialPort(const QString& value) {
//  if (serialPort_ != value) {
//    serialPort_ = value;
//    return true;
//  }
//  return false;
//}
//bool Modbus::applySerialBaud(const int& value) {
//  if (serialBaud_ != value) {
//    serialBaud_ = value;
//    return true;
//  }
//  return false;
//}
/* Modbus items */
//bool Modbus::applySlaveId(const int& value) {
//  if (slaveId_ != value) {
//    slaveId_ = value;
//    return true;
//  }
//  return false;
//}


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

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptuc::Modbus& lhs, const gptuc::Modbus& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptuc::Modbus& lhs, const gptuc::Modbus& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptuc::Modbus& first, const gptuc::Modbus& second) {
  return (
    /* Modbus output items */
    first.serialPort_ == second.serialPort_&&
    first.serialBaud_ == second.serialBaud_&&
    first.slaveId_ == second.slaveId_) ? 0 : 1;
}
