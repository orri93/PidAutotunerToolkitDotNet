#ifndef GOS_PID_TUNING_UI_VIEW_MODEL_BLACK_BOX_H_
#define GOS_PID_TUNING_UI_VIEW_MODEL_BLACK_BOX_H_

#include <QObject>
#include <QVariant>
#include <QtGlobal>
#include <QAbstractListModel>

#include <gos/pid/tuning/types.h>
#include <gos/pid/tuning/notify.h>

#include <gos/pid/ui/configuration/tuning.h>

#include <gos/pid/ui/view/model/modbus.h>

#include <gos/pid/ui/view/model/interface.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace view {
namespace model {

namespace black{
namespace box {
class State : public QAbstractListModel {
  Q_OBJECT
public:
  enum class Enum : quint8 {
  Undefined,
  Initialize,
  Reach,
  Over,
  Under,
  Balance,
  Cooldown,
//evaluation,
  Completed
  };
  enum StateRoles {
    ValueRole = Qt::UserRole + 1,
    TextRole
  };
  Q_ENUM(Enum)
  Q_ENUM(StateRoles)
  typedef ::gos::pid::toolkit::ui::model::Enumerate<
    Enum, StateRoles> EnumerateModel;
  State(QObject* parent = nullptr);
  Q_INVOKABLE int index(const Enum& state);
  Q_INVOKABLE Enum state(const int& index);
  int rowCount(const QModelIndex& parent = QModelIndex()) const;
  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  static EnumerateModel& enumerateModel();
protected:
  QHash<int, QByteArray> roleNames() const;
private:
  static EnumerateModel EnumerateModel_;
};
}
}

class BlackBox :
  public ::gos::pid::toolkit::ui::model::Ptu,
  public virtual ::gos::pid::toolkit::ui::view::model::Interface {
  Q_OBJECT

  /* BlackBox items */

  /**
   * @brief Black Box tuning state of an enumerated type
  */
  Q_PROPERTY(::gos::pid::toolkit::ui::view::model::black::box::State::Enum state READ state NOTIFY stateChanged)

  /* Controller settings items */

  /**
   * @brief Force the Arduino Controller to be in Idle, Manual or Automatic
  */
  Q_PROPERTY(::gos::pid::toolkit::ui::model::Force::Enum force READ force NOTIFY forceChanged)

  /* Controller tuning items */
  //Q_PROPERTY(double kp READ kp NOTIFY kpChanged)
  //Q_PROPERTY(double ki READ ki NOTIFY kiChanged)
  //Q_PROPERTY(double kd READ kd NOTIFY kdChanged)

public:  
  BlackBox(
    ::gos::pid::toolkit::ui::configuration::Tuning& tuning,
    ::gos::pid::toolkit::ui::view::model::Modbus& modbus,
    ::gos::pid::toolkit::ui::model::Force& force,
    QObject* parent = nullptr);

  bool initialize();
  bool shutdown();
  ::gos::pid::toolkit::ui::model::types::result execute(
    ::gos::pid::arduino::modbus::types::registry::Input& input,
    const bool& issuccess);

  /* Apply View Model interface implementation */
  bool apply(::gos::pid::toolkit::ui::configuration::Interface& configuration);
  void notify();

  /* BlackBox items */
  const ::gos::pid::toolkit::ui::view::model::black::box::State::Enum& state() const;

  /* Controller settings items */
  const ::gos::pid::toolkit::ui::model::Force::Enum& force() const;

  /* Controller tuning items */
  //const double& kp() const;
  //const double& ki() const;
  //const double& kd() const;



signals:
  //void methodChanged();
  void stateChanged();
  //void lastMessageChanged();

  /* Controller settings items */
  void forceChanged();
  
  /* Controller tuning items */
  //void kpChanged();
  //void kiChanged();
  //void kdChanged();

public slots:
  //void setMethod(const ::gos::pid::toolkit::ui::model::tuning::Method::Enum& method);

private:

  bool applyState(const ::gos::pid::toolkit::ui::view::model::black::box::State::Enum& state);

  void setState(const ::gos::pid::toolkit::ui::view::model::black::box::State::Enum& state);

  /* Status items */
  //void setLastMessage(const QString& message, const bool isLastMessageError = false);
  //void setLastError(const QString& message);

  /* Controller settings items */
  void setForce(const ::gos::pid::toolkit::ui::model::Force::Enum& force);
  
  /* Controller tuning items */
  //void setKp(const double& value);
  //void setKi(const double& value);
  //void setKd(const double& value);

  //bool handoverNotify();
  //bool recoverNotify();

  ::gos::pid::toolkit::ui::configuration::Tuning& tuning_;
  ::gos::pid::toolkit::ui::view::model::Modbus& modbus_;
  ::gos::pid::toolkit::ui::model::Force& forceModel_;

  ::gos::pid::toolkit::ui::view::model::black::box::State::Enum state_;

  /* Controller settings items */
  ::gos::pid::toolkit::ui::model::Force::Enum force_;

  /* Controller tuning items */
  //::gos::pid::toolkit::ui::model::Triplet triplet_;

  //QString lastMessage_;
  //bool isLastMessageError_;

  /* Modbus items */

  /* BlackBox items */
  int tuningRound_;
  //bool isNotifyHandedOver_;
  ::gos::pid::toolkit::ui::types::Time tuningStart_;
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
