import QtQuick 2.14
import QtCharts 2.3

ChartView {
  id: pidChart

  animationOptions: ChartView.NoAnimation
  theme: ChartView.ChartThemeDark

  property bool openGl: true
  property bool openGlSupported: true

  ValueAxis {
    id: axisY
    min: 0
    max: ptOrchestration.configuration.ui.chart.maximum;
  }

  ValueAxis {
    id: axisX
    min: 0
    max: 1024
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
    target: ptOrchestration
    onIntervalChanged: {
      refreshTimer.interval = ptOrchestration.interval;
    }
  }

  Connections {
    target: ptOrchestration
    onStatusChanged: {
      refreshTimer.running = ptOrchestration.isConnected;
    }
  }

  Timer {
    id: refreshTimer
    interval: ptOrchestration.interval
    running: false
    repeat: true
    onTriggered: {
      axisX.max = ptOrchestration.update(
        pidChart.series("output"),
        pidChart.series("temperature"),
        pidChart.series("setpoint"));
    }
  }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

