import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

GroupBox {
  property string groupTitle: qsTr("Controller")

  property alias isBaseChecked: baseCheckBox.checked

  signal baseChanged(real value)
  signal isBaseChanged(bool value)
  signal setpointChanged(real value)
  signal manualChanged(real value)

  signal useCurrent()
  signal ready()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"

  property int labelFontPointSize:  8
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  property bool enableSignalling: false

  function setBase(value) {
    baseInput.value = value;
  }
  function setIsBase(value) {
    baseCheckBox.checked = value;
    resolveUserInterface();
  }
  function setManual(value) {
    manualInput.value = value;
  }
  function setSetpoint(value) {
    setpointRealSpinBox.value = 1000 * value;
  }
  function setEnabledCurrent(enable) {
    useCurrentButton.enabled = enable;
  }

  Component.onCompleted: {
    ready();
  }

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  RowLayout {

    ColumnLayout {
      id: manualColumn
      Layout.fillWidth: true
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
          if(enableSignalling) {
            manualChanged(value);
          }
        }
      }
    }

    ColumnLayout {
      id: setpointColumn
      Layout.fillWidth: true
      Label {
        text: qsTr("Setpoint")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      PidToolkit.RealSpinBox {
        id: setpointRealSpinBox
        Layout.fillWidth: true
        decimals: 2
        onValueChanged: {
          if(enableSignalling) {
            setpointChanged(value / 1000);
          }
        }
      }
    }

    ColumnLayout {
      id: baseColumn

      Label {
        text: qsTr("Base")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      RowLayout {
        SpinBox {
          id: baseInput
          editable: true
          Layout.fillWidth: true
          onValueChanged: {
            if(enableSignalling) {
              console.log("Base input changed to " + baseInput.value);
              baseChanged(baseInput.value);
            }
          }
        }
        CheckBox {
          id: baseCheckBox
          onClicked: {
            if(enableSignalling) {
              console.log("Base Checked changed to " + baseCheckBox.checked);
              isBaseChanged(baseCheckBox.checked);
            }
            resolveUserInterface();
          }
        }
      }
    }

    Button {
      id: useCurrentButton
      Layout.alignment: Qt.AlignBottom
      text: qsTr("Use current")
      onClicked: {
        if(enableSignalling) {
          useCurrent();
        }
      }
    }
  }

  function resolveUserInterface() {
    if(isBaseChecked) {
      baseInput.enabled = true;
    } else {
      baseInput.enabled = false;
    }
  }
}

