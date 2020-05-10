import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

GroupBox {
  id: dpi

  property string groupTitle: qsTr("Start PID values")

  property alias isUseMiddleChecked: useMiddleCheckBox.checked
  //property alias 

  signal kpChanged(real kp);
  signal kiChanged(real kp);
  signal kdChanged(real kp);

  signal middleChanged(bool value)

  signal useCurrent()
  signal ready()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 80.0

  property real kpRangeFrom: 0.0
  property real kpRangeTo: 1.0
  property real kiRangeFrom: 0.0
  property real kiRangeTo: 1.0

  property real saveKp: 0.0
  property real saveKi: 0.0
  property real saveKd: 0.0

  property bool enableSignalling: false

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  PidToolkit.FloatValidator { id:floatValidator }

  function setEnabledCurrent(enable) {
    useCurrentButton.enabled = enable;
  }

  function setKp(kp) {
    dpi.saveKp = kp;
    if(!dpi.useMiddle) {
      kpTextInput.text = dpi.saveKp.toFixed(3).toString();
    }
  }
  function setKi(ki) {
    dpi.saveKi = ki;
    if(!dpi.useMiddle) {
      kiTextInput.text = dpi.saveKi.toFixed(3).toString();
    }
  }
  function setKd(kd) {
    dpi.saveKd = kd;
    kdTextInput.text = dpi.saveKd.toFixed(3).toString();
  }

  function setKpRange(from, to) {
    dpi.kpRangeFrom = from;
    dpi.kpRangeTo = to;
    resolveUserInterface();
  }
  function setKiRange(from, to) {
    dpi.kiRangeFrom = from;
    dpi.kiRangeTo = to;
    resolveUserInterface();
  }

  Component.onCompleted: {
    ready();
  }

  RowLayout {
    id: dpirl

    ColumnLayout {
      id: kpColumn
      Layout.preferredWidth: preferredWidth
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
        id: kpTextInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          dpi.saveKp = kpTextInput.text;
          if(enableSignalling) {
            kpChanged(dpi.saveKp);
          }
        }
      }
    }

    ColumnLayout {
      id: kiColumn
      Layout.preferredWidth: preferredWidth
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
        id: kiTextInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          dpi.saveKi = kiTextInput.text;
          if(enableSignalling) {
            kiChanged(dpi.saveKi);
          }
        }
      }
    }
    CheckBox {
      id: useMiddleCheckBox
      text: qsTr("Use middle of range")
      onClicked: {
        if(enableSignalling) {
          middleChanged(useMiddleCheckBox.checked);
        }
        dpi.resolveUserInterface();
      }
    }

    ColumnLayout {
      id: kdColumn
      Layout.preferredWidth: preferredWidth
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 1
      Label {
        text: qsTr("Kd")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      TextInput {
        id: kdTextInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          dpi.saveKd = kdTextInput.text;
          if(enableSignalling) {
            kdChanged(dpi.saveKd);
          }
        }
      }
    }

    Button {
      id: useCurrentButton
      text: qsTr("Use current")
      onClicked: {
        if(enableSignalling) {
          useCurrent();
        }
      }
    }
  }

  function middle(minimum, maximum) {
    return minimum + (maximum - minimum) / 2.0;
  }

  function showMiddle() {
    var middleKp = middle(dpi.kpRangeFrom, dpi.kpRangeTo).toFixed(3);
    var middleKi = middle(dpi.kiRangeFrom, dpi.kiRangeTo).toFixed(3);
    kpTextInput.text = middleKp;
    kiTextInput.text = middleKi;
  }

  function showSaved() {
    kpTextInput.text = saveKp.toFixed(3);
    kiTextInput.text = saveKi.toFixed(3);
  }

  function resolveUserInterface() {
    if(useMiddleCheckBox.checked) {
      showMiddle();
      kpTextInput.enabled = false;
      kiTextInput.enabled = false;
    } else {
      showSaved();
      kpTextInput.enabled = true;
      kiTextInput.enabled = true;
    }
  }
}
