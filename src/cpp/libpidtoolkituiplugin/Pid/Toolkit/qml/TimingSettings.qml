import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property alias intervalBoxIndex: intervalComboBox.currentIndex
  property alias intervalBoxModel: intervalComboBox.model

  signal intervalIndexChanged(int value)
  signal applyToControllerChanged(bool value)

  property string groupTitle: qsTr("Timing")

  property color groupTextColor: "gray"
  property color labelTextColor: "white"
  property color informationTextColor: "burlywood"

  property int labelFontPointSize:  8
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  function setApplyToController(value) {
    intervalApplyCheckBox.checked = value;
  }

  GridLayout {
    columns: 2
    rows: 1

    ColumnLayout {
      id: intervalColumn
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 0
      Label {
        text: qsTr("Interval")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: intervalComboBox
        Layout.fillWidth: true
        onCurrentIndexChanged: {
          intervalIndexChanged(currentIndex);
        }
      }
    }

    ColumnLayout {
      id: intervalApplyColumn
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 0
      Label {
        text: qsTr("Apply to controller")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      CheckBox {
        id: intervalApplyCheckBox
        onCheckedChanged: {
          applyToControllerChanged(checked);
        }
      }
    }
  }
}