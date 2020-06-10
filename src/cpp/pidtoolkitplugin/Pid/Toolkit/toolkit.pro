TEMPLATE = lib
CONFIG += plugin
QT += qml
QT += quick

TARGET  = pidtoolkitplugin
#DESTDIR =  $$PWD

INCLUDEPATH += $$PWD/../../../../../include/cpp

SOURCES += plugin.cpp \
  pathvalidator.cpp

HEADERS += $$PWD/../../../../../include/cpp/gos/pid/ui/plugin/plugin.h \
  $$PWD/../../../../../include/cpp/gos/pid/ui/plugin/pathvalidator.h

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH = $$PWD/../../../../../out/install/x64-Release/bin/ui
#QML_IMPORT_PATH = $$PWD/../../../../../artifacts/RelWithDebInfo/bin/ui
#QML_IMPORT_PATH = $$PWD/../../../../../build/RelWithDebInfo/plugin
QML_IMPORT_PATH = $$PWD/../../../../../artifacts/RelWithDebInfo/plugin/empty

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH = $$PWD/../../../../../out/install/x64-Release/bin/ui
#QML_DESIGNER_IMPORT_PATH =
#QML_DESIGNER_IMPORT_PATH = $$PWD

RESOURCES += plugin.qrc

#DISTFILES += $$PWD/../../../../../pidtoolkit.root
#DISTFILES += $$PWD/../../plugin.root
