#ifndef GOS_PID_TUNING_UI_MODEL_PTU_H_
#define GOS_PID_TUNING_UI_MODEL_PTU_H_

#include <memory>

#include <QDebug>
#include <QObject>
#include <QtGlobal>
#include <QSettings>
#include <QAbstractListModel>

#include <gos/pid/ui/model/enumerate.h>

#include <gos/pid/ui/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

namespace ptu {
class Status : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    Startup,
    Initializing,
    Writing,        /* Only for Configuration? */
    Idle            /* The normal state of item after startup and initialize */
  };
  enum PtuStatusRoles {
    TextRole = Qt::UserRole + 1,
    ValueRole
  };
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, PtuStatusRoles> EnumerateModel;
  Q_ENUM(Enum)
  Q_ENUM(PtuStatusRoles)

  Status(QObject* parent = nullptr);

  Q_INVOKABLE int index(const Enum& status);
  Q_INVOKABLE Enum status(const int& index);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  static EnumerateModel& enumerateModel();

protected:
  QHash<int, QByteArray> roleNames() const;
private:

  static EnumerateModel EnumerateModel_;
};
}

class Ptu : public QObject {
  Q_OBJECT

  Q_PROPERTY(::gos::pid::toolkit::ui::model::ptu::Status::Enum ptStatus READ ptStatus NOTIFY ptStatusChanged)
  Q_PROPERTY(bool ptReady READ ptReady)

  Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY lastMessageChanged)
  Q_PROPERTY(bool isLastMessageError READ isLastMessageError)

public:
  explicit Ptu(QObject* parent = nullptr);
  virtual ~Ptu();

  virtual bool initialize();

  virtual QSettings* read(QSettings* settings);
  virtual QSettings* write(QSettings* settings);

  const ::gos::pid::toolkit::ui::model::ptu::Status::Enum& ptStatus() const;
  const bool ptReady() const;

  const QString& lastMessage() const;
  const bool& isLastMessageError() const;

signals:
  void ptStatusChanged();
  void lastMessageChanged();

protected:

  /* Messages helpers */
  void setLastMessage(const QString& message, const bool isLastMessageError = false);
  void setLastError(const QString& message);

  /* Status helpers */
  virtual void startup();
  virtual void initializing();
  virtual void writing();
  virtual void idle();

  virtual bool applyPtStatus(
    const ::gos::pid::toolkit::ui::model::ptu::Status::Enum& status);

  virtual void setPtStatus(
    const ::gos::pid::toolkit::ui::model::ptu::Status::Enum& status);

  template<typename T> bool canApplyPointer(T* internal, T* external) {
    return external != nullptr && external != internal;
  }

  template<typename T> bool applyPointer(T*& internal, T* external) {
    if (canApplyPointer(internal, external)) {
      internal = external;
      return true;
    }
    return false;
  }

  template<typename T> bool applyComparePointer(T*& internal, T* external) {
    if (canApplyPointer(internal, external)) {
      if (*internal != *external) {
        internal = external;
        return true;
      }
    }
    return false;
  }

  template<typename T> bool applyPointer(
    std::unique_ptr<T>& internal, T* external) {
    if (canApplyPointer(internal.get(), external)) {
      internal.reset(external);
      return true;
    }
    return false;
  }

  template<typename T> bool applyComparePointer(
    std::unique_ptr<T>& internal, T* external) {
    if (canApplyPointer(internal.get(), external)) {
      if (*internal != *external) {
        internal.reset(external);
        return true;
      }
    }
    return false;
  }

  ::gos::pid::toolkit::ui::model::ptu::Status::Enum ptStatus_;

  /* Messages */
  QString lastMessage_;
  bool isLastMessageError_;

};

} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
