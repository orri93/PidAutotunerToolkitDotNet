#ifndef GOS_PID_TUNING_UI_CONFIGURATION_H_
#define GOS_PID_TUNING_UI_CONFIGURATION_H_

#include <memory>
#include <vector>

#include <QObject>
#include <QSettings>
#include <QMetaType>
#include <QFileSystemWatcher>
#include <QDebug>

#include <gos/pid/tuning/types.h>
#include <gos/pid/ui/types.h>
#include <gos/pid/ui/model/ptu.h>

#include <gos/pid/ui/configuration/interface.h>
#include <gos/pid/ui/configuration/controller.h>
#include <gos/pid/ui/configuration/blackbox.h>
#include <gos/pid/ui/configuration/modbus.h>
#include <gos/pid/ui/configuration/tuning.h>
#include <gos/pid/ui/configuration/timer.h>
#include <gos/pid/ui/configuration/ui.h>

#define GOS_CONFIGURATION_FILE_PATH "configuration.ini"

#define GOS_QML_TYPE_CONFIGURATION_NAME "PidToolkitConfiguration"
#define GOS_QML_TYPE_CONFIGURATION_URI GOS_QML_TYPE_CONFIGURATION_NAME
namespace gos { namespace pid { namespace toolkit { namespace ui {
class Configuration; } } } }

bool operator==(
  const ::gos::pid::toolkit::ui::Configuration& lhs,
  const ::gos::pid::toolkit::ui::Configuration& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::Configuration& lhs,
  const ::gos::pid::toolkit::ui::Configuration& rhs);

int compare(
  const ::gos::pid::toolkit::ui::Configuration& first,
  const ::gos::pid::toolkit::ui::Configuration& second);

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {

class Configuration :
  public ::gos::pid::toolkit::ui::model::Ptu,
  public virtual ::gos::pid::toolkit::ui::configuration::Interface {
  Q_OBJECT

  /* Modbus Communication configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::Modbus* modbus READ modbus NOTIFY modbusChanged)

  /* Controller configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::Controller* controller READ controller NOTIFY controllerChanged)

  /* Timers configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::Timer* timer READ timer NOTIFY timerChanged)
  //Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
  //Q_PROPERTY(bool applyIntervalToController READ applyIntervalToController WRITE setApplyIntervalToController NOTIFY applyIntervalToControllerChanged)

  /* Tuning configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::Tuning* tuning READ tuning NOTIFY tuningChanged)
  //Q_PROPERTY(::gos::pid::tuning::types::TuningMode tuning READ tuning WRITE setTuning NOTIFY tuningChanged)
  //Q_PROPERTY(QString tuningText READ tuningText WRITE setTuningText)

  /* UI configuration */
  Q_PROPERTY(::gos::pid::toolkit::ui::configuration::Ui* ui READ ui NOTIFY uiChanged)

  /* Configuration mode */
  //Q_PROPERTY(QString modeText READ modeText NOTIFY modeTextChanged)

  /* Chart*/
#ifdef GOS_NOT_YET_USED
    antialiasing
#endif

  friend bool (::operator==) (const Configuration&, const Configuration&);
  friend bool (::operator!=) (const Configuration&, const Configuration&);
  friend int(::compare) (const Configuration&, const Configuration&);

protected:
  const QSettings::Format SettingsFormat = QSettings::IniFormat;

public:
  explicit Configuration(const QString& filepath, QObject* parent = nullptr);
  explicit Configuration(QObject* parent = nullptr);
  Configuration(const Configuration& configuration);

  Configuration& operator=(const Configuration& configuration);

  virtual Configuration& set(const Configuration& configuration);

  virtual QSettings* initialize(const bool& watcher);

  virtual QSettings* read(const bool& sync = false);
  virtual QSettings* write(const bool& sync = false);

  /* Modbus Communication configuration */
  ::gos::pid::toolkit::ui::configuration::Modbus* modbus();

  /* Controller configuration */
  ::gos::pid::toolkit::ui::configuration::Controller* controller();

  /* Timers configuration */
  ::gos::pid::toolkit::ui::configuration::Timer* timer();

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::configuration::Tuning* tuning();

  /* Black Box configuration */
  //::gos::pid::toolkit::ui::configuration::BlackBox& blackBox();

  /* Ui configuration */
  ::gos::pid::toolkit::ui::configuration::Ui* ui();

  /* Interface implementation */

  /* Controller configuration */
  ::gos::pid::toolkit::ui::configuration::Controller& getController();
  
  /* Modbus configuration */
  ::gos::pid::toolkit::ui::configuration::Modbus& getModbus();

  /* Timers configuration */
  ::gos::pid::toolkit::ui::configuration::Timer& getTimer();

  /* Tuning configuration */
  ::gos::pid::toolkit::ui::configuration::Tuning& getTuning();

    /* UI configuration */
  ::gos::pid::toolkit::ui::configuration::Ui& getUi();

signals:
  //void modeTextChanged();
  /* Modbus Communication configuration */
  void modbusChanged();
  /* Controller configuration */
  void controllerChanged();
  /* Timers configuration */
  void timerChanged();
  /* Tuning configuration */
  void tuningChanged();
  /* Communication configuration */
  //void serialPortChanged();
  //void serialBaudChanged();
  /* Modbus configuration */
  //void slaveIdChanged();
  /* Timers configuration */
  //void intervalChanged();
  //void applyIntervalToControllerChanged();

  /* Tuning configuration */
  //void tuningChanged();

  /* Black Box configuration */
  //void blackBoxChanged();

  /* UI configuration */
  void uiChanged();

public slots:
  /* Modbus Communication configuration */
  //void setModbus(
  //  const ::gos::pid::toolkit::ui::configuration::Modbus* modbus);
  /* Controller configuration */
  //void setController(
  //  const ::gos::pid::toolkit::ui::configuration::Controller* controller);
  /* Timers configuration */
  //void setTimer(
  //  const ::gos::pid::toolkit::ui::configuration::Timer* timer);
  /* Tuning configuration */
  //void setTuning(
  //  const ::gos::pid::toolkit::ui::configuration::Tuning* tuning);

  /* Communication configuration */
  //void setSerialPort(const QString& value);
  //void setSerialBaud(const int& value);
  /* Timers configuration */
  //void setInterval(const int& value);
  //void setApplyIntervalToController(const bool& value);

  /* Tuning configuration */
  //void setTuning(const ::gos::pid::tuning::types::TuningMode& value);
  //void setTuningText(const QString& value);

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
  void writeModbus();
  void writeController();
  void writeTuning();
  void writeTimers();
  //void writeBlackBox();
  void writeUi();
  virtual QSettings* completeWriting(const bool& sync = false);

  /* Modbus configuration */
  //void setSlaveId(const int& value);


  /* Modbus Communication configuration */
  ::gos::pid::toolkit::ui::configuration::Modbus modbus_;
  /* Controller configuration */
  ::gos::pid::toolkit::ui::configuration::Controller controller_;
  /* Timers configuration */
  ::gos::pid::toolkit::ui::configuration::Timer timer_;
  /* Tuning configuration */
  ::gos::pid::toolkit::ui::configuration::Tuning tuning_;

  /* Black box configuration */
  //::gos::pid::toolkit::ui::configuration::BlackBox blackBox_;
  /* Ui configuration */
  ::gos::pid::toolkit::ui::configuration::Ui ui_;


  /* Functions */
  std::function<void()> fWriteModbus_;
  std::function<void()> fWriteController_;
  std::function<void()> fWriteTuning_;
  std::function<void()> fWriteTimers_;
  //std::function<void()> fWriteBlackBox_;
  std::function<void()> fWriteUi_;

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
