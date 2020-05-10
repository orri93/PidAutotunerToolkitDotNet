import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property string groupTitle: qsTr("Evaluation")

  property color groupTextColor: "gray"
  property color labelTextColor: "white"
  property color inputTextColor: "beige"
  property color informationTextColor: "burlywood"
  property color unitTextColor: "cornsilk"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10
  property int informationFontPointSize: 10
  property int unitFontPointSize: 8

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

  RowLayout {

    ControlFactor {
      name: qsTr("Target time")
    }

    ControlFactor {
      name: qsTr("Integral buildup")
    }

    ControlFactor {
      name: qsTr("Peak error")
    }

    ControlFactor {
      name: qsTr("Stable")
    }

  }

}
