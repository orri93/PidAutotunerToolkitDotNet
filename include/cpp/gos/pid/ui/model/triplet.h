#ifndef GOS_PID_TUNING_UI_MODEL_TRIPLET_H_
#define GOS_PID_TUNING_UI_MODEL_TRIPLET_H_

#include <QObject>
#include <QtGlobal>
#include <QSettings>

namespace gos { namespace pid {namespace toolkit {namespace ui { 
namespace model { class Triplet; } } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::model::Triplet& lhs,
  const ::gos::pid::toolkit::ui::model::Triplet& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::model::Triplet& lhs,
  const ::gos::pid::toolkit::ui::model::Triplet& rhs);

int compare(
  const ::gos::pid::toolkit::ui::model::Triplet& first,
  const ::gos::pid::toolkit::ui::model::Triplet& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

QSettings* read(QSettings* settings, Triplet& triplet);
QSettings* read(QSettings* settings, const QString& key, Triplet& triplet);
QSettings* read(QSettings* settings, Triplet& triplet, const Triplet& default);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Triplet& triplet,
  const Triplet& default);
QSettings* read(
  QSettings* settings,
  Triplet& triplet,
  const double& kp,
  const double& ki,
  const double& kd);
QSettings* read(
  QSettings* settings,
  const QString& key,
  Triplet& triplet,
  const double& kp,
  const double& ki,
  const double& kd);
QSettings* write(QSettings * settings, const Triplet & triplet);
QSettings* write(
  QSettings * settings,
  const QString & key,
  const Triplet & triplet);

class Triplet : public QObject {
  Q_OBJECT

  Q_PROPERTY(double kp READ kp WRITE setKp NOTIFY kpChanged)
  Q_PROPERTY(double ki READ ki WRITE setKi NOTIFY kiChanged)
  Q_PROPERTY(double kd READ kd WRITE setKd NOTIFY kdChanged)

  friend bool (::operator==) (const Triplet&, const Triplet&);
  friend bool (::operator!=) (const Triplet&, const Triplet&);
  friend int(::compare) (const Triplet&, const Triplet&);

  friend QSettings* read(QSettings* settings, Triplet& triplet);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Triplet& triplet);
  friend QSettings* read(
    QSettings* settings,
    Triplet& triplet,
    const Triplet& default);
  friend QSettings* read(
    QSettings* settings,
    const QString& key,
    Triplet& triplet,
    const Triplet& default);
  friend QSettings* read(
    QSettings* settings,
    Triplet& triplet,
    const double& kp,
    const double& ki,
    const double& kd);
  friend QSettings* read(
    QSettings * settings,
    const QString & key,
    Triplet & triplet,
    const double& kp,
    const double& ki,
    const double& kd);
  friend QSettings* write(QSettings * settings, const Triplet & triplet);
  friend QSettings* write(
    QSettings * settings,
    const QString & key,
    const Triplet & triplet);

public:
  Triplet(QObject* parent = nullptr);
  Triplet(
    const double& kp,
    const double& ki,
    const double& kd,
    QObject* parent = nullptr);
  Triplet(const Triplet& triplet);

  Triplet& operator=(const Triplet& triplet);

  Triplet& set(const Triplet& triplet);
  void set(const double& kp, const double& ki, const double& kd);

  virtual const double& kp() const;
  virtual const double& ki() const;
  virtual const double& kd() const;

  virtual bool applyKp(const double& kp);
  virtual bool applyKi(const double& ki);
  virtual bool applyKd(const double& kd);

signals:
  void kpChanged();
  void kiChanged();
  void kdChanged();

public slots:
  virtual void setKp(const double& value);
  virtual void setKi(const double& value);
  virtual void setKd(const double& value);

protected:
  double kp_;
  double ki_;
  double kd_;
};

Triplet make_triplet(
  const double& kp,
  const double& ki,
  const double& kd);

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
