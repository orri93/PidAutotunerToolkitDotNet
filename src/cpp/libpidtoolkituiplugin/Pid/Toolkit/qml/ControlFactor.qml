import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

RowLayout {

  property string name: qsTr("Name")

  property color labelTextColor: "white"
  property color inputTextColor: "beige"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  ColumnLayout {
    Label {
      text: name
      color: labelTextColor
      Layout.leftMargin: labelLeftMargin
      font.pointSize: labelFontPointSize
    }
    RowLayout {
      CheckBox {
        text: qsTr("Factor:")
      }
      TextInput {
        text: qsTr("0.1")
        color: inputTextColor
        font.pointSize: inputFontPointSize
      }
    }
  }

}
