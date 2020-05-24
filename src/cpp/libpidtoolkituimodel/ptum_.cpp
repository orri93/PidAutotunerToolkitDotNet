#include <gos/pid/ui/model/ptum.h>

namespace gp = ::gos::pid;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

Ptum::Ptum(QObject* parent) :
  Ptu(parent),
  serialBaud_(0),
  slaveId_(0),
  interval_(0) {
}

Ptum::~Ptum() {
}

/* Communication items */
const QString& Ptum::serialPort() const {
  return serialPort_;
}
const int& Ptum::serialBaud() const {
  return serialBaud_;
}
/* Modbus items */
const int& Ptum::slaveId() const {
  return slaveId_;
}
/* Timers items */
const int& Ptum::interval() const {
  return interval_;
}

/* Communication items */
bool Ptum::applySerialPort(const QString& value) {
  if (iscompleted_ && serialPort_ != value) {
    serialPort_ = value;
    return true;
  }
  return false;
}
bool Ptum::applySerialBaud(const int& value) {
  if (iscompleted_ && serialBaud_ != value) {
    serialBaud_ = value;
    return true;
  }
  return false;
}
/* Modbus items */
bool Ptum::applySlaveId(const int& value) {
  if (iscompleted_ && slaveId_ != value) {
    slaveId_ = value;
    return true;
  }
  return false;
}

/* Timers items */
bool Ptum::applyInterval(const int& value) {
  if (iscompleted_ && interval_ != value) {
    interval_ = value;
    return true;
  }
  return false;
}

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
