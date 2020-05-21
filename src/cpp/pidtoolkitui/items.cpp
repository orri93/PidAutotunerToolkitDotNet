#include <items.h>

#include <gos/pid/ui/model/models.h>

namespace gp = ::gos::pid;
namespace gptum = ::gos::pid::toolkit::ui::model;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Items::Items(QObject* parent) :
  gptum::Ptu(parent),
  serialBaud_(0),
  slaveId_(0),
  interval_(0),
  applyIntervalToController_(false),
  tuning_(gp::tuning::types::TuningMode::undefined) {
}

Items::~Items() {
}

/* Communication items */
const QString& Items::serialPort() const {
  return serialPort_;
}
const int Items::serialPortIndex() const {
  return gptum::port::index(serialPort_);
}
const int& Items::serialBaud() const {
  return serialBaud_;
}
const int Items::serialBaudIndex() const {
  return gptum::baud::index(serialBaud_);
}

/* Modbus items */
const int& Items::slaveId() const {
  return slaveId_;
}

/* Timers items */
const int& Items::interval() const {
  return interval_;
}
const int Items::intervalIndex() const {
  return gptum::interval::index(interval_);
}
const bool& Items::applyIntervalToController() const {
  return applyIntervalToController_;
}

/* Tuning items */
const gp::tuning::types::TuningMode& Items::tuning() const {
  return tuning_;
}
const int Items::tuningIndex() const {
  return gptum::tuning::index(tuning_);
}
const QString Items::tuningText() const {
  return tuningText(tuning_);
}
const bool Items::isTuning() const {
  return tuning_ != gp::tuning::types::TuningMode::undefined;
}

/* Communication items */
bool Items::applySerialPort(const QString& value) {
  if (iscompleted_ && serialPort_ != value) {
    serialPort_ = value;
    return true;
  }
  return false;
}
bool Items::applySerialPortIndex(const int& index) {
  return applySerialPort(gptum::port::value(index));
}
bool Items::applySerialBaud(const int& value) {
  if (iscompleted_ && serialBaud_ != value) {
    serialBaud_ = value;
    return true;
  }
  return false;
}
bool Items::applySerialBaudIndex(const int& index) {
  return applySerialBaud(gptum::baud::value(index));
}

/* Modbus items */
bool Items::applySlaveId(const int& value) {
  if (iscompleted_ && slaveId_ != value) {
    slaveId_ = value;
    return true;
  }
  return false;
}

/* Timers items */
bool Items::applyInterval(const int& value) {
  if (iscompleted_ && interval_ != value) {
    interval_ = value;
    return true;
  }
  return false;
}
bool Items::applyIntervalIndex(const int& value) {
  return applyInterval(gptum::interval::value(value));
}
bool Items::applyApplyIntervalToController(const bool& value) {
  if (iscompleted_ && applyIntervalToController_ != value) {
    applyIntervalToController_ = value;
    return true;
  }
  return false;
}

/* Tuning items */
bool Items::applyTuning(const gp::tuning::types::TuningMode& value) {
  if (iscompleted_ && tuning_ != value) {
    tuning_ = value;
    return true;
  }
  return false;
}
bool Items::applyTuningIndex(const int& value) {
  return applyTuning(gptum::tuning::value(value));
}
bool Items::applyTuningText(const QString& value) {
  return applyTuning(tuningMode(value));
}

/* Tuning methods */
const gp::tuning::types::TuningMode Items::tuningMode(const QString& text) {
  if (text.compare(TUNING_TEXT_BLACK_BOX, Qt::CaseInsensitive) == 0) {
    return gp::tuning::types::TuningMode::blackbox;
  }
  return gp::tuning::types::TuningMode::undefined;
}
const QString Items::tuningText(const gp::tuning::types::TuningMode& mode) {
  switch (mode) {
  case gp::tuning::types::TuningMode::blackbox:
    return TUNING_TEXT_BLACK_BOX;
  default:
    return TUNING_TEXT_OFF;
  }
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
