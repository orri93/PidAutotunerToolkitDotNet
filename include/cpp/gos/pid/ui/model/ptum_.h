#ifndef GOS_PID_TUNING_UI_MODEL_PTUM_H_
#define GOS_PID_TUNING_UI_MODEL_PTUM_H_

#include <memory>

#include <QObject>
#include <QString>

#include <gos/pid/arduino/types.h>
#include <gos/pid/tuning/types.h>
#include <gos/pid/ui/model/ptu.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

class Ptum : public Ptu {
  Q_OBJECT
public:
  explicit Ptum(QObject* parent = nullptr);
  virtual ~Ptum();

  /* Communication items */
  virtual const QString& serialPort() const;
  virtual const int& serialBaud() const;

  /* Modbus items */
  virtual const int& slaveId() const;

  /* Timers items */
  virtual const int& interval() const;

protected:
  /* Communication items */
  virtual bool applySerialPort(const QString& value);
  virtual bool applySerialBaud(const int& value);

  /* Modbus items */
  virtual bool applySlaveId(const int& value);

  /* Timers items */
  virtual bool applyInterval(const int& value);

  /* Communication configuration */
  QString serialPort_;
  int serialBaud_;
  /* Modbus configuration */
  int slaveId_;
  /* Timers configuration */
  int interval_;
};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
