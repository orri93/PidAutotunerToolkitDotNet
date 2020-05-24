#ifndef GOS_PID_TUNING_UI_CONFIGURATION_MODBUS_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_MODBUS_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QDebug>

#include <gos/pid/ui/model/modbus.h>

#define GOS_QML_TYPE_MODBUS_NAME "ModbusSetting"
#define GOS_QML_TYPE_MODBUS_URI GOS_QML_TYPE_MODBUS_NAME

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace configuration { class Modbus; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::configuration::Modbus& lhs,
  const ::gos::pid::toolkit::ui::configuration::Modbus& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::configuration::Modbus& lhs,
  const ::gos::pid::toolkit::ui::configuration::Modbus& rhs);

int compare(
  const ::gos::pid::toolkit::ui::configuration::Modbus& first,
  const ::gos::pid::toolkit::ui::configuration::Modbus& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace configuration {

class Modbus : public ::gos::pid::toolkit::ui::model::Modbus {
  Q_OBJECT

  /* Communication configuration */
  //Q_PROPERTY(QString serialPort READ serialPort WRITE setSerialPort NOTIFY serialPortChanged)
  //Q_PROPERTY(int serialBaud READ serialBaud WRITE setSerialBaud NOTIFY serialBaudChanged)

  /* Modbus configuration */
  //Q_PROPERTY(int slaveId READ slaveId NOTIFY slaveIdChanged)

  friend bool (::operator==) (const Modbus&, const Modbus&);
  friend bool (::operator!=) (const Modbus&, const Modbus&);
  friend int(::compare) (const Modbus&, const Modbus&);

public:

  explicit Modbus(QObject* parent = nullptr);

  Modbus(const Modbus& modbus);

  Modbus& operator=(const Modbus& modbus);

  //Modbus& set(const Modbus& modbus);

  QSettings* read(QSettings* settings);
  QSettings* write(QSettings* settings);

  /* Modbus output items */
  //const QString& serialPort() const;
  //const int& serialBaud() const;

  /* Modbus configuration */
  //const int& slaveId() const;

  /* Modbus output items */
  //bool Modbus::applySerialPort(const QString& value);
  //bool Modbus::applySerialBaud(const int& value);

  /* Modbus configuration */
  //bool Modbus::applySlaveId(const int& value);

signals:
  /* Communication configuration */
  //void serialPortChanged();
  //void serialBaudChanged();
  /* Modbus configuration */
  //void slaveIdChanged();

public slots:
  /* Communication configuration */
  void setSerialPort(const QString& value);
  void setSerialBaud(const int& value);
  /* Modbus configuration */
  void setSlaveId(const int& value);

protected:
  void create();

  /* Communication configuration */
  //QString serialPort_;
  //int serialBaud_;
  /* Modbus configuration */
  //int slaveId_;
};

typedef std::unique_ptr<Modbus> ModbusPointer;

} // namespace configuration
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos


#endif
