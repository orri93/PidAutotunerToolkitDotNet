import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import Pid.Toolkit 1.0 as PidToolkit

ColumnLayout {
  id: pidRealTimePanel

  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true
  Layout.fillHeight: true

  property string titleText: qsTr("Real Time")
  
  property color dialogColor: "#404040"
  property color titleTextColor: "floralwhite"
  property color labelTextColor: "white"
  property color inputTextColor: "beige"
  property color informationTextColor: "burlywood"
  property color errorTextColor: "red"

  property int titleFontPointSize: 18
  property int labelFontPointSize:  8
  property int inputFontPointSize: 10
  property int informationFontPointSize: 10

  property real gridMargin: 5.0
  property real titleVerticalMargin: 10.0
  property real titleLeftMargin: 10.0
  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0
  property real informationTextLeftMargin: 5.0

  property bool isPanelCompleted: false

  property int nextMaximumTemperture: 0
  property int nextMaximumOutput: 0

  Text {
    text: titleText
    color: titleTextColor
    Layout.fillWidth: false
    Layout.leftMargin: titleLeftMargin
    Layout.topMargin: titleVerticalMargin
    Layout.bottomMargin: titleVerticalMargin
    Layout.alignment: Qt.AlignTop
    font.pointSize: titleFontPointSize
  }

  PidToolkit.ControllerOutput {
    id: controllerOutput
    Connections {
      target: orchestration
      onSetpointChanged: {
        controllerOutput.setSetpoint(orchestration.setpoint);
      }
      onTemperatureChanged: {
        if(pidRealTimePanel.visible) {
          controllerOutput.setTemperture(orchestration.temperature);
        }
      }
      onOutputChanged: {
        if(pidRealTimePanel.visible) {
          controllerOutput.setOutput(orchestration.output);
        }
      }
    }

  }
}