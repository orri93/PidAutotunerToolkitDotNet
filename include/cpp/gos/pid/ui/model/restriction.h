#ifndef GOS_PID_TUNING_UI_MODEL_RESTRICTION_H_
#define GOS_PID_TUNING_UI_MODEL_RESTRICTION_H_

#include <QObject>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/ui/model/enumerate.h>

#define GOS_QML_MODEL_RESTRICTION "restrictionModel"

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

class Restriction : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    None,
    Minimum,
    Maximum,
    Both
  };
  enum RestrictionRoles {
    TextRole = Qt::UserRole + 1,
    ValueRole
  };
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, RestrictionRoles> EnumerateModel;
  Q_ENUM(Enum)
  Q_ENUM(RestrictionRoles)

  Restriction(QObject* parent = nullptr);

  Q_INVOKABLE int index(const Enum& restriction);
  Q_INVOKABLE Enum restriction(const int& index);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  static EnumerateModel& enumerateModel();

protected:
  QHash<int, QByteArray> roleNames() const;
private:

  static EnumerateModel EnumerateModel_;
};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
