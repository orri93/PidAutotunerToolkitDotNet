#include <QDir>

#include <configuration.h>

/* Communication configuration */
//#define GROUP_COMMUNICATION "Communication"
//#define KEY_SERIAL_PORT "SerialPort"
//#define KEY_SERIAL_BAUD "SerialBaud"
//#define DEFAULT_SERIAL_PORT "COM1"
//#define DEFAULT_SERIAL_BAUD 9600

/* Modbus configuration */
//#define GROUP_MODBUS "Modbus"
//#define KEY_SLAVE_ID "SlaveId"
//#define DEFAULT_SLAVE_ID 1

/* Timers configuration */
//#define GROUP_TIMERS "Timers"
//#define KEY_INTERVAL "Interval"
//#define KEY_APPLY_TO_CONTROLLER "ApplyToController"
//#define DEFAULT_INTERVAL 250
//#define DEFAULT_APPLY_TO_CONTROLLER false

/* Tuning configuration */
#define GROUP_TUNING "Tuning"
#define KEY_TUNING_TEXT "Tuning"
#define DEFAULT_TUNING_TEXT TUNING_TEXT_OFF

/* UI configuration */
#define GROUP_UI "Ui"

namespace gp = ::gos::pid;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptum = ::gos::pid::toolkit::ui::model;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;
namespace gptutc = ::gos::pid::toolkit::ui::types::configuration;
namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Configuration::Configuration(const QString& filepath, QObject* parent) :
  gptum::Ptu(parent),
  filepath_(filepath){
  create();
}

Configuration::Configuration(QObject* parent) :
  gptum::Ptu(parent),
  filepath_(GOS_CONFIGURATION_FILE_PATH) {
  create();
}

Configuration::Configuration(const Configuration& configuration) :
  controller_(configuration.controller_),
  tuning_(configuration.tuning_),
  modbus_(configuration.modbus_),
  timer_(configuration.timer_),
  ui_(configuration.ui_) {
}

Configuration& Configuration::operator=(const Configuration& configuration) {
  return set(configuration);
}

Configuration& Configuration::set(const Configuration& configuration) {
  if (this != &configuration) {
    controller_ = configuration.controller_;
    tuning_ = configuration.tuning_;
    modbus_ = configuration.modbus_;
    timer_ = configuration.timer_;
    ui_ = configuration.ui_;
  }
  return *this;
}

QSettings* Configuration::initialize(const bool& watcher) {
  QSettings* result = nullptr;
  //QString filepath = QDir::cleanPath(path_ + QDir::separator() + filename_);
  settings_ = std::make_unique<QSettings>(filepath_, SettingsFormat);
  if (settings_) {
    gptum::Ptu::initializing();
    controller_.initialize();
    tuning_.initialize();
    modbus_.initialize();
    timer_.initialize();
    ui_.initialize();
    result = read();
    if (!QFile::exists(settings_->fileName())) {
      qInfo() << "Creating a default Configuration file at '"
        << settings_->fileName() << "'";
      result = write(true);
      if (result == nullptr) {
        qCritical() << "Failed to write default configuration file";
        return result;
      }
    }
    if(result != nullptr) {
      if (watcher) {
        watcher_ = std::make_unique<QFileSystemWatcher>(this);
        if (watcher_) {
          QObject::connect(
            watcher_.get(),
            &QFileSystemWatcher::fileChanged,
            this,
            &Configuration::onFileChanged);
          watcher_->addPath(settings_->fileName());
          qInfo() << "Watching Configuration from '"
            << settings_->fileName() << "'";
        } else {
          qCritical() << "Out of memory when trying to create a "
            "Qt File System Watcher";
          result = nullptr;
        }
      } else {
        qInfo() << "Reading Configuration from '"
          << settings_->fileName() << "'";
      }
    } else {
      qCritical() << "Failed to read configuration";
      result = nullptr;
    }
  } else {
    qCritical() << "Out of memory when trying to create a Qt Setting";
    result = nullptr;
  }
  idle();
  return result;
}

QSettings* Configuration::read(const bool& sync) {
  if (!settings_) {
    return nullptr;
  }
  if (sync) {
    settings_->sync();
  }

  QVariant value;

  /* Communication configuration */
  //settings_->beginGroup(GROUP_COMMUNICATION);
  //value = settings_->value(KEY_SERIAL_PORT, DEFAULT_SERIAL_PORT);
  //setSerialPort(value.toString());
  //value = settings_->value(KEY_SERIAL_BAUD, DEFAULT_SERIAL_BAUD);
  //setSerialBaud(value.toInt());
  //settings_->endGroup();

  /* Modbus configuration */
  //settings_->beginGroup(GROUP_MODBUS);
  //value = settings_->value(KEY_SLAVE_ID, DEFAULT_SLAVE_ID);
  //setSlaveId(value.toInt());
  //settings_->endGroup();

  /* Timers configuration */
  //settings_->beginGroup(GROUP_TIMERS);
  //value = settings_->value(KEY_INTERVAL, DEFAULT_INTERVAL);
  //setInterval(value.toInt());
  //value = settings_->value(KEY_APPLY_TO_CONTROLLER, DEFAULT_APPLY_TO_CONTROLLER);
  //setApplyIntervalToController(value.toBool());
  //settings_->endGroup();

  /* Tuning configuration */
  //settings_->beginGroup(GROUP_TUNING);
  //value = settings_->value(KEY_TUNING_TEXT, DEFAULT_TUNING_TEXT);
  //setTuningText(value.toString());
  //settings_->endGroup();

  modbus_.read(settings_.get());
  controller_.read(settings_.get());
  timer_.read(settings_.get());
  ui_.read(settings_.get());
  tuning_.read(settings_.get());

  return settings_.get();
}

QSettings* Configuration::write(const bool& sync) {
  if (startWriting() == nullptr) {
    return nullptr;
  }

  writeModbus();
  writeController();
  writeTimers();
  writeUi();
  writeTuning();

  return completeWriting(sync);
}

/* Modbus Communication configuration */
gptuc::Modbus* Configuration::modbus() { return &modbus_; }

/* Controller configuration */
gptuc::Controller* Configuration::controller() { return &controller_; }

/* Timers configuration */
gptuc::Timer* Configuration::timer() { return &timer_; }

/* Tuning configuration */
gptuc::Tuning* Configuration::tuning() { return &tuning_; }

/* Ui configuration */
gptuc::Ui* Configuration::ui() { return &ui_; }

/* Interface implementation */

/* Controller configuration */
gptuc::Controller& Configuration::getController() { return controller_; }
  
/* Modbus configuration */
gptuc::Modbus& Configuration::getModbus() { return modbus_; }

/* Tuning configuration */
gptuc::Timer& Configuration::getTimer() { return timer_; }

/* Tuning configuration */
gptuc::Tuning& Configuration::getTuning() { return tuning_; }

gptuc::Ui& Configuration::getUi() { return ui_; }

/* Writing */
QSettings* Configuration::startWriting() {
  if (settings_) {
    return settings_.get();
  } else {
    return nullptr;
  }
}
void Configuration::writeModbus() {
  modbus_.write(settings_.get());
}
void Configuration::writeController() {
  controller_.write(settings_.get());
}
void Configuration::writeTuning() {
  /* Tuning configuration */
  tuning_.write(settings_.get());
}
void Configuration::writeTimers() {
  /* Timers configuration */
  timer_.write(settings_.get());
}
void Configuration::writeUi() {
  ui_.write(settings_.get());
}
QSettings* Configuration::completeWriting(const bool& sync) {
  if (sync) {
    settings_->sync();
  }
  return settings_.get();
}

//bool Configuration::applyUiDialog(gptuc::Ui* ui) {
//  if (&ui_ != ui) {
//    if (::compare(ui_, *ui) != 0) {
//      ui_ = *ui;
//      writing();
//      write(true);
//      idle();
//      emit uiChanged();
//      return true;
//    }
//  }
//  return false;
//}

/* Modbus configuration */
//void Configuration::setSlaveId(const int& value) {
//  if (applySlaveId(value)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::slaveIdChanged, this);
//    qDebug() << "Setting slave id to " << value;
//    handle(changed);
//  }
//}

/* Communication configuration */
//void Configuration::setSerialPort(const QString& value) {
//  if (applySerialPort(value)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::serialPortChanged, this);
//    qDebug() << "Setting serial port to " << value;
//    handle(changed);
//  }
//}
//void Configuration::setSerialBaud(const int& value) {
//  if (applySerialBaud(value)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::serialBaudChanged, this);
//    qDebug() << "Setting serial baud to " << value;
//    handle(changed);
//  }
//}

/* Timers configuration */
//void Configuration::setInterval(const int& value) {
//  if (applyInterval(value)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::intervalChanged, this);
//    qDebug() << "Setting interval to " << value;
//    handle(changed, fWriteTimers_);
//  }
//}
//void Configuration::setApplyIntervalToController(const bool& value) {
//  if (applyApplyIntervalToController(value)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::applyIntervalToControllerChanged, this);
//    qDebug() << "Setting apply to controller to " << value;
//    handle(changed, fWriteTimers_);
//  }
//}

/* Tuning configuration */
//void Configuration::setTuning(const gp::tuning::types::TuningMode& value) {
//  if (applyTuning(value)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::tuningChanged, this);
//    qDebug() << "Setting tuning to " << tuningText(value);
//    handle(changed, fWriteTuning_);
//  }
//}
//void Configuration::setTuningText(const QString& value) {
//  setTuning(Items::tuningMode(value));
//}

/* Black Box configuration */
//void Configuration::setBlackBox(gptuc::BlackBox* blackBox) {
//  if (applyPointer(blackBox_, blackBox)) {
//    std::function<void()> changed =
//      std::bind(&Configuration::blackBoxChanged, this);
//    qDebug() << "Setting new Black Box Settings";
//    handle(changed, fWriteBlackBox_);
//  }
//}

void Configuration::onFileChanged(const QString& path) {
  switch (ptStatus_) {
  case gptum::ptu::Status::Enum::Idle:
    qDebug() << "Configuration file at '" << path
             << "' change and in 'read' mode";
    read(true);
    break;
  case gptum::ptu::Status::Enum::Writing:
    qDebug() << "Ignoring Configuration file at '" << path
             << "' change because in 'write' mode";
    qDebug() << "Configuration Setting mode back to 'normal'";
    idle();
    break;
  case gptum::ptu::Status::Enum::Initializing:
    qDebug() << "Ignoring Configuration file at '" << path
             << "' change because in 'initializing' mode";
    break;
  default:
    qWarning() << "Ignoring Configuration file at '" << path
               << "' change because in Unknown mode";
    break;
  }
}

void Configuration::create() {
  fWriteModbus_ = std::bind(&Configuration::writeModbus, this);
  fWriteController_ = std::bind(&Configuration::writeController, this);
  fWriteTuning_ = std::bind(&Configuration::writeTuning, this);
  fWriteTimers_ = std::bind(&Configuration::writeTimers, this);
  fWriteUi_ = std::bind(&Configuration::writeUi, this);
}

void Configuration::handle(std::function<void()>& changed) {
  switch (ptStatus_) {
  case gptum::ptu::Status::Enum::Idle:
    emit changed();
    break;
  case gptum::ptu::Status::Enum::Writing:
  case gptum::ptu::Status::Enum::Initializing:
  default:
    break;
  }
}

void Configuration::handle(
  std::function<void()>& changed,
  std::function<void()>& write) {
  switch (ptStatus_) {
  case gptum::ptu::Status::Enum::Idle:
    qDebug() << "Configuration handling mode 'normal'";
    emit changed();
    break;
  case gptum::ptu::Status::Enum::Writing:
    qDebug() << "Configuration handling mode 'write'";
    if (startWriting()) {
      write();
      completeWriting(true);
      qDebug() << "Configuration writing completed";
    }
    break;
  case gptum::ptu::Status::Enum::Initializing:
  default:
    break;
  }
}

void Configuration::handle(
  std::vector<std::function<void()>>& changed,
  std::function<void()>& write) {
  switch (ptStatus_) {
  case gptum::ptu::Status::Enum::Idle:
    qDebug() << "Configuration handling mode 'normal'";
    for (std::function<void()> f : changed) {
      emit f();
    }
    break;
  case gptum::ptu::Status::Enum::Writing:
    qDebug() << "Configuration handling mode 'write'";
    if (startWriting()) {
      write();
      completeWriting(true);
      qDebug() << "Configuration writing completed";
    }
    break;
  case gptum::ptu::Status::Enum::Initializing:
  default:
    break;
  }
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(const gptu::Configuration& lhs, const gptu::Configuration& rhs) {
  return compare(lhs, rhs) == 0;
}
bool operator!=(const gptu::Configuration& lhs, const gptu::Configuration& rhs) {
  return compare(lhs, rhs) != 0;
}

int compare(const gptu::Configuration& first, const gptu::Configuration& second) {
  return (
    /* Controller output items */
    compare(first.modbus_, second.modbus_) == 0 &&
    compare(first.controller_, second.controller_) == 0 &&
    compare(first.timer_, second.timer_) == 0 &&
    compare(first.tuning_, second.tuning_) == 0 &&
    compare(first.ui_, second.ui_) == 0) ? 0 : 1;
}
