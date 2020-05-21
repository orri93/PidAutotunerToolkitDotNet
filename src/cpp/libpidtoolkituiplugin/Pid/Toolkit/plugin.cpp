#include <QtQml/QtQml>

#ifdef GOS_PID_TUNING_UI_PLUGIN_USE_ADVANCED_FILEDIALOG
#include <fileopendialog.h>
#include <filesavedialog.h>
#endif

#include <gos/pid/ui/plugin.h>
#include <gos/pid/ui/floatvalidator.h>
#include <gos/pid/ui/pathvalidator.h>

namespace gptu = ::gos::pid::toolkit::ui;

void PidToolkitPlugin::registerTypes(const char* uri) {
  qmlRegisterType<gptu::validator::Float>(
    uri, 1, 0, GOS_QML_VALIDATOR_NAME_FLOAT);
  qmlRegisterType<gptu::validator::Path>(
    uri, 1, 0, GOS_QML_VALIDATOR_NAME_PATH);
//qmlRegisterType<gptu::item::Connection>(
//  uri, 1, 0, GOS_QML_ITEM_NAME_CONNECTION);
}