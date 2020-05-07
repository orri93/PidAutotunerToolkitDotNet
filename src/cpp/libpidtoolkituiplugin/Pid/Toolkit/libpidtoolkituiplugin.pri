INCLUDEPATH += $$PWD/../../../../../include/cpp/

SOURCES     += $$PWD/floatvalidator.cpp \
               $$PWD/connection.cpp \
               $$PWD/plugin.cpp

HEADERS     += $$PWD/../../../../../include/cpp/gos/pid/ui/floatvalidator.h \
               $$PWD/../../../../../include/cpp/gos/pid/ui/connection.h \
               $$PWD/../../../../../include/cpp/gos/pid/ui/plugin.h

RESOURCES += \
  $$PWD/qml/pidtoolkitui.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

DISTFILES += \
  $$PWD/qmldir
