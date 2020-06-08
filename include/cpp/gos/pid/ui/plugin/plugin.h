#ifndef GOS_PID_TUNING_UI_PLUGIN_H_
#define GOS_PID_TUNING_UI_PLUGIN_H_

#include <QtQml/QQmlExtensionPlugin>

class PidToolkitPlugin : public QQmlExtensionPlugin {
  Q_OBJECT
  //Q_PLUGIN_METADATA(IID "Pid.Toolkit/1.0")
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:

  //void initializeEngine(QQmlEngine* engine, const char* uri) override;

  /**
   * @brief registerTypes Overrided function that should register all
   * C++ classes exported by this plugin.
   * @param uri           Plugin uri.
   */
  void registerTypes(const char* uri) override;
};

#endif
