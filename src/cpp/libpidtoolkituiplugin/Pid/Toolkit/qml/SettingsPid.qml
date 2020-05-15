import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property alias kp: kpInput
  property alias ki: kiInput
  property alias kd: kdInput
  property alias integral: integralText
  
  signal kpTextChanged(string value)
  signal kiTextChanged(string value)
  signal kdTextChanged(string value)

  property string groupTitle: qsTr("PID")

  property color groupTextColor: "gray"
  property color labelTextColor: "white"
  property color inputTextColor: "beige"
  property color inputTextErrorColor: "red"
  property color informationTextColor: "burlywood"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  function enableInput(isenable) {
    kpInput.enabled = isenable;
    kiInput.enabled = isenable;
    kdInput.enabled = isenable;
  }

  GridLayout {
    Layout.alignment: Qt.AlignTop
    Layout.fillWidth: true
    columns: 2
    rows: 3

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
        id: kpInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: acceptableInput ? inputTextColor : inputTextErrorColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          kpChanged(kpInput.text)
        }
      }
    }

    ColumnLayout {
      id: integralColumn
      Layout.preferredWidth: preferredWidth
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
        id: kiInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        color: acceptableInput ? inputTextColor : inputTextErrorColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          kiChanged(kiInput.text)
        }
      }
    }

    ColumnLayout {
      id: kdColumn
      Layout.preferredWidth: preferredWidth
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
        color: acceptableInput ? inputTextColor : inputTextErrorColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          kdChanged(kdInput.text)
        }
      }
    } 
  }
}
