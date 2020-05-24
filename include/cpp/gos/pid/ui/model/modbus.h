#ifndef GOS_PID_TUNING_UI_MODEL_MODBUS_H_
#define GOS_PID_TUNING_UI_MODEL_MODBUS_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/arduino/types.h>
#include <gos/pid/arduino/modbus/types.h>

#include <gos/pid/ui/model/ptu.h>
#include <gos/pid/ui/model/status.h>
#include <gos/pid/ui/model/triplet.h>
#include <gos/pid/ui/model/force.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

/**
 * @brief The Modbus View Model class.
*/
class Modbus : public Ptu {
  Q_OBJECT

  /* Communication items */

  /**
   * @brief The Serial Port to use for the Modbus communication.
  */
  Q_PROPERTY(QString serialPort READ serialPort WRITE setSerialPort NOTIFY serialPortChanged)
  /**
   * @brief The Serial Baud to use for the Modbus communication.
  */
  Q_PROPERTY(int serialBaud READ serialBaud WRITE setSerialBaud NOTIFY serialBaudChanged)

  /* Modbus items */

  /**
   * @brief The Slave ID for the Arduino Controller (usually 1)
  */
  Q_PROPERTY(int slaveId READ slaveId WRITE setSlaveId NOTIFY slaveIdChanged)

public:
  explicit Modbus(QObject* parent = nullptr);
  Modbus(const Modbus& modbus);

  virtual Modbus& set(const Modbus& modbus);

  /* Modbus output items */
  virtual const QString& serialPort() const;
  virtual const int& serialBaud() const;

  /* Modbus items */
  virtual const int& slaveId() const;

  /* Modbus output items */
  virtual bool Modbus::applySerialPort(const QString& value);
  virtual bool Modbus::applySerialBaud(const int& value);

  /* Modbus items */
  virtual bool Modbus::applySlaveId(const int& value);

  /* Other items */

signals:
  /* Communication items */
  void serialPortChanged();
  void serialBaudChanged();
  /* Modbus items */
  void slaveIdChanged();

  /* Other items */

public slots:
  /* Communication items */
  virtual void setSerialPort(const QString& value);
  virtual void setSerialBaud(const int& value);
  /* Modbus items */
  virtual void setSlaveId(const int& value);

  /* Other items */

private slots:

protected:

  /* Communication configuration */
  QString serialPort_;
  int serialBaud_;
  /* Modbus configuration */
  int slaveId_;
};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
