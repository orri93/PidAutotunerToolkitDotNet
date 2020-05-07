import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

ColumnLayout {
  id: pidParameterPanel

  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true
  Layout.fillHeight: true

  property string titleText: qsTr("PID Toolkit")

  property string realPlaceholderText: qsTr("0.0")

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

  Component.onCompleted: {
    enableInput(false);
    orchestration.panelCompleted();
    pidParameterPanel.isPanelCompleted = true;
  }

  PidToolkit.FloatValidator {
    id: floatValidator
  }

  GridLayout {
    Layout.alignment: Qt.AlignTop
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.margins: gridMargin

    columns: 2
    rows: 10

    ColumnLayout {
      id: titleColumn
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 0

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
    }

    ColumnLayout {
      id: controllerColumn
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 1
      PidToolkit.ControllerSettings {
        id: controllerSettings
        modeBoxModel: modeModel
        onModeIndexChanged: {
          orchestration.forceIndex = value;
        }
        onSetpointChanged: {
          orchestration.setpoint = value;
        }
        onManualChanged: {
          orchestration.manual = value;
        }
        Connections {
          target: orchestration
          onForceChanged: {
            controllerSettings.modeBoxIndex = orchestration.forceIndex;
          }
        }
        Connections {
          target: orchestration
          onManualChanged: {
            controllerSettings.setManual(orchestration.manual);
          }
        }
        Connections {
          target: orchestration
          onSetpointChanged: {
            controllerSettings.setSetpoint(orchestration.setpoint);
          }
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 2
      PidToolkit.ConnectionSettings {
        id: connectionGroup
        serialPortModel: portModel
        serialBaudModel: baudModel
        onSerialPortIndexChanged: {
          orchestration.serialPortIndex = connectionGroup.serialPortBoxIndex;
          //console.log("Serial Port group Changed: " + connectionGroup.serialPortBoxIndex.toString());
        }
        onSerialBaudIndexChanged: {
          orchestration.serialBaudIndex = connectionGroup.serialBaudBoxIndex;
          //console.log("Serial Baud group Changed: " + connectionGroup.serialBaudBoxIndex.toString());
        }
        onConnectButtonPressed: {
          orchestration.connectDisconnect();
        }
        Connections {
          target: orchestration
          onSerialPortChanged: {
            //console.log("Serial Port Changed: " + orchestration.serialPort);
            //console.log("Serial Port Index Changed: " + orchestration.serialPortIndex.toString());
            connectionGroup.serialPortBoxIndex = orchestration.serialPortIndex;
          }
        }
        Connections {
          target: orchestration
          onSerialBaudChanged: {
            connectionGroup.serialBaudBoxIndex = orchestration.serialBaudIndex;
            //console.log("Serial Baud Index Changed: " + orchestration.serialBaudIndex.toString());
          }
        }
        Connections {
          target: orchestration
          onStatusChanged: {
            connectionGroup.statusText = orchestration.statusText;
            connectionGroup.setConnectionState(orchestration.isConnected);
            if(orchestration.isTuning) { console.log("Tuning"); } else { console.log("Not Tuning"); }
            resolveEnable();
          }
        }
      }
    }

    ColumnLayout {
      id: timingColumn
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 3
      PidToolkit.TimingSettings {
        id: timingSettings
        intervalBoxModel: intervalModel
        onIntervalIndexChanged: {
          orchestration.intervalIndex = value;
        }
        onApplyToControllerChanged: {
          orchestration.applyIntervalToController = value;
        }
        Connections {
          target: orchestration
          onIntervalChanged: {
            timingSettings.intervalBoxIndex = orchestration.intervalIndex;
          }
        }
        Connections {
          target: orchestration
          onApplyIntervalToControllerChanged: {
            timingSettings.setApplyToController(orchestration.applyIntervalToController);
          }
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 4

      PidToolkit.TuningSettings {
        id: tuningSettings
        tuningBoxModel: tuningModel
        onTuningIndexChanged: {
          console.log("Tuning index changed to " + value.toString()); 
          orchestration.tuningIndex = value;
          resolveEnable();
          if(orchestration.isTuning) { console.log("Tuning"); } else { console.log("Not Tuning"); }
        }
        Connections {
          target: orchestration
          onTuningChanged: {
            tuningSettings.tuningBoxIndex = orchestration.tuningIndex;
            resolveEnable();
          }
        }
        Connections {
          target: orchestration
          onTuningStateChanged: {
            tuningSettings.tuningStatus = orchestration.tuningStateText;
          }
        }
      }
    }

    ColumnLayout {
      id: pidColumn
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 5
      PidToolkit.PidSettings {
        id: pidSettings
        onKpTextChanged: {
          orchestration.kpText = text;
        }
        onKiTextChanged: {
          orchestration.kiText = text;
        }
        onKdTextChanged: {
          orchestration.kdText = text;
        }
        Connections {
          target: orchestration
          onKpChanged: {
            pidSettings.kp.text = orchestration.kpText
          }
        }
        Connections {
          target: orchestration
          onKiChanged: {
            pidSettings.ki.text = orchestration.kiText
          }
        }
        Connections {
          target: orchestration
          onKdChanged: {
            pidSettings.kd.text = orchestration.kdText
          }
        }
        Connections {
          target: orchestration
          onIntegralTextChanged: {
            pidSettings.integral.text = orchestration.integralText;
          }
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 6

      PidToolkit.LoggingSettings {
        id: loggingSettings
        onLoggingButtonPressed: {
          orchestration.startStopLogging();
        }
        Connections {
          target: orchestration
          onIsLoggingChanged: {
            loggingSettings.setLoggingState(orchestration.isLogging);
          }
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 7
      Label {
        text: qsTr("Message")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: messageText
        text: qsTr("")
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.fillWidth: true
      }
      Connections {
        target: orchestration
        onLastMessageChanged: {
          messageText.text = orchestration.lastMessage;
          if(orchestration.isLastMessageError) {
            messageText.color = errorTextColor;
          } else {
            messageText.color = informationTextColor;
          }
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 8
      Label {
        id: debugLabel
        text: qsTr("Debug")
        visible: false
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: debugText
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.fillWidth: true
      }
    }

    ColumnLayout {
      visible: false
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 9
      Label {
        id: configurationModeLabel
        text: qsTr("Configuration Mode")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: configurationModeText
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.fillWidth: true
      }
      Connections {
        target: orchestration
        onConfigurationModeTextChanged: {
          configurationModeText.text = orchestration.configurationModeText;
        }
      }
    }
  }

  function resolveEnable() {
    if(orchestration.isConnected) {
      enableInput(!orchestration.isTuning);
    } else {
      enableInput(false);
    }
  }

  function enableInput(enable) {
    controllerSettings.enableInput(enable);
    pidSettings.enableInput(enable);
  }

  function debugMessage(message) {
    if(pidParameterPanel.isPanelCompleted) {
      debugLabel.visible = true;
      debugText.text = message;
    }
  }
}
