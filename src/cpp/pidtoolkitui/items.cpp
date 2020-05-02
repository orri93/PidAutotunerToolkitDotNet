#include <items.h>

namespace gp = ::gos::pid;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Items::Items(QObject* parent) :
  QObject(parent),
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
const int& Items::serialBaud() const {
  return serialBaud_;
}

/* Modbus items */
const int& Items::slaveId() const {
  return slaveId_;
}

/* Timers items */
const int& Items::interval() const {
  return interval_;
}
const bool& Items::applyIntervalToController() const {
  return applyIntervalToController_;
}

/* Tuning items */
const gp::tuning::types::TuningMode& Items::tuning() const {
  return tuning_;
}
const QString Items::tuningText() const {
  return tuningText(tuning_);
}

/* Tuning items */
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
