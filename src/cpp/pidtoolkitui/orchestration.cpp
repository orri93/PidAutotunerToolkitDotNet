#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include <QDebug>

#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>

#include <gos/pid/toolkit/exception.h>
#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/arduino/modbus/retry.h>

#include <gos/pid/ui/plugin.h>
#include <gos/pid/ui/model/status.h>
#include <gos/pid/ui/model/interval.h>
#include <gos/pid/ui/model/tuning.h>
#include <gos/pid/ui/model/mode.h>
#include <gos/pid/ui/formatting.h>

#include <gos/pid/tuning/setting.h>

#include <gos/pid/ui/view/model/interface.h>

#include <orchestration.h>

#include <models.h>

#define GOS_QML_ORCHESTRATION "ptOrchestration"

namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;

namespace gptt = ::gos::pid::tuning::types;

namespace gpa = ::gos::pid::arduino;
namespace gpam = ::gos::pid::arduino::modbus;
namespace gpat = ::gos::pid::arduino::types;

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptut = ::gos::pid::toolkit::ui::types;
namespace gptuvm = ::gos::pid::toolkit::ui::view::model;
namespace gptutc = ::gos::pid::toolkit::ui::types::configuration;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

namespace orchestration {
typedef std::unique_ptr<Orchestration> OrchestrationPointer;
static OrchestrationPointer _orchestration;
//static PidToolkitPlugin _plugin;
bool create(QQmlContext& context) {

  qRegisterMetaType<::gos::pid::toolkit::ui::model::Range*>(
    "::gos::pid::toolkit::ui::model::Range*");
  qRegisterMetaType<::gos::pid::toolkit::ui::model::Factor*>(
    "::gos::pid::toolkit::ui::model::Factor*");
  qRegisterMetaType< ::gos::pid::toolkit::ui::model::Accuracy*>(
    "::gos::pid::toolkit::ui::model::Accuracy*");
  qRegisterMetaType<::gos::pid::toolkit::ui::configuration::BlackBox*>(
    "::gos::pid::toolkit::ui::configuration::BlackBox*");
  qRegisterMetaType<::gos::pid::toolkit::ui::configuration::Ui*>(
    "::gos::pid::toolkit::ui::configuration::Ui*");
  qRegisterMetaType<::gos::pid::toolkit::ui::Configuration*>(
    "::gos::pid::toolkit::ui::Configuration*");
  qRegisterMetaType<::gos::pid::toolkit::ui::model::Modbus*>(
    "::gos::pid::toolkit::ui::model::Modbus*");

  if (gptu::models::create(context)) {
    _orchestration = std::make_unique<Orchestration>(context);
    if (_orchestration) {
      context.setContextProperty(GOS_QML_ORCHESTRATION, _orchestration.get());
      if (_orchestration->initialize(false)) {
        return true;
      } else {
        qCritical() << "Failed to initialize the Orchestration";
      }
    } else {
      qCritical() << "Out of memory when creating the Orchestration";
    }
  }
  return false;
}
namespace handle {
template<typename T> void general(
  Configuration& configuration,
  std::function<void(const T&)>& setter,
  const bool& watcher,
  const T& value) {
  qDebug() << "Setting configuration to 'write' mode";
  if (watcher) {
    configuration.setMode(gptutc::mode::write);
    setter(value);
  } else {
    configuration.setMode(gptutc::mode::write);
    setter(value);
    configuration.setMode(gptutc::mode::normal);
  }
}
}
}

Orchestration::Orchestration(QQmlContext& context, QObject* parent) :
  gptum::Ptu(parent),
  context_(context),
  count_(0),
  watcher_(false),
  isLastMessageError_(false)
  //tuningRound_(0),
  //isNotifyHandedOver_(false),
  //tuningState_(gp::tuning::types::TuningState::undefined),
  /* Status items */
  //status_(gptum::Status::Enum::Undefined),
  //isInitialize_(false)
  /* Controller input items */
  /* Controller settings items */
  /* Controller tuning items */
  /* Controller output items */ {
  qRegisterMetaType<QAbstractSeries*>();
  qRegisterMetaType<QAbstractAxis*>();
}

Orchestration::~Orchestration() {
  //if (isNotifyHandedOver_) {
  //  recoverNotify();
  //}
  //switch (status_) {
  //case gptum::Status::Enum::Connected:
  //  gpam::master::disconnect();
  //  status_ = gptum::Status::Enum::Disconnected;
  //  break;
  //}
  if (logfile_) {
    logfile_->flush();
    logfile_->close();
  }
  gpam::master::shutdown();
}

bool Orchestration::initialize(const bool& watcher) {
  Models& models = gptu::models::instance();
  watcher_ = watcher;
  configuration_ = std::make_unique<Configuration>();
  if (configuration_) {
    QSettings* settings = configuration_->initialize(watcher);
    if (settings != nullptr) {
      gptum::Force& force = models.getForce();
      modbus_ = std::make_unique<gptuvm::Modbus>(force);
      if (modbus_) {
        settings_ = std::make_unique<gptu::Configuration>(*configuration_);
        if (settings_) {
          tuning_ = std::make_unique<gptuvm::Tuning>(
            configuration_->getTuning(),
            *modbus_,
            force);
          if (tuning_) {
            if (applyConfiguration()) {
              if (modbus_->initialize()) {
                if (tuning_->initialize()) {
                  idle();
                  qInfo() << "Initialize completed";
                  return true;
                } else {
                  qCritical() << "Failed to Initialize Tuning";
                }
              } else {
                qCritical() << "Failed to Initialize Modbus";
              }
            } else {
              qCritical() << "Failed to apply the configuration";
            }
          } else {
            qCritical() << "Out of memory for Tuning";
          }
        } else {
          qCritical() << "Out of memory for Settings";
        }
      } else {
        qCritical() << "Out of memory for Modbus";
      }
    } else {
      qCritical() << "Out of memory for Configuration";
    }
  } else {
    qCritical() << "Failed to create configuration";
  }
  return false;
}

int Orchestration::update(
  QAbstractSeries* output,
  QAbstractSeries* temperature,
  QAbstractSeries* setpoints) {
  if (modbus_) {
    gpam::types::registry::Input input;
    if (modbus_->update(input)) {
      logging(input);
      if (tuning_->isTuning()) {
        tuning_->execute(input, true);
      }
      float x = static_cast<float>(count_);
      outputsList_.append(QPointF(x, static_cast<double>(input.Output)));
      temperatureList_.append(QPointF(x, static_cast<double>(
        input.Temperature)));
      setpointsList_.append(QPointF(x, modbus_->setpoint()));
      count_++;
    } else {
      if (tuning_->isTuning()) {
        tuning_->execute(input, false);
      }
    }
  }
  if (count_ > 2) {
    if (output) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(output);
      xySeries->replace(outputsList_);
    }
    if (temperature) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(temperature);
      xySeries->replace(temperatureList_);
    }
    if (setpoints) {
      QXYSeries* xySeries = static_cast<QXYSeries*>(setpoints);
      xySeries->replace(setpointsList_);
    }
  }
  return count_;
}

bool Orchestration::connectDisconnect() {
  bool result = modbus_->connectDisconnect();
  if (result) {
    if (modbus_->isConnected()) {
      gptuc::Timer& timer = configuration_->getTimer();
      if (timer.applyIntervalToController()) {
        if (!modbus_->writeInterval(timer.interval())) {
          //setLastMessage(modbus_->lastMessage());
        }
      }
    }
  } else {
    //setLastError(modbus_->lastMessage());
  }
  return result;
}

bool Orchestration::startStopLogging() {
  if (logfile_) {
    if (logfile_->is_open()) {
      std::cout << "Closing the logging file" << std::endl;
      logfile_->flush();
      logfile_->close();
    }
    logfile_.reset(nullptr);
    emit isLoggingChanged();
    return true;
  } else {
    logfile_ = std::make_unique<std::ofstream>("pid.csv", std::ios::out);
    if (logfile_->is_open()) {
      start_ = gptu::types::Clock::now();
      std::cout << "Logging file opened successful" << std::endl;
      emit isLoggingChanged();
      return true;
    } else {
      std::cerr << "Failed to open a logging file" << std::endl;
      logfile_.reset(nullptr);
      return false;
    }
  }
}

void Orchestration::panelCompleted() {
  qDebug() << "Panel Completed";
  notify();
//  iscompleted_ = true;
//  emit uiChanged();
//  emit blackBoxChanged();
//  emit isCompletedChanged();
  emit configurationChanged();
  emit completed();
}

//void Orchestration::applyBlackBoxDialog() {
//  if (blackBoxForDialog_ && configuration_) {
//    gptuc::BlackBox& ref = configuration_->blackBox();
//    if (&ref != blackBoxForDialog_.get()) {
//      if (::compare(ref, *blackBoxForDialog_) != 0) {
//        ref = *blackBoxForDialog_;
//        configuration_->setMode(gptutc::mode::write);
//        configuration_->write(true);
//        configuration_->setMode(gptutc::mode::normal);
//      }
//    }
//  }
//}

//void Orchestration::rejectBlackBoxDialog() {
//  if (blackBoxForDialog_ && configuration_) {
//    gptuc::BlackBox& ref = configuration_->blackBox();
//    if (::compare(ref, *blackBoxForDialog_) != 0) {
//      *blackBoxForDialog_ = ref;
//      emit blackBoxChanged();
//    }
//  }
//}

//void Orchestration::applyUiDialog() {
//  if (uiForDialog_ && configuration_) {
//    if (configuration_->applyUiDialog(uiForDialog_.get())) {
//      emit configurationChanged();
//    }
//  }
//}
//
//void Orchestration::rejectUiDialog() {
//  if (uiForDialog_ && configuration_) {
//    gptuc::Ui* uip = configuration_->ui();
//    if (::compare(*uip, *uiForDialog_) != 0) {
//      *uiForDialog_ = *uip;
//      emit uiChanged();
//    }
//  }
//}

void Orchestration::applySettings() {
  if (settings_ && configuration_) {
    if (compare(*settings_, *configuration_) == 0) {
      qWarning() << "Applying settings with no changes";
    } else {
      qInfo() << "Applying updated settings to the configuration";
      configuration_->set(*settings_);
    }
  }
}
void Orchestration::rejecSettings() {
  if (settings_ && configuration_) {
    if (compare(*settings_, *configuration_) == 0) {
      qWarning() << "Rejecting settings with no changes";
    } else {
      qInfo() << "Applying rejecting updated settings by "
        "reading from the configuration again";
      settings_->set(*configuration_);
    }
  }
}



//const QString Orchestration::configurationModeText() const {
//  return configuration_->modeText();
//}

/* Configuration Access */
Configuration* Orchestration::configuration() {
  if (configuration_) {
    return configuration_.get();
  }
  return nullptr;
}

Configuration* Orchestration::settings() {
  if (settings_) {
    return settings_.get();
  } else {
    return nullptr;
  }
}

//gptu::configuration::BlackBox* Orchestration::blackBox() {
//  if (blackBoxForDialog_) {
//    return blackBoxForDialog_.get();
//  } else {
//    qWarning() << "Undefined Black Box from Orchestration";
//    return nullptr;
//  }
//}

//gptu::configuration::Ui* Orchestration::ui() {
//  if (uiForDialog_) {
//    return uiForDialog_.get();
//  } else {
//    qWarning() << "Undefined Black Box from Orchestration";
//    return nullptr;
//  }
//}


  /* View Models */
gptuvm::Modbus* Orchestration::modbus() {
  if (modbus_) {
    return modbus_.get();
  } else {
    return nullptr;
  }
}
gptuvm::Tuning* Orchestration::tuning() {
  if (tuning_) {
    return tuning_.get();
  } else {
    return nullptr;
  }
}

/* Tuning items */
//const gp::tuning::types::TuningState& Orchestration::tuningState() const {
//  return tuningState_;
//}
//const QString Orchestration::tuningStateText() const {
//  switch (tuningState_) {
//  case gp::tuning::types::TuningState::undefined:
//    return "Undefined";
//  case gp::tuning::types::TuningState::initialize:
//    return "Initialize";
//  case gp::tuning::types::TuningState::reach:
//    return "Reaching";
//  case gp::tuning::types::TuningState::over:
//    return "Over";
//  case gp::tuning::types::TuningState::under:
//    return "Under";
//  case gp::tuning::types::TuningState::balance:
//    return "Stable";
//  case gp::tuning::types::TuningState::cooldown:
//    return "Cool down";
//  case gp::tuning::types::TuningState::completed:
//    return "Completed";
//  default:
//    return "Unknown";
//  }
//}

/* Status items */
//const gptum::Status::Enum Orchestration::status() const {
//  return status_;
//}
//const bool& Orchestration::isInitialize() const {
//  return isInitialize_;
//}
//const bool& Orchestration::isCompleted() const {
//  return iscompleted_;
//}
//const bool Orchestration::isConnected() const {
//  return status_ == gptum::Status::Enum::Connected;
//}
//const QString& Orchestration::lastMessage() const {
//  return lastMessage_;
//}
//const bool& Orchestration::isLastMessageError() const {
//  return isLastMessageError_;
//}

/* Logging items */
const bool Orchestration::isLogging() const {
  if (logfile_) {
    return logfile_->is_open();
  } else {
    return false;
  }
}

/* Controller input items */

/* Controller settings items */


/* Controller tuning items */

/* Controller output items */

/* Other items */

/* Timers items */

/* Tuning items */
/*
void Orchestration::setTuning(const gptt::TuningMode& value) {
  gptt::TuningMode saved = tuning_;
  if (applyTuning(value)) {
    std::function<void(const gptt::TuningMode&)> setter = std::bind(
      &Configuration::setTuning, configuration_.get(), std::placeholders::_1);
    orchestration::handle::general(*configuration_, setter, watcher_, value);
    if (isTuning()) {
      if (handoverNotify()) {
        setLastMessage("Notify Handed Over");
        setTuningState(gp::tuning::types::TuningState::initialize);
        emit tuningChanged();
      } else {
        setLastError("Failed to hand over notify");
        setTuningState(gp::tuning::types::TuningState::undefined);
        tuning_ = saved;
      }
    } else {
      if (recoverNotify()) {
        setTuningState(gp::tuning::types::TuningState::undefined);
      } else {
        throw std::runtime_error("Failed to recover tuning notifier");
      }
      emit tuningChanged();
    }
  }
}
*/
/*
void Orchestration::setTuningIndex(const int& value) {
  setTuning(gptum::tuning::value(value));
}
*/

/* Tuning items */
/*
void Orchestration::setTuningState(const gp::tuning::types::TuningState& state) {
  if (tuningState_ != state) {
    tuningState_ = state;
    emit tuningStateChanged();
  }
}
*/

/* Controller input items */

/* Controller settings items */

/* Controller tuning items */



/* Controller output items */

/* Other items */

/*
void Orchestration::onConfigurationModeTextChanged() {
  qDebug() << " Configuration Mode Text Changed";
  emit configurationModeTextChanged();
}
*/

/*
void Orchestration::onCommunicationConfigurationChanged() {
  qDebug() << " Communication Configuration Changed";
}
*/

/*
void Orchestration::onModbusConfigurationChanged() {
  qDebug() << " Modbus Configuration Changed";
}
*/

/*
void Orchestration::onTimersConfigurationChanged() {
  qDebug() << " Timers Configuration Changed";
  setInterval(configuration_->interval());
  setApplyIntervalToController(configuration_->applyIntervalToController());
}
*/

/*
void Orchestration::onTuningConfigurationChanged() {
  qDebug() << " Tuning Configuration Changed";
  setTuning(configuration_->tuning());
}
*/

bool Orchestration::applyConfiguration() {
  bool result = true;
  gptuc::Interface& configinterface =
    dynamic_cast<gptuc::Interface&>(*configuration_);
  if (modbus_) {
    gptuvm::Interface& vm = dynamic_cast<gptuvm::Interface&>(*modbus_);
    if (vm.apply(configinterface)) {
      qInfo() << "Applying configuration to Modbus";
    } else {
      qWarning() << "Failed to apply configuration to Modbus";
      result = false;
    }
  } else {
    qWarning() << "Failed to apply configuration to undefined Modbus";
    result = false;
  }
  if (tuning_) {
    gptuvm::Interface& vm = dynamic_cast<gptuvm::Interface&>(*tuning_);
    if (vm.apply(configinterface)) {
      qInfo() << "Applying configuration to Tuning";
    } else {
      qWarning() << "Failed to apply configuration to Tuning";
      result = false;
    }
  } else {
    qWarning() << "Failed to apply configuration to undefined Tuning";
    result = false;
  }
  //serialPort_ = configuration_->serialPort();
  //serialBaud_ = configuration_->serialBaud();
  //slaveId_= configuration_->slaveId();
  //interval_ = configuration_->interval();
  //applyIntervalToController_ = configuration_->applyIntervalToController();
  //tuning_ = configuration_->tuning();
  return result;
}

/*
void Orchestration::connectConfiguration() {
  QObject::connect(
    configuration_.get(),
    &Configuration::modeTextChanged,
    this,
    &Orchestration::onConfigurationModeTextChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::serialPortChanged,
    this,
    &Orchestration::onCommunicationConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::serialBaudChanged,
    this,
    &Orchestration::onCommunicationConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::slaveIdChanged,
    this,
    &Orchestration::onModbusConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::intervalChanged,
    this,
    &Orchestration::onTimersConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::applyIntervalToControllerChanged,
    this,
    &Orchestration::onTimersConfigurationChanged);
  QObject::connect(
    configuration_.get(),
    &Configuration::tuningChanged,
    this,
    &Orchestration::onTuningConfigurationChanged);
}
*/

/* Communication items */

/* Status items */
/*
void Orchestration::setStatus(const gptum::Status::Enum& status) {
  if (status_ != status) {
    status_ = status;
    emit statusChanged();
  }
}
void Orchestration::setLastMessage(const QString& message, const bool isLastMessageError) {
  isLastMessageError_ = isLastMessageError;
  if (lastMessage_ != message) {
    lastMessage_ = message;
    emit lastMessageChanged();
  }
}
void Orchestration::setLastError(const QString& message) {
  setLastMessage(message, true);
}
*/

/* Controller input items */

/* Controller settings items */

/* Controller tuning items */

/* Controller output items */


/* Other items */

void Orchestration::notify() {
    bool result = true;
  if (modbus_) {
    gptuvm::Interface& vm = dynamic_cast<gptuvm::Interface&>(*modbus_);
    vm.notify();
  } else {
    qWarning() << "Failed to notify to undefined Modbus";
    result = false;
  }
  if (tuning_) {
    gptuvm::Interface& vm = dynamic_cast<gptuvm::Interface&>(*tuning_);
    vm.notify();
  } else {
    qWarning() << "Failed to notify configuration to undefined Tuning";
    result = false;
  }

  //emit statusChanged();
  //emit lastMessageChanged();
  //emit serialPortChanged();
  //emit serialBaudChanged();
  //emit slaveIdChanged();
  //emit configurationModeTextChanged();
  //emit intervalChanged();
  //emit applyIntervalToControllerChanged();
  //emit forceChanged();
  //emit tuningChanged();
  //emit setpointChanged();
}

/*
bool Orchestration::initializemodbus() {
  gpam::types::result result;
  std::string serialport = serialPort_.toStdString();
  result = gpam::master::initialize(
    serialport.c_str(),
    serialBaud_,
    slaveId_);
  if (result == gpam::types::result::success) {
    applyConfiguration();
    connectConfiguration();
    return true;
  } else {
    qWarning() << "Failed to initialize Modbus Master";
  }
  return false;
}
*/

void Orchestration::logging(const gpam::types::registry::Input& input) {
  double setpoint = 0.0;
  if (modbus_) {
    setpoint = modbus_->setpoint();
  }
  if (logfile_) {
    if (logfile_->is_open()) {
      gptu::types::Duration duration = gptu::types::Clock::now() - start_;
      gptu::types::Duration seconds =
        std::chrono::duration_cast<std::chrono::seconds>(duration);
      (*logfile_)
        << seconds.count() << ","
        << input.Output << ","
        << input.Temperature << ","
        << setpoint << std::endl;
      logfile_->flush();
    }
  }
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

