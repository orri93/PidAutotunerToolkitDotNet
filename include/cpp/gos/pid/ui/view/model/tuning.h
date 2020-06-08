#ifndef GOS_PID_TUNING_UI_VIEW_MODEL_TUNING_H_
#define GOS_PID_TUNING_UI_VIEW_MODEL_TUNING_H_

#include <QObject>
#include <QVariant>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/tuning/types.h>

#include <gos/pid/ui/configuration/tuning.h>

#include <gos/pid/ui/view/model/tuning.h>
#include <gos/pid/ui/view/model/modbus.h>
#include <gos/pid/ui/view/model/blackbox.h>
#include <gos/pid/ui/view/model/interface.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace view {
namespace model {

namespace tuning {
class Status : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
    Undefined,
    Idle,
    Starting,
    Tuning,
    Evaluating,
    Completed
  };
  enum StatusRoles {
    ValueRole = Qt::UserRole + 1,
    TextRole
  };
  Q_ENUM(Enum)
  Q_ENUM(StatusRoles)
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, StatusRoles> EnumerateModel;
  Status(QObject* parent = nullptr);
  Q_INVOKABLE int index(const Enum& state);
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

class Tuning :
  public ::gos::pid::toolkit::ui::model::Tuning,
  public virtual ::gos::pid::tuning::Nofity,
  public virtual ::gos::pid::toolkit::ui::view::model::Interface {
  Q_OBJECT

  /* Tuning status */
  /**
   * @brief Black Box tuning state of an enumerated type
  */
  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::tuning::Status::Enum status READ status NOTIFY statusChanged)
  Q_PROPERTY(bool isTuning READ isTuning)

  //Q_PROPERTY(::gos::pid::toolkit::ui::model::tuning::Method::Enum method READ method WRITE setMethod NOTIFY methodChanged)
  //Q_PROPERTY(QString lastMessage READ lastMessage NOTIFY lastMessageChanged)
  //Q_PROPERTY(bool isLastMessageError READ isLastMessageError)

  /* Controller settings items */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Force::Enum force READ force NOTIFY forceChanged)

  /* Controller tuning items */
  //Q_PROPERTY(double kp READ kp NOTIFY kpChanged)
  //Q_PROPERTY(double ki READ ki NOTIFY kiChanged)
  //Q_PROPERTY(double kd READ kd NOTIFY kdChanged)

  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::BlackBox* blackBox READ blackBox NOTIFY blackBoxChanged)

public:
  Tuning(
    ::gos::pid::toolkit::ui::configuration::Tuning& tuning,
    ::gos::pid::toolkit::ui::view::model::Modbus& modbus,
    ::gos::pid::toolkit::ui::model::Force& force,
    QObject* parent = nullptr);
  virtual ~Tuning();

  bool initialize();
  bool shutdown();
  ::gos::pid::toolkit::ui::model::types::result execute(
    ::gos::pid::arduino::modbus::types::registry::Input& input,
    const bool& issuccess);

  /* Apply View Model interface implementation */
  bool apply(::gos::pid::toolkit::ui::configuration::Interface& configuration);
  void notify();

  /* Tuning Notify interface */
  void notifyForce(const ::gos::pid::arduino::types::Unsigned& value);
  void notifyKp(const ::gos::pid::arduino::types::Real& kp);
  void notifyKi(const ::gos::pid::arduino::types::Real& ki);
  void notifyKd(const ::gos::pid::arduino::types::Real& kd);

  /* Tuning items */
  //const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method() const;

  /* Tuning status */
  const ::gos::pid::toolkit::ui::view::model::tuning::Status::Enum status() const;
  const bool isTuning() const;

  /* Controller tuning items */
  //const double& kp() const;
  //const double& ki() const;
  //const double& kd() const;

//const QString& lastMessage() const;
//const bool& isLastMessageError() const;

  /* Controller settings items */
  const ::gos::pid::toolkit::ui::model::Force::Enum& force() const;

  ::gos::pid::toolkit::ui::view::model::BlackBox* blackBox();

  ::gos::pid::toolkit::ui::view::model::BlackBox& getBlackBox();

signals:

  /* Tuning status */
  void statusChanged();

  //void methodChanged();
//void stateChanged();
//void lastMessageChanged();

  /* Controller settings items */
  void forceChanged();
  
  /* Controller tuning items */
  //void kpChanged();
  //void kiChanged();
  //void kdChanged();

  void blackBoxChanged();
  
public slots:
  void setMethod(const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method);

private slots:
  void onStateChanged();

private:

  /* Status items */
//void setStatus(const ::gos::pid::toolkit::ui::model::Status::Enum& status);
//void setLastMessage(const QString& message, const bool isLastMessageError = false);
//void setLastError(const QString& message);

  /* Controller settings items */
  void setForce(const ::gos::pid::toolkit::ui::model::Force::Enum& force);
  
  /* Controller tuning items */
  //void setKp(const double& value);
  //void setKi(const double& value);
  //void setKd(const double& value);

  bool handoverNotify();
  bool recoverNotify();

  ::gos::pid::toolkit::ui::configuration::Tuning& tuning_;
  ::gos::pid::toolkit::ui::view::model::Modbus& modbus_;
  ::gos::pid::toolkit::ui::model::Force& forceModel_;

  ::gos::pid::toolkit::ui::model::tuning::Method::Enum method_;

  /* Controller settings items */
  ::gos::pid::toolkit::ui::model::Force::Enum force_;

  /* Controller tuning items */
  //::gos::pid::toolkit::ui::model::Triplet triplet_;

  ::gos::pid::toolkit::ui::view::model::BlackBox blackBox_;

//QString lastMessage_;
//bool isLastMessageError_;

  /* Modbus items */

  /* Tuning items */
  int tuningRound_;
  bool isNotifyHandedOver_;
  ::gos::pid::toolkit::ui::types::Time tuningStart_;
  ::gos::pid::tuning::types::TuningState tuningState_;
  ::gos::pid::tuning::types::InitializedPointer tuningInitialized_;
  ::gos::pid::tuning::types::VariablesPointer tuningVariables_;
  ::gos::pid::tuning::types::EvaluationPointer tuningBestEvaluation_;
  ::gos::pid::tuning::black::box::VariablesPointer tuningBlackBoxVariables_;

};

} // namespace model
} // namespace view
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
