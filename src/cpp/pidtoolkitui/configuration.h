#ifndef GOS_PID_TUNING_UI_CONFIGURATION_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QFileSystemWatcher>
#include <QDebug>

#include <ui.h>
#include <blackbox.h>
#include <gos/pid/tuning/types.h>
#include <gos/pid/ui/types.h>

#include <items.h>

#define GOS_CONFIGURATION_FILE_PATH "configuration.ini"


#define GOS_QML_TYPE_CONFIGURATION_NAME "PidToolkitConfiguration"
#define GOS_QML_TYPE_CONFIGURATION_URI GOS_QML_TYPE_CONFIGURATION_NAME

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Configuration : public Items {
  Q_OBJECT

  /* Communication configuration */
  Q_PROPERTY(QString serialPort READ serialPort WRITE setSerialPort NOTIFY serialPortChanged)
  Q_PROPERTY(int serialBaud READ serialBaud WRITE setSerialBaud NOTIFY serialBaudChanged)
  
  /* Modbus configuration */
  Q_PROPERTY(int slaveId READ slaveId NOTIFY slaveIdChanged)

  /* Timers configuration */
  Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
  Q_PROPERTY(bool applyIntervalToController READ applyIntervalToController WRITE setApplyIntervalToController NOTIFY applyIntervalToControllerChanged)

  /* Tuning configuration */
  Q_PROPERTY(::gos::pid::tuning::types::TuningMode tuning READ tuning WRITE setTuning NOTIFY tuningChanged)
  Q_PROPERTY(QString tuningText READ tuningText WRITE setTuningText)

  /* Black Box configuration */
  //Q_PROPERTY(::gos::pid::toolkit::ui::configuration::BlackBox* blackBox READ blackBox WRITE setBlackBox NOTIFY blackBoxChanged)

  /* UI configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::Ui* ui READ ui NOTIFY uiChanged)

  /* Configuration mode */
  Q_PROPERTY(QString modeText READ modeText NOTIFY modeTextChanged)

  /* Chart*/
#ifdef GOS_NOT_YET_USED
    antialiasing
#endif

protected:
  const QSettings::Format SettingsFormat = QSettings::IniFormat;

public:
  explicit Configuration(const QString& filepath, QObject* parent = nullptr);
  explicit Configuration(QObject* parent = nullptr);

  virtual QSettings* initialize(const bool& watcher);

  virtual QSettings* read(const bool& sync = false);
  virtual QSettings* write(const bool& sync = false);

  /* Black Box configuration */
  ::gos::pid::toolkit::ui::configuration::BlackBox& blackBox();

  /* Ui configuration */
  ::gos::pid::toolkit::ui::configuration::Ui* ui();

  bool applyUiDialog(::gos::pid::toolkit::ui::configuration::Ui* ui);

signals:
  void modeTextChanged();
  /* Communication configuration */
  void serialPortChanged();
  void serialBaudChanged();
  /* Modbus configuration */
  void slaveIdChanged();
  /* Timers configuration */
  void intervalChanged();
  void applyIntervalToControllerChanged();

  /* Tuning configuration */
  void tuningChanged();

  /* Black Box configuration */
  void blackBoxChanged();

  /* UI configuration */
  void uiChanged();

public slots:
  /* Communication configuration */
  void setSerialPort(const QString& value);
  void setSerialBaud(const int& value);
  /* Timers configuration */
  void setInterval(const int& value);
  void setApplyIntervalToController(const bool& value);

  /* Tuning configuration */
  void setTuning(const ::gos::pid::tuning::types::TuningMode& value);
  void setTuningText(const QString& value);

private slots:
  void onFileChanged(const QString& path);

private:
  typedef std::unique_ptr<QSettings> SettingsPointer;
  typedef std::unique_ptr<QFileSystemWatcher> WatcherPointer;

  void create();

  void handle(std::function<void()>& changed);
  void handle(std::function<void()>& changed, std::function<void()>& write);
  void handle(
    std::vector<std::function<void()>>& changed,
    std::function<void()>& write);

  /* Writing */
  QSettings* startWriting();
  void writeTuning();
  void writeTimers();
  void writeBlackBox();
  void writeUi();
  virtual QSettings* completeWriting(const bool& sync = false);

  /* Modbus configuration */
  void setSlaveId(const int& value);

  /* Black box configuration */
  ::gos::pid::toolkit::ui::configuration::BlackBox blackBox_;
  /* Ui configuration */
  ::gos::pid::toolkit::ui::configuration::Ui ui_;


  /* Functions */
  std::function<void()> fWriteTuning_;
  std::function<void()> fWriteTimers_;
  std::function<void()> fWriteBlackBox_;

  /* Private */
  SettingsPointer settings_;
  WatcherPointer watcher_;

  QString filepath_;
};

} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
