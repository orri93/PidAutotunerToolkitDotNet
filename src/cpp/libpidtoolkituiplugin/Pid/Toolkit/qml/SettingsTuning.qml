import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property alias tuningBoxIndex: tuningComboBox.currentIndex
  property alias tuningBoxModel: tuningComboBox.model
  property alias tuningStatus: tuningStatusText.text

  signal tuningIndexChanged(int value)

  property string groupTitle: qsTr("Tuning")
  
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

  GridLayout {
    columns: 2
    rows: 1

    ColumnLayout {
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 0
      Label {
        text: qsTr("Method")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: tuningComboBox
        Layout.fillWidth: true
        onCurrentIndexChanged: {
          tuningIndexChanged(tuningComboBox.currentIndex);
        }
      }
    }
    ColumnLayout {
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 0
      Label {
        text: qsTr("Status")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Text {
        id: tuningStatusText
        color: informationTextColor
        Layout.leftMargin: informationTextLeftMargin
        font.pointSize: informationFontPointSize
        Layout.fillWidth: true
      }
    }
  }
}