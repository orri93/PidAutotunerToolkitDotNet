#include <QStringList>

#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/ui/view/model/blackbox.h>
#include <gos/pid/tuning/setting.h>

namespace gp = ::gos::pid;

namespace gpa = ::gos::pid::arduino;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuvm = ::gos::pid::toolkit::ui::view::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;
namespace gptumt = ::gos::pid::toolkit::ui::model::tuning;
namespace gptumty = ::gos::pid::toolkit::ui::model::types;
namespace gpamtr = ::gos::pid::arduino::modbus::types::registry;
namespace gptt = ::gos::pid::tuning::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace view {
namespace model {

namespace black{
namespace box {
static const QString StateTextArray[] = {
  "Initialize",
  "Reach",
  "Over",
  "Under",
  "Balance",
  "Cooldown",
  //"evaluation",
  "Completed",
  "" };
static const State::Enum StateArray[] = {
  State::Enum::Initialize,
  State::Enum::Reach,
  State::Enum::Over,
  State::Enum::Under,
  State::Enum::Balance,
  State::Enum::Cooldown,
  //evaluation,
  State::Enum::Completed,
  State::Enum::Undefined
};
State::EnumerateModel State::EnumerateModel_(
  StateArray,
  StateTextArray,
  State::Enum::Undefined,
  State::StateRoles::ValueRole,
  State::StateRoles::TextRole);
State::State(QObject* parent) :
  QAbstractListModel(parent) {
}
int State::index(const State::Enum& state) {
  return EnumerateModel_.index(state);
}
State::Enum State::state(const int& index) {
  return EnumerateModel_.enumerate(index);
}
int State::rowCount(const QModelIndex& parent) const {
  Q_UNUSED(parent);
  return EnumerateModel_.count();
}
QVariant State::data(const QModelIndex& index, int role) const {
  return EnumerateModel_.data(index, role);
}
QHash<int, QByteArray> State::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[TextRole] = "text";
  roles[ValueRole] = "value";
  return roles;
}
State::EnumerateModel& State::enumerateModel() { return EnumerateModel_; }
} // namespace box
} // namespace black

BlackBox::BlackBox(
  gptuc::Tuning& tuning,
  gptuvm::Modbus& modbus,
  gptum::Force& forcemodel,
  QObject* parent) :
  gptum::Ptu(parent),
  tuning_(tuning),
  modbus_(modbus),
  forceModel_(forcemodel),
  state_(gptuvm::black::box::State::Enum::Undefined),
  force_(gptum::Force::Enum::Undefined),
  //isLastMessageError_(false),
  tuningRound_(0)
  /* isNotifyHandedOver_(false) */ {
}

bool BlackBox::initialize() {
//  return handoverNotify();
  return true;
}

bool BlackBox::shutdown() {
//  return recoverNotify();
  return true;
}

/* Apply View Model interface implementation */
bool BlackBox::apply(gptuc::Interface& configuration) {
  return true;
}
void BlackBox::notify() {
}

gptumty::result BlackBox::execute(gpamtr::Input& input, const bool& issuccess) {
  gptuc::BlackBox& blackBox = tuning_.getBlackBox();
  gptumty::result result = gptumty::result::success;
  QString separator = blackBox.separator();
  QString outputfile = blackBox.file();
  std::string stdseparator = separator.toStdString();
  std::string stdoutputfile = outputfile.toStdString();
  bool isinternal = blackBox.internalVariables();
  gpa::types::Real lkp = static_cast<gpa::types::Real>(blackBox.kp());
  gpa::types::Real lki = static_cast<gpa::types::Real>(blackBox.ki());
  gpa::types::Real lkd = static_cast<gpa::types::Real>(blackBox.kd());
  gp::tuning::setting::window::size = blackBox.windowSize();
  gp::tuning::setting::stable::duration::minutes = 
    blackBox.stableDuration();
  gp::tuning::setting::output::file::path = stdoutputfile;
  switch (state_) {
  case gptuvm::black::box::State::Enum::Undefined:
    setLastError("Undefined tuning state");
    result = gptumty::result::error;
    return result;
    break;
  case gptuvm::black::box::State::Enum::Initialize:
    tuningInitialized_ = std::make_unique<gp::tuning::types::Initialized>();
    if (tuningInitialized_) {
      tuningInitialized_->Setpoint = 
        static_cast<gpa::types::Real>(blackBox.setpoint());
      tuningInitialized_->Manual =
        static_cast<gpa::types::Unsigned>(blackBox.manual());
      tuningInitialized_->Kp = lkp;
      tuningInitialized_->Ki = lki;
      tuningInitialized_->Kd = lkd;
      tuningVariables_ = std::make_unique<gp::tuning::types::Variables>();
      tuningBlackBoxVariables_ =
        std::make_unique<gp::tuning::black::box::Variables>();
      if (tuningVariables_ && tuningBlackBoxVariables_) {
        gp::tuning::setting::parameters.Sd = blackBox.sd();
        gptum::Range* kprp = blackBox.kpRange();
        if (kprp != nullptr) {
          gp::tuning::setting::parameters.Kp.lowest =
            static_cast<gpa::types::Real>(kprp->from());
          gp::tuning::setting::parameters.Kp.highest = 
            static_cast<gpa::types::Real>(kprp->to());
        }
        gptum::Range* kirp = blackBox.kiRange();
        if (kirp != nullptr) {
          gp::tuning::setting::parameters.Ki.lowest =
            static_cast<gpa::types::Real>(kirp->from());
          gp::tuning::setting::parameters.Ki.highest =
            static_cast<gpa::types::Real>(kirp->to());
        }
        if (blackBox.isBase()) {
          gp::tuning::setting::parameters.BaseLine =
            static_cast<gpa::types::Real>(blackBox.base());
        } else {
          gp::tuning::setting::parameters.BaseLine = ::boost::none;
        }
        if (modbus_.haveLastHolding()) {
          gpamtr::Holding& holding = modbus_.lastHolding();
          gp::tuning::black::box::load(
            *tuningBlackBoxVariables_,
            *tuningInitialized_,
            holding,
            stdseparator,
            isinternal);
          gp::tuning::black::box::initialize(
            *tuningVariables_,
            *tuningBlackBoxVariables_,
            gp::tuning::setting::parameters,
            tuningInitialized_->Kp.get(),
            tuningInitialized_->Ki.get());
            if (modbus_.writeForce(gptum::Force::Enum::Auto)) {
              force_ = gptum::Force::Enum::Auto;
              emit forceChanged();
              tuningRound_ = 0;
              tuningStart_ = gptu::types::Clock::now();
              setState(gptuvm::black::box::State::Enum::Reach);
            } else {
              result = gptumty::result::warning;
              setLastError("Failed to force for tuning");
            }
          }
        } else {
          setLastError("Last holding is undefined");
          result = gptumty::result::error;
          return result ;
        }
      } else {
        setLastError("Out of memory for tuning");
        result = gptumty::result::error;
        return result ;
      }
    break;
  case gptuvm::black::box::State::Enum::Reach:
  case gptuvm::black::box::State::Enum::Over:
  case gptuvm::black::box::State::Enum::Under:
  case gptuvm::black::box::State::Enum::Balance:
  case gptuvm::black::box::State::Enum::Cooldown:
    break;
  default:
    setLastError("Unknown tuning state");
    break;
  }
  gptu::types::Time time = gptu::types::Clock::now();
  gptu::types::Duration duration = time - tuningStart_;
  std::chrono::milliseconds dms =
    std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  double elapsed = static_cast<double>(dms.count()) / 1000.0;
  if (tuningVariables_ && tuningBlackBoxVariables_) {
    switch (state_) {
    case gptuvm::black::box::State::Enum::Undefined:
      setLastError("Undefined tuning state again");
      break;
    case gptuvm::black::box::State::Enum::Initialize:
      setLastError("Initialize state repeated");
      break;
    case gptuvm::black::box::State::Enum::Reach:
    case gptuvm::black::box::State::Enum::Over:
    case gptuvm::black::box::State::Enum::Under:
    case gptuvm::black::box::State::Enum::Balance:
    case gptuvm::black::box::State::Enum::Cooldown:
      gp::tuning::black::box::cycle(
        tuningRound_,
        *tuningVariables_,
        *tuningBlackBoxVariables_,
        tuningBestEvaluation_,
        gp::tuning::setting::parameters,
        input,
        elapsed,
        time,
        stdseparator,
        issuccess,
        isinternal);
      break;
    default:
      setLastError("Unknown tuning state again");
      break;
    }
    switch (state_) {
    case gptuvm::black::box::State::Enum::Undefined:
      setLastError("Undefined tuning state the third time");
      break;
    case gptuvm::black::box::State::Enum::Initialize:
      setLastError("Initialize state repeated again");
      break;
    case gptuvm::black::box::State::Enum::Reach:
      if (tuningBlackBoxVariables_->IsOver) {
        setLastMessage("BlackBox Setpoint Reached");
        setState(gptuvm::black::box::State::Enum::Over);
      }
    case gptuvm::black::box::State::Enum::Over:
      if (tuningBlackBoxVariables_->IsUnder) {
        setLastMessage("BlackBox Under");
        setState(gptuvm::black::box::State::Enum::Under);
      }
    case gptuvm::black::box::State::Enum::Under:
      if (tuningBlackBoxVariables_->IsStable) {
        setLastMessage("BlackBox Stable");
        setState(gptuvm::black::box::State::Enum::Balance);
      }
    case gptuvm::black::box::State::Enum::Balance:
      if (tuningBlackBoxVariables_->IsCooling) {
        setLastMessage("BlackBox Cooling Down");
        setState(gptuvm::black::box::State::Enum::Cooldown);
      }
    case gptuvm::black::box::State::Enum::Cooldown:
      if (tuningBlackBoxVariables_->IsRoundStarting) {
        setState(gptuvm::black::box::State::Enum::Reach);
      }
      break;
    default:
      setLastError("Unknown tuning state the third time");
      break;
    }
  }
  return result;
}

/* BlackBox Notify interface */
//void BlackBox::notifyForce(const gpa::types::Unsigned& value) {
//  int forcenumber = static_cast<int>(value);
//  gptum::Force::Enum notifyforce = forceModel_.fromNumber(forcenumber);
//  if (force_ != notifyforce) {
//    force_ = notifyforce;
//    emit forceChanged();
//  }
//}
//void BlackBox::notifyKp(const gpa::types::Real& kp) {
//  setKp(static_cast<double>(kp));
//}
//void BlackBox::notifyKi(const gpa::types::Real& ki) {
//  setKi(static_cast<double>(ki));
//}
//void BlackBox::notifyKd(const gpa::types::Real& kd) {
//  setKd(static_cast<double>(kd));
//}

/* BlackBox items */
//const gptum::tuning::Method::Enum& BlackBox::method() const { return method_; }
const gptuvm::black::box::State::Enum& BlackBox::state() const { return state_; }
//const bool BlackBox::isBlackBox() const {
//  switch (state_) {
//  case gptuvm::black::box::State::Enum::Undefined:
//  case gptuvm::black::box::State::Enum::Initialize:
//    return false;
//  case gptuvm::black::box::State::Enum::Reach:
//  case gptuvm::black::box::State::Enum::Over:
//  case gptuvm::black::box::State::Enum::Under:
//  case gptuvm::black::box::State::Enum::Balance:
//  case gptuvm::black::box::State::Enum::Cooldown:
//    return true;
//  case gptuvm::black::box::State::Enum::Completed:
//    return false;
//  default:
//    return false;
//  }
//}

/* Controller settings items */
const gptum::Force::Enum& BlackBox::force() const { return force_; }

/* Controller tuning items */
//const double& BlackBox::kp() const { return triplet_.kp(); }
//const double& BlackBox::ki() const { return triplet_.ki(); }
//const double& BlackBox::kd() const { return triplet_.kd(); }

//void BlackBox::setMethod(const gptum::tuning::Method::Enum& method) {
//  if (method_ != method) {
//    method_ = method;
//    emit methodChanged();
//  }
//}
bool BlackBox::applyState(const gptuvm::black::box::State::Enum& state) {
  if (state_ != state) {
    state_ = state;
    return true;
  } else {
    return false;
  }
}

void BlackBox::setState(const gptuvm::black::box::State::Enum& state) {
  if (applyState(state)) {
    emit stateChanged();
  }
}

/* Controller settings items */
void BlackBox::setForce(const gptum::Force::Enum& force) {
  if (force_ != force) {
    force_ = force;
    emit forceChanged();
  }
}
//
//void BlackBox::setKp(const double& value) {
//  if (triplet_.kp() != value) {
//    triplet_.setKp(value);
//    emit kpChanged();
//  }
//}
//void BlackBox::setKi(const double& value) {
//  if (triplet_.ki() != value) {
//    triplet_.setKi(value);
//    emit kiChanged();
//  }
//}
//void BlackBox::setKd(const double& value) {
//  if (triplet_.kd() != value) {
//    triplet_.setKd(value);
//    emit kdChanged();
//  }
//}


//bool BlackBox::handoverNotify() {
//  if (!isNotifyHandedOver_) {
//    gp::tuning::NotifyPointer notify(this);
//    if (notify) {
//      isNotifyHandedOver_ = gp::tuning::black::box::notify::handover(notify);
//      if (isNotifyHandedOver_) {
//        return true;
//      } else {
//        setLastError("Failed to hand over notify");
//      }
//    } else {
//      setLastError("Failed to create notify for hand over");
//    }
//  } else {
//    setLastError("Notify has already been handed over");
//  }
//  return false;
//}
//
//bool BlackBox::recoverNotify() {
//  if (isNotifyHandedOver_) {
//    gp::tuning::NotifyPointer notify;
//    isNotifyHandedOver_ = !(gp::tuning::black::box::notify::recover(notify));
//    if (!isNotifyHandedOver_) {
//      gp::tuning::Nofity* pointer = notify.release();
//      return true;
//    } else {
//      setLastError("Failed to recover notify");
//    }
//  } else {
//    setLastError("Notify has not yet been handed over");
//  }
//  return false;
//}


} // namespace model
} // namespace view
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

