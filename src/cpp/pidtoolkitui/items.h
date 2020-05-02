#ifndef GOS_PID_TUNING_UI_ITEMS_H_
#define GOS_PID_TUNING_UI_ITEMS_H_

#include <QtCore/QObject>

#include <gos/pid/arduino/types.h>

#include <gos/pid/tuning/types.h>

#define TUNING_TEXT_OFF "Off"
#define TUNING_TEXT_BLACK_BOX "BlackBox"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Items : public QObject {
  Q_OBJECT
public:
  Items(QObject* parent = nullptr);

  virtual ~Items();

  /* Communication items */
  virtual const QString& serialPort() const;
  virtual const int& serialBaud() const;

  /* Modbus items */
  virtual const int& slaveId() const;

  /* Timers items */
  virtual const int& interval() const;
  virtual const bool& applyIntervalToController() const;

  /* Tuning items */
  virtual const ::gos::pid::tuning::types::TuningMode& tuning() const;
  virtual const QString tuningText() const;

protected:

  /* Tuning items */
  static const ::gos::pid::tuning::types::TuningMode tuningMode(const QString& text);
  static const QString tuningText(const ::gos::pid::tuning::types::TuningMode& mode);

  /* Communication configuration */
  QString serialPort_;
  int serialBaud_;
  /* Modbus configuration */
  int slaveId_;
  /* Timers configuration */
  int interval_;
  bool applyIntervalToController_;
  /* Tuning configuration */
  ::gos::pid::tuning::types::TuningMode tuning_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif