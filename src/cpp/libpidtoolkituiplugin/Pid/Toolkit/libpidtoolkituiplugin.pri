INCLUDEPATH += $$PWD/../../../../../include/cpp/

SOURCES     += $$PWD/floatvalidator.cpp \
               $$PWD/plugin.cpp

HEADERS     += $$PWD/../../../../../include/cpp/gos/pid/ui/floatvalidator.h \
               $$PWD/../../../../../include/cpp/gos/pid/ui/plugin.h

RESOURCES += \
  $$PWD/assets.qrc \
  $$PWD/model.qrc \
  $$PWD/component.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD

DISTFILES += \
  $$PWD/qmldir
