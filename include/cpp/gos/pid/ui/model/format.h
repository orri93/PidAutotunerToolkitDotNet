#ifndef GOS_PID_TUNING_UI_MODEL_FORMAT_H_
#define GOS_PID_TUNING_UI_MODEL_FORMAT_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/ptu.h>

#define KEY_BB_FORMAT_PRECISION "Precision"
#define DEFAULT_BB_FORMAT_PRECISION 0

namespace gos { namespace pid { namespace toolkit { namespace ui {
namespace model { class Format; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::model::Format& lhs,
  const ::gos::pid::toolkit::ui::model::Format& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::model::Format& lhs,
  const ::gos::pid::toolkit::ui::model::Format& rhs);

int compare(
  const ::gos::pid::toolkit::ui::model::Format& first,
  const ::gos::pid::toolkit::ui::model::Format& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

QSettings* read(QSettings* settings, const QString& key, Format& format);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Format& format,
  const int& precision);
QSettings* write(QSettings* settings, const QString& key, const Format& format);

class Format : public Ptu {
  Q_OBJECT

  Q_PROPERTY(int precision MEMBER precision_ WRITE setPrecision NOTIFY precisionChanged)

  friend bool(::operator==) (const Format& lhs, const Format& rhs);
  friend bool(::operator!=) (const Format& lhs, const Format& rhs);
  friend int(::compare) (const Format& first, const Format& second);

  friend QSettings* read(QSettings* settings, const QString& key, Format& format);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Format& format,
    const int& precision);
  friend QSettings* write(
    QSettings* settings,
    const QString& key,
    const Format& format);

public:
  explicit Format(QObject* parent = nullptr);
  Format(
    const int& precision,
    QObject* parent = nullptr);
  Format(const Format& format);
  virtual Format& operator=(const Format& format);

  Format& set(const Format& format);
  virtual void set(const int& precision);

signals:
  void precisionChanged();

public slots:
  void setPrecision(const int& value);

protected:
  int precision_;
};

Format make_format(const int& precision);

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
