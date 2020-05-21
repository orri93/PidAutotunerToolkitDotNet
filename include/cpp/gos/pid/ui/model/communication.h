#ifndef GOS_PID_TUNING_UI_MODEL_COMMUNICATION_H_
#define GOS_PID_TUNING_UI_MODEL_COMMUNICATION_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/range.h>
#include <gos/pid/ui/model/format.h>
#include <gos/pid/ui/model/restriction.h>

#define KEY_BB_COMMUNICATION_RANGE "Range"
#define KEY_BB_COMMUNICATION_PRECISION "Precision"
#define KEY_BB_COMMUNICATION_RESTRICTION "Restriction"

#define DEFAULT_BB_COMMUNICATION_PRECISION 0

namespace gos { namespace pid { namespace toolkit { namespace ui {
namespace model { class Communication; } } } } }

int compare(
  const ::gos::pid::toolkit::ui::model::Communication& first,
  const ::gos::pid::toolkit::ui::model::Communication& second);

bool operator==(
  const ::gos::pid::toolkit::ui::model::Communication& lhs,
  const ::gos::pid::toolkit::ui::model::Communication& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::model::Communication& lhs,
  const ::gos::pid::toolkit::ui::model::Communication& rhs);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

QSettings* read(QSettings* settings, const QString& key, Communication& communication);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Communication& communication,
  const Communication& default);
QSettings* write(
  QSettings* settings,
  const QString& key,
  const Communication& communication);

class Communication : public Format {
  Q_OBJECT

  Q_PROPERTY(QString serialPort READ serialPort_ WRITE setSerialPort NOTIFY serialPortChanged)
  Q_PROPERTY(int serialBaud READ serialBaud_ WRITE setSerialBaud NOTIFY serialBaudChanged)

  friend bool(::operator==) (const Communication& lhs, const Communication& rhs);
  friend bool(::operator!=) (const Communication& lhs, const Communication& rhs);
  friend int(::compare) (const Communication& first, const Communication& second);

  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Communication& communication);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Communication& communication,
    const Communication& default);
  friend QSettings* write(
    QSettings* settings,
    const QString& key,
    const Communication& communication);

public:
  explicit Communication(QObject* parent = nullptr);
  Communication(
    const QString& serialPort,
    const int& serialBaud,
    QObject* parent = nullptr);
  Communication(const Communication& communication);
  Communication& operator=(const Communication& communication);

  Communication& set(const Communication& communication);
  void set(const QString& serialPort, const int& serialBaud);

signals:
  void serialPortChanged();
  void serialBaudChanged();

public slots:
  void setSerialPort(const QString& value);
  void setSerialBaud(const int& value);

private:
  Range range_;
  ::gos::pid::toolkit::ui::model::Restriction::Enum restriction_;
};

Communication make_communication(
  const ::gos::pid::toolkit::ui::model::Restriction::Enum& restriction,
  const Range& range,
  const int& precision);

Communication make_communication(const int& precision);

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
