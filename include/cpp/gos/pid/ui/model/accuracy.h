#ifndef GOS_PID_TUNING_UI_MODEL_ACCURACY_H_
#define GOS_PID_TUNING_UI_MODEL_ACCURACY_H_

#include <QObject>
#include <QSettings>

#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/format.h>
#include <gos/pid/ui/model/number.h>

#define KEY_BB_ACCURACY_NUMBER "Number"
#define KEY_BB_ACCURACY_FORMAT "Format"

#define DEFAULT_BB_ACCURACY_PRECISION 0

namespace gos { namespace pid { namespace toolkit { namespace ui {
namespace model { class Accuracy; } } } } }

int compare(
  const ::gos::pid::toolkit::ui::model::Accuracy& first,
  const ::gos::pid::toolkit::ui::model::Accuracy& second);

bool operator==(
  const ::gos::pid::toolkit::ui::model::Accuracy& lhs,
  const ::gos::pid::toolkit::ui::model::Accuracy& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::model::Accuracy& lhs,
  const ::gos::pid::toolkit::ui::model::Accuracy& rhs);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

QSettings* read(QSettings* settings, const QString& key, Accuracy& accuracy);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Format& format);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Number& number,
  const Format& format);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Accuracy& accuracy,
  const Accuracy& default);
QSettings* write(
  QSettings * settings,
  const QString & key,
  const Accuracy & accuracy);

class Accuracy : public QObject {
  Q_OBJECT

  Q_PROPERTY(Number* number READ number WRITE setNumber NOTIFY numberChanged)
  Q_PROPERTY(Format* format READ format WRITE setFormat NOTIFY formatChanged)

  friend bool(::operator==) (const Accuracy& lhs, const Accuracy& rhs);
  friend bool(::operator!=) (const Accuracy& lhs, const Accuracy& rhs);
  friend int(::compare) (const Accuracy& first, const Accuracy& second);

  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Accuracy& accuracy);
  friend QSettings* read(
    QSettings * settings,
    const QString & key,
    Accuracy & accuracy,
    const Format& format);
  friend QSettings* read(
    QSettings * settings,
    const QString & key,
    Accuracy & accuracy,
    const Number& number,
    const Format& format);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Accuracy& accuracy,
    const Accuracy& default);
  friend QSettings* write(
    QSettings * settings,
    const QString & key,
    const Accuracy & accuracy);

public:
  explicit Accuracy(QObject* parent = nullptr);
  Accuracy(
    const Number& number,
    const Format& format,
    QObject* parent = nullptr);
  Accuracy(
    const Format& format,
    QObject* parent = nullptr);
  Accuracy(const Accuracy& accuracy);
  Accuracy& operator=(const Accuracy& accuracy);

  Accuracy& set(const Accuracy& accuracy);
  void set(const Number& number, const Format& format);
  void set(const Format& format);

  Number* number();
  Format* format();

signals:
  void numberChanged();
  void formatChanged();

public slots:
  void setNumber(const Number* number);
  void setFormat(const Format* format);

private:
  void setNumber(const Number& number);
  void setFormat(const Format& format);

  Number number_;
  Format format_;
};

Accuracy make_accuracy(const Number& number, const Format& format);
Accuracy make_accuracy(const Format& format);

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
