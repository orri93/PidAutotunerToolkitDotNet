import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

GroupBox {
  property string groupTitle: qsTr("Timing")

  signal stableDurationChanged(int value)

  signal ready()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"

  property color unitTextColor: "royalblue"

  property int labelFontPointSize:  8
  property int unitFontPointSize: 8

  property real labelLeftMargin: 2.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  function setStableDuration(value) {
    stableDurationSpinBox.value = value;
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
      Label {
        text: qsTr("Stable duration")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      RowLayout {
        SpinBox {
          id: stableDurationSpinBox
          onValueChanged: {
            stableDurationChanged(stableDurationSpinBox.value);
          }
        }
        Label {
          text: qsTr("minutes")
          color: unitTextColor
          font.pointSize: unitFontPointSize
        }
      }
    }
  }
}
