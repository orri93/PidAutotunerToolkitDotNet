import QtQuick 2.14
import QtCharts 2.3

PidChartPanelForm {

  property bool openGl: true
  property bool openGlSupported: true

  property var orchestration: ptOrchestration
  property var configuration: ptOrchestration.configuration
  property var timer: ptOrchestration.configuration.timer
  property var modbus: ptOrchestration.modbus
  property var ui: ptOrchestration.configuration.ui

  ValueAxis {
    id: axisY
    min: 0
    max: 255
  }

  ValueAxis {
    id: axisX
    min: 0
    max: 320.0
  }

  LineSeries {
      id: lineSeriesOutput
      name: "output"
      axisX: axisX
      axisY: axisY
      useOpenGL: pidChart.openGl
  }
  LineSeries {
      id: lineSeriesTemperature
      name: "temperature"
      axisX: axisX
      axisY: axisY
      useOpenGL: pidChart.openGl
  }
  LineSeries {
      id: lineSeriesSetpoint
      name: "setpoint"
      axisX: axisX
      axisY: axisY
      useOpenGL: pidChart.openGl
  }

  Timer {
    id: refreshTimer
    interval: timer.interval
    running: false
    repeat: true
    onTriggered: {
      axisX.max = orchestration.update(
        pidChart.series("output"),
        pidChart.series("temperature"),
        pidChart.series("setpoint"));
    }
  }

  Component.onCompleted: {
    if (!series("output").useOpenGL) {
      openGlSupported = false
      openGl = false
    }
  }

  onOpenGlChanged: {
    if (openGlSupported) {
      series("output").useOpenGL = openGl
      series("temperature").useOpenGL = openGl;
      series("setpoint").useOpenGL = openGl;
    }
  }

  Connections {
    target: timer
    onIntervalChanged: {
      refreshTimer.interval = timer.interval;
    }
  }

  Connections {
    target: modbus
    onStatusChanged: {
      refreshTimer.running = modbus.isConnected;
    }
  }
}
