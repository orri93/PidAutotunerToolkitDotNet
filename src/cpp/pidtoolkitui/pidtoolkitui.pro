QT += charts qml quick


VERSION = 1.0.0
QMAKE_TARGET_COMPANY = Geirmundur Orri Sigurdsson
QMAKE_TARGET_PRODUCT = PID Toolkit
QMAKE_TARGET_DESCRIPTION = PID Toolkit User Interface
QMAKE_TARGET_COPYRIGHT = Copyright (C) Geirmundur Orri Sigurdsson 2019 - 2020
QMAKE_CXXFLAGS += /FS

TARGET       = PidToolkitUi

#INCLUDEPATH += "$$(BOOST_32B_PATH)"
INCLUDEPATH += $$PWD

HEADERS += \
    configuration.h \
    orchestration.h

SOURCES += \
    pidtoolkitui.cpp \
    configuration.cpp \
    orchestration.cpp

RESOURCES += \
    resources.qrc

include("$$PWD/../libpidtoolkitui/libpidtoolkitui.pri")

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

win32 {
LIBS += -lws2_32
} else {
}


LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libmodbus.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidarduinomodbusmaster.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtuningblackbox.lib"
LIBS            += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkitcpp.lib"

PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libmodbus.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidarduinomodbusmaster.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtuningblackbox.lib"
PRE_TARGETDEPS  += "$${PID_TOOLKIT_API_PATH}/lib/libpidtoolkitcpp.lib"

INCLUDEPATH +="$${PID_TOOLKIT_API_PATH}/include/modbus"
INCLUDEPATH +="$${PID_TOOLKIT_API_PATH}/include/cpp"

DISTFILES += \
    qml/pid/main.qml \
    qml/pid/PidChart.qml \
    qml/pid/PidPanel.qml \
    qml/pid/RealSpinBox.qml \
    qml/pid/*
