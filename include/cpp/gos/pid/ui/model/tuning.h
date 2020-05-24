#ifndef GOS_PID_TUNING_UI_MODEL_TUNING_H_
#define GOS_PID_TUNING_UI_MODEL_TUNING_H_

#include <QObject>
#include <QVariant>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/tuning/types.h>
#include <gos/pid/tuning/notify.h>

#include <gos/pid/arduino/types.h>
#include <gos/pid/arduino/modbus/types.h>

#include <gos/pid/ui/model/ptu.h>
#include <gos/pid/ui/model/enumerate.h>
#include <gos/pid/ui/model/triplet.h>
#include <gos/pid/ui/model/modbus.h>
#include <gos/pid/ui/model/force.h>
#include <gos/pid/ui/model/types.h>

#include <gos/pid/ui/configuration/blackbox.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

namespace tuning {
class Method : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    None,
    BlackBox
  };
  enum MethodRoles {
    ValueRole = Qt::UserRole + 1,
    TextRole
  };
  Q_ENUM(Enum)
  Q_ENUM(MethodRoles)
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, MethodRoles> EnumerateModel;
  Method(QObject* parent = nullptr);
  Q_INVOKABLE int index(const Enum& method);
  Q_INVOKABLE Enum method(const int& index);
  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  static EnumerateModel& enumerateModel();
protected:
  QHash<int, QByteArray> roleNames() const;
private:
  static EnumerateModel EnumerateModel_;
};
}

class Tuning : public Ptu {
  Q_OBJECT

  /* Tuning items */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::tuning::Method::Enum method READ method WRITE setMethod NOTIFY methodChanged)

  /* Controller tuning items */
  Q_PROPERTY(double kp READ kp NOTIFY kpChanged)
  Q_PROPERTY(double ki READ ki NOTIFY kiChanged)
  Q_PROPERTY(double kd READ kd NOTIFY kdChanged)

public:
  Tuning(QObject* parent = nullptr);
  Tuning(const Tuning& tuning);

  virtual Tuning& set(const Tuning& tuning);

  /* Tuning items */
  virtual const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method() const;

  /* Controller tuning items */
  virtual const double& kp() const;
  virtual const double& ki() const;
  virtual const double& kd() const;

    /* Tuning items */
  virtual bool applyMethod(
    const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method);

  virtual bool applyKp(const double& value);
  virtual bool applyKi(const double& value);
  virtual bool applyKd(const double& value);

signals:
  /* Tuning items */
  void methodChanged();

  /* Controller tuning items */
  void kpChanged();
  void kiChanged();
  void kdChanged();

public slots:
  virtual void setMethod(
    const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method);

protected:
  
  /* Controller tuning items */
  virtual void setKp(const double& value);
  virtual void setKi(const double& value);
  virtual void setKd(const double& value);

  ::gos::pid::toolkit::ui::model::tuning::Method::Enum method_;

  /* Controller tuning items */
  ::gos::pid::toolkit::ui::model::Triplet triplet_;

  /* Modbus items */

  /* Tuning items */
};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
