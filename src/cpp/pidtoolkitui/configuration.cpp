#include <QDir>

#include <configuration.h>

/* Communication configuration */
#define GROUP_COMMUNICATION "Communication"
#define KEY_SERIAL_PORT "SerialPort"
#define KEY_SERIAL_BAUD "SerialBaud"
#define DEFAULT_SERIAL_PORT "COM1"
#define DEFAULT_SERIAL_BAUD 9600

/* Modbus configuration */
#define GROUP_MODBUS "Modbus"
#define KEY_SLAVE_ID "SlaveId"
#define DEFAULT_SLAVE_ID 1

/* Timers configuration */
#define GROUP_TIMERS "Timers"
#define KEY_INTERVAL "Interval"
#define KEY_APPLY_TO_CONTROLLER "ApplyToController"
#define DEFAULT_INTERVAL 250
#define DEFAULT_APPLY_TO_CONTROLLER false

/* Tuning configuration */
#define GROUP_TUNING "Tuning"
#define KEY_TUNING_TEXT "Tuning"
#define DEFAULT_TUNING_TEXT TUNING_TEXT_OFF

/* UI configuration */
#define GROUP_UI "Ui"

namespace gp = ::gos::pid;
namespace gptu = ::gos::pid::toolkit::ui;
namespace gptuc = ::gos::pid::toolkit::ui::configuration;
namespace gptutc = ::gos::pid::toolkit::ui::types::configuration;
namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

Configuration::Configuration(const QString& filepath, QObject* parent) :
  Items(parent),
  filepath_(filepath){
  create();
}

Configuration::Configuration(QObject* parent) :
  Items(parent),
  filepath_(GOS_CONFIGURATION_FILE_PATH) {
  create();
}

QSettings* Configuration::initialize(const bool& watcher) {
  QSettings* result = nullptr;
  //QString filepath = QDir::cleanPath(path_ + QDir::separator() + filename_);
  settings_ = std::make_unique<QSettings>(filepath_, SettingsFormat);
  if (settings_) {
    gptuc::Base::initialize();
    blackBox_.initialize();
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
  setNormal();
  blackBox_.setNormal();
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
  settings_->beginGroup(GROUP_COMMUNICATION);
  value = settings_->value(KEY_SERIAL_PORT, DEFAULT_SERIAL_PORT);
  setSerialPort(value.toString());
  value = settings_->value(KEY_SERIAL_BAUD, DEFAULT_SERIAL_BAUD);
  setSerialBaud(value.toInt());
  settings_->endGroup();

  /* Modbus configuration */
  settings_->beginGroup(GROUP_MODBUS);
  value = settings_->value(KEY_SLAVE_ID, DEFAULT_SLAVE_ID);
  setSlaveId(value.toInt());
  settings_->endGroup();

  /* Timers configuration */
  settings_->beginGroup(GROUP_TIMERS);
  value = settings_->value(KEY_INTERVAL, DEFAULT_INTERVAL);
  setInterval(value.toInt());
  value = settings_->value(KEY_APPLY_TO_CONTROLLER, DEFAULT_APPLY_TO_CONTROLLER);
  setApplyIntervalToController(value.toBool());
  settings_->endGroup();

  /* Tuning configuration */
  settings_->beginGroup(GROUP_TUNING);
  value = settings_->value(KEY_TUNING_TEXT, DEFAULT_TUNING_TEXT);
  setTuningText(value.toString());
  settings_->endGroup();

  blackBox_.read(settings_.get());

  return settings_.get();
}

QSettings* Configuration::write(const bool& sync) {
  if (startWriting() == nullptr) {
    return nullptr;
  }

  /* Communication configuration */
  settings_->beginGroup(GROUP_COMMUNICATION);
  settings_->setValue(KEY_SERIAL_PORT, serialPort_);
  settings_->setValue(KEY_SERIAL_BAUD, serialBaud_);
  settings_->endGroup();

  /* Modbus configuration */
  settings_->beginGroup(GROUP_MODBUS);
  settings_->setValue(KEY_SLAVE_ID, slaveId_);
  settings_->endGroup();

  writeTuning();
  writeTimers();
  writeBlackBox();

  return completeWriting(sync);
}

/* Writing */
QSettings* Configuration::startWriting() {
  if (settings_) {
    return settings_.get();
  } else {
    return nullptr;
  }
}
void Configuration::writeTuning() {
  /* Tuning configuration */
  settings_->beginGroup(GROUP_TUNING);
  settings_->setValue(KEY_TUNING_TEXT, tuningText());
  settings_->endGroup();
}
void Configuration::writeTimers() {
  /* Timers configuration */
  settings_->beginGroup(GROUP_TIMERS);
  settings_->setValue(KEY_INTERVAL, interval_);
  settings_->setValue(KEY_APPLY_TO_CONTROLLER, applyIntervalToController_);
  settings_->endGroup();
}
void Configuration::writeBlackBox() {
  blackBox_.write(settings_.get());
}
QSettings* Configuration::completeWriting(const bool& sync) {
  if (sync) {
    settings_->sync();
  }
  return settings_.get();
}

/* Black Box configuration */
gptuc::BlackBox& Configuration::blackBox() {
  return blackBox_;
}

/* Modbus configuration */
void Configuration::setSlaveId(const int& value) {
  if (applySlaveId(value)) {
    std::function<void()> changed =
      std::bind(&Configuration::slaveIdChanged, this);
    qDebug() << "Setting slave id to " << value;
    handle(changed);
  }
}

/* Communication configuration */
void Configuration::setSerialPort(const QString& value) {
  if (applySerialPort(value)) {
    std::function<void()> changed =
      std::bind(&Configuration::serialPortChanged, this);
    qDebug() << "Setting serial port to " << value;
    handle(changed);
  }
}
void Configuration::setSerialBaud(const int& value) {
  if (applySerialBaud(value)) {
    std::function<void()> changed =
      std::bind(&Configuration::serialBaudChanged, this);
    qDebug() << "Setting serial baud to " << value;
    handle(changed);
  }
}

/* Timers configuration */
void Configuration::setInterval(const int& value) {
  if (applyInterval(value)) {
    std::function<void()> changed =
      std::bind(&Configuration::intervalChanged, this);
    qDebug() << "Setting interval to " << value;
    handle(changed, fWriteTimers_);
  }
}
void Configuration::setApplyIntervalToController(const bool& value) {
  if (applyApplyIntervalToController(value)) {
    std::function<void()> changed =
      std::bind(&Configuration::applyIntervalToControllerChanged, this);
    qDebug() << "Setting apply to controller to " << value;
    handle(changed, fWriteTimers_);
  }
}

/* Tuning configuration */
void Configuration::setTuning(const gp::tuning::types::TuningMode& value) {
  if (applyTuning(value)) {
    std::function<void()> changed =
      std::bind(&Configuration::tuningChanged, this);
    qDebug() << "Setting tuning to " << tuningText(value);
    handle(changed, fWriteTuning_);
  }
}
void Configuration::setTuningText(const QString& value) {
  setTuning(Items::tuningMode(value));
}

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
  switch (mode_) {
  case gptutc::mode::normal:
    qDebug() << "Configuration file at '" << path
             << "' change and in 'read' mode";
    read(true);
    break;
  case gptutc::mode::write:
    qDebug() << "Ignoring Configuration file at '" << path
             << "' change because in 'write' mode";
    qDebug() << "Configuration Setting mode back to 'normal'";
    setMode(gptutc::mode::normal);
    break;
  case gptutc::mode::initializing:
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
  fWriteTuning_ = std::bind(&Configuration::writeTuning, this);
  fWriteTimers_ = std::bind(&Configuration::writeTimers, this);
  fWriteBlackBox_ = std::bind(&Configuration::writeBlackBox, this);
}

void Configuration::handle(std::function<void()>& changed) {
  switch (mode_) {
  case gptutc::mode::normal:
    emit changed();
    break;
  case gptutc::mode::write:
  case gptutc::mode::initializing:
  default:
    break;
  }
}

void Configuration::handle(
  std::function<void()>& changed,
  std::function<void()>& write) {
  switch (mode_) {
  case gptutc::mode::normal:
    qDebug() << "Configuration handling mode 'normal'";
    emit changed();
    break;
  case gptutc::mode::write:
    qDebug() << "Configuration handling mode 'write'";
    if (startWriting()) {
      write();
      completeWriting(true);
      qDebug() << "Configuration writing completed";
    }
    break;
  case gptutc::mode::initializing:
  default:
    break;
  }
}

void Configuration::handle(
  std::vector<std::function<void()>>& changed,
  std::function<void()>& write) {
  switch (mode_) {
  case gptutc::mode::normal:
    qDebug() << "Configuration handling mode 'normal'";
    for (std::function<void()> f : changed) {
      emit f();
    }
    break;
  case gptutc::mode::write:
    qDebug() << "Configuration handling mode 'write'";
    if (startWriting()) {
      write();
      completeWriting(true);
      qDebug() << "Configuration writing completed";
    }
    break;
  case gptutc::mode::initializing:
  default:
    break;
  }
}

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
