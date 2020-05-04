import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import FloatValidator 1.0

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

  Component.onCompleted: {
    enableInput(false);
    orchestration.panelCompleted();
  }

  FloatValidator {
    id: floatValidator
  }

  GridLayout {
    Layout.alignment: Qt.AlignTop
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.margins: gridMargin

    columns: 2
    rows: 11

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
      id: kpColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 1
      Label {
        text: qsTr("Kp")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      TextInput {
        id: kpInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          orchestration.kpText = text
        }
      }
      Connections {
        target: orchestration
        onKpChanged: {
          kpInput.text = orchestration.kpText
        }
      }
    }

    ColumnLayout {
      id: integralColumn
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 1
      Label {
        text: qsTr("Integral")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: integralText
        text: realPlaceholderText
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.fillWidth: true
      }
      Connections {
        target: orchestration
        onIntegralTextChanged: {
          integralText.text = orchestration.integralText
        }
      }
    }

    ColumnLayout {
      id: kiColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 2
      Label {
        text: qsTr("Ki")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      TextInput {
        id: kiInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          orchestration.kiText = text
        }
      }
      Connections {
        target: orchestration
        onKiChanged: {
          kiInput.text = orchestration.kiText;
        }
      }
    }

    ColumnLayout {
      id: kdColumn
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 2
      Label {
        text: qsTr("Kd")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      TextInput {
        id: kdInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          orchestration.kdText = text
        }
      }
      Connections {
        target: orchestration
        onKdChanged: {
          kdInput.text = orchestration.kdText;
        }
      }
    }

    ColumnLayout {
      id: manualColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 3
      Label {
        text: qsTr("Manual")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      SpinBox {
        id: manualInput
        editable: true
        Layout.fillWidth: true
        onValueChanged: {
          orchestration.manual = value;
        }
      }
      Connections {
        target: orchestration
        onManualChanged: {
          manualInput.value = orchestration.manual;
        }
      }
    }

    ColumnLayout {
      id: forceColumn
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 3
      Label {
        text: qsTr("Mode")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: forceBox
        Layout.fillWidth: true
        model: modeModel
        onCurrentIndexChanged: {
          orchestration.forceIndex = currentIndex;
        }
      }
      Connections {
        target: orchestration
        onForceChanged: {
          forceBox.currentIndex = orchestration.forceIndex;
        }
      }
    }

    ColumnLayout {
      id: setpointColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 4
      Label {
        text: qsTr("Setpoint")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      RealSpinBox {
        id: setpointInput
        Layout.fillWidth: true
        decimals: 1
        onValueChanged: {
          orchestration.setpoint = value / 1000;
        }
      }
      Connections {
        target: orchestration
        onSetpointChanged: {
          setpointInput.value = 1000 * orchestration.setpoint;
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 4
      Label {
        text: qsTr("Interval")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: intervalText
        text: realPlaceholderText
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.minimumWidth: 130
      }
      Connections {
        target: orchestration
        onIntervalChanged: {
          intervalText.text = orchestration.interval.toString() + " ms";
        }
      }
    }

    ColumnLayout {
      id: intervalColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 5
      Label {
        text: qsTr("Interval")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: intervalComboBox
        Layout.fillWidth: true
        model: intervalModel
        onCurrentIndexChanged: {
          orchestration.intervalIndex = currentIndex;
        }
      }
      Connections {
        target: orchestration
        onIntervalChanged: {
          intervalComboBox.currentIndex = orchestration.intervalIndex;
        }
      }
    }

    ColumnLayout {
      id: intervalApplyColumn
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 5
      Label {
        text: qsTr("Apply to controller")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      CheckBox {
        id: intervalApplyCheckBox
        onCheckedChanged: {
          orchestration.applyIntervalToController = checked;
        }
      }
      Connections {
        target: orchestration
        onApplyIntervalToControllerChanged: {
          if(orchestration.applyIntervalToController) {
            debugMessage("Apply Interval To Controller Changed to true");
          } else {
            debugMessage("Apply Interval To Controller Changed to false");
          }
          intervalApplyCheckBox.checked =
              orchestration.applyIntervalToController;
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 6
      Label {
        text: qsTr("Tuning")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: tuningComboBox
        Layout.fillWidth: true
        model: tuningModel
        onCurrentIndexChanged: {
          orchestration.tuningIndex = currentIndex;
          if(pidParameterPanel.status == Component.Ready) {
            enableInput(currentIndex == 0);
          }
        }
      }
      Connections {
        target: orchestration
        onTuningChanged: {
          tuningComboBox.currentIndex = orchestration.tuningIndex;
          if(pidParameterPanel.status == Component.Ready) {
            enableInput(orchestration.tuningIndex == 0);
          }
        }
      }
    }

    Button {
      id: connectDisconnectButton
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 7
      text: qsTr("Connect")
      onClicked: {
        orchestration.connectDisconnect();
      }
    }

    Button {
      id: startStopLoggingButton
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 7
      text: qsTr("Start logging")
      onClicked: {
        orchestration.startStopLogging();
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 8
      Label {
        text: qsTr("Status")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: statusText
        text: qsTr("Starting")
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.fillWidth: true
      }
      Connections {
        target: orchestration
        onStatusStringChanged: {
          statusText.text = orchestration.statusString;
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 9
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
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 10
      Label {
        id: configurationModeLabel
        text: qsTr("Configuration Mode")
        visible: true
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

  Connections {
    target: orchestration
    onIsLoggingChanged: {
      if(orchestration.isLogging) {
        startStopLoggingButton.text = "Stop logging";
      } else {
        startStopLoggingButton.text = "Start logging";
      }
    }
  }

  Connections {
    target: orchestration
    onIsConnectedChanged: {
      enableInput(orchestration.isConnected);
      if(orchestration.isConnected) {
        intervalText.text = orchestration.interval.toString();
        connectDisconnectButton.text = "Disconnect";
        manualInput.value = orchestration.manual;
        setpointInput.value = 1000 * orchestration.setpoint;
        kpInput.value = 1000 * orchestration.kp;
        kiInput.value = 1000 * orchestration.ki;
        kdInput.value = 1000 * orchestration.kd;
      } else {
        connectDisconnectButton.text = "Connect";
      }
    }
  }

  function debugMessage(message) {
    if(pidParameterPanel.status == Component.Ready) {
      debugLabel.visible = true;
      debugText.text = message;
    }
  }

  function enableInput(enable) {
    manualInput.enabled = enable
    setpointInput.enabled = enable
    kpInput.enabled = enable
    kiInput.enabled = enable
    kdInput.enabled = enable
    forceBox.enabled = enable
  }
}
