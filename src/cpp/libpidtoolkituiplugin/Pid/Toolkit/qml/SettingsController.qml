import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property alias modeBoxIndex: forceBox.currentIndex
  property alias modeBoxModel: forceBox.model

  signal modeIndexChanged(int value)
  signal setpointChanged(real value)
  signal manualChanged(real value)

  property string groupTitle: qsTr("Controller")

  property color groupTextColor: "gray"
  property color labelTextColor: "white"
  property color informationTextColor: "burlywood"

  property int labelFontPointSize:  8
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  function setUpdatedUiConfiguration(ui) {
    setpointInput.setRealUiNumber(ui.setpoint);
  }

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  function setSetpoint(value) {
    setpointInput.setRealValue(value);
  }

  function setManual(value) {
    manualInput.value = value;
  }

  function enableInput(isenable) {
    manualInput.enabled = isenable;
    setpointInput.enabled = isenable;
    forceBox.enabled = isenable;
  }

  GridLayout {
    columns: 2
    rows: 2

    ColumnLayout {
      id: manualColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 0
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
          manualChanged(value);
        }
      }
    }

    ColumnLayout {
      id: forceColumn
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 0
      Label {
        text: qsTr("Mode")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: forceBox
        Layout.fillWidth: true
        onCurrentIndexChanged: {
          modeIndexChanged(currentIndex);
        }
      }
    }

    ColumnLayout {
      id: setpointColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 1
      Label {
        text: qsTr("Setpoint")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      PidToolkit.RealSpinBox {
        id: setpointInput
        Layout.fillWidth: true
        onRealValueChanged: {
          setpointChanged(realValue);
        }
      }
    }
  }
}
