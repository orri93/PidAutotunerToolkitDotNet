#include <QtQml/QtQml>

#include <gos/pid/ui/plugin/plugin.h>
#include <gos/pid/ui/plugin/pathvalidator.h>

namespace gptu = ::gos::pid::toolkit::ui;

//void PidToolkitPlugin::initializeEngine(QQmlEngine* engine, const char* uri) {}

void PidToolkitPlugin::registerTypes(const char* uri) {

  qmlRegisterType<gptu::validator::Path>(
    uri, 1, 0, GOS_QML_VALIDATOR_NAME_PATH);
//qmlRegisterType<gptu::item::Connection>(
//  uri, 1, 0, GOS_QML_ITEM_NAME_CONNECTION);
}
