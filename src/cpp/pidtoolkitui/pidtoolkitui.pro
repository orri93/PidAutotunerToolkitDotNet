QT += serialport charts quick core qml

CONFIG += c++11

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = Geirmundur Orri Sigurdsson
QMAKE_TARGET_PRODUCT = PID Toolkit
QMAKE_TARGET_DESCRIPTION = PID Toolkit User Interface
QMAKE_TARGET_COPYRIGHT = Copyright (C) Geirmundur Orri Sigurdsson 2019 - 2020
QMAKE_CXXFLAGS += /FS

TARGET       = PidToolkitUi

INCLUDEPATH += "$$(BOOST)"
INCLUDEPATH += $$PWD

HEADERS += \
    orchestration.h \
    configuration.h \
    models.h

SOURCES += \
    orchestration.cpp \
    configuration.cpp \
    pidtoolkitui.cpp \
    models.cpp

RESOURCES += \
    qml/pidtoolkit.qrc

include("$$PWD/../libpidtoolkituiplugin/Pid/Toolkit/libpidtoolkituiplugin.pri")

#DEFINES += _USE_MATH_DEFINES

# Debugging files for Release builds
# https://stackoverflow.com/questions/9234337/qt-no-map-pdb-files-generated-for-windows-release-builds
QMAKE_LFLAGS_RELEASE +=/MAP
QMAKE_CFLAGS_RELEASE += /Zi
QMAKE_LFLAGS_RELEASE +=/debug /opt:ref

CONFIG(release, debug|release) {
    # Release build
    DEFINES += QT_NO_DEBUG_OUTPUT
    PID_TOOLKIT_API_PATH = $$PWD/../../../out/install/x64-Release
} else {
    # Debug build
#   DEFINES += GOS_DEBUG
    PID_TOOLKIT_API_PATH = $$PWD/../../../out/install/x64-Debug
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/../libpidtoolkituiplugin/Pid/Toolkit

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = $$PWD/../libpidtoolkituiplugin/Pid/Toolkit

win32 {
LIBS += -lws2_32 -L"$$(BOOST)\lib64-msvc-14.2"
} else {
}

LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libmodbus.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidarduinomodbusmaster.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtuningblackbox.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkitcpp.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/pidtoolkitplugin.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkituimodel.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkituiviewmodel.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkituiconfiguration.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkitui.lib"

PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libmodbus.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidarduinomodbusmaster.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtuningblackbox.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkitcpp.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/pidtoolkitplugin.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkituimodel.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkituiviewmodel.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkituiconfiguration.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkitui.lib"

INCLUDEPATH +="$${PID_TOOLKIT_API_PATH}/include/modbus"
INCLUDEPATH +="$${PID_TOOLKIT_API_PATH}/include/cpp"

DISTFILES += \
    configuration.ini
