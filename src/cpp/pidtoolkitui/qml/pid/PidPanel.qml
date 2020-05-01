import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import FloatValidator 1.0

ColumnLayout {
  id: pidParameterPanel

  property string tunePlaceholderText: qsTr("0.0")
  
  property color titleTextColor: "floralwhite"
  property color labelTextColor: "white"
  property color inputTextColor: "beige"
  property color informationTextColor: "burlywood"

  property int titleFontPointSize: 18
  property int labelFontPointSize:  8
  property int inputFontPointSize: 10
  property int informationFontPointSize: 10

  property real titleLeftMargin: 10.0
  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0
  property real informationTextLeftMargin: 5.0

  Component.onCompleted: {
    enableInput(false)
  }

  FloatValidator {
    id: floatValidator
  }

  Text {
    text: "PID"
    color: titleTextColor
    Layout.fillWidth: false
    Layout.leftMargin: titleLeftMargin
    font.pointSize: titleFontPointSize
  }

  GridLayout {
    columns: 2
    rows: 7

    ColumnLayout {
      id: kpColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 0
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
      Layout.row: 0
      Label {
        text: qsTr("Integral")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: integralText
        text: qsTr("0.0")
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
      Layout.row: 1
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
      Layout.row: 1
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
      Layout.row: 2
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
      Layout.row: 2
      Label {
        text: qsTr("Mode")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: forceBox
        Layout.fillWidth: true
        model: ListModel {
          id: forceItems
          ListElement { text: "Idle" }
          ListElement { text: "Manual" }
          ListElement { text: "Automatic" }
        }
        onCurrentIndexChanged: {
          orchestration.forceText = forceItems.get(currentIndex).text;
        }
      }
      Connections {
        target: orchestration
        onForceChanged: {
          forceBox.currentIndex = orchestration.force - 1;
        }
      }
    }

    ColumnLayout {
      id: setpointColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 3
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
      id: frequencyColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 4
      Layout.columnSpan: 2
      Label {
        text: qsTr("Frequency")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Slider {
        id: frequencySlider
        stepSize: 0.25
        value: 1
        from: 0.1
        to: 10
        Layout.fillWidth: true
        onValueChanged: {
          orchestration.refreshFrequency = value;
        }
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 3
      Label {
        text: qsTr("Interval")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: intervalText
        text: qsTr("0 ms")
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.minimumWidth: 130
      }
      Connections {
        target: orchestration
        onRefreshIntervalChanged: {
          intervalText.text = orchestration.refreshInterval.toString();
        }
      }
    }

    Button {
      id: connectDisconnectButton
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 5
      text: qsTr("Connect")
      onClicked: {
        orchestration.connectDisconnect();
      }
    }

    Button {
      id: startStopLoggingButton
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 5
      text: qsTr("Start logging")
      onClicked: {
        orchestration.startStopLogging();
      }
    }

    ColumnLayout {
      Layout.fillWidth: true
      Layout.columnSpan: 2
      Layout.column: 0
      Layout.row: 6
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
        intervalText.text = orchestration.refreshInterval.toString();
        connectDisconnectButton.text = "Disconnect";
        frequencySlider.value = orchestration.refreshFrequency;
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

  function enableInput(enable) {
    manualInput.enabled = enable
    setpointInput.enabled = enable
    kpInput.enabled = enable
    kiInput.enabled = enable
    kdInput.enabled = enable
    forceBox.enabled = enable
  }
}
