#include <QtQml/QtQml>

#include <gos/pid/ui/plugin.h>
#include <gos/pid/ui/floatvalidator.h>
#include <gos/pid/ui/items.h>

namespace gptu = ::gos::pid::toolkit::ui;

void PidToolkitPlugin::registerTypes(const char* uri) {
  qmlRegisterType<gptu::validator::Float>(
    uri, 1, 0, GOS_QML_VALIDATOR_NAME_FLOAT);
  qmlRegisterType<gptu::item::Connection>(
    uri, 1, 0, GOS_QML_ITEM_NAME_CONNECTION);
}