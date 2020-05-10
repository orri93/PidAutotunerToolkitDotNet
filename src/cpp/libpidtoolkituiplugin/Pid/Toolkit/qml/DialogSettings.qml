import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

GroupBox {
  property string groupTitle: qsTr("Settings")

  signal windowSizeChanged(int value)
  signal standardDeviationChanged(real value)

  signal ready()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color unitTextColor: "royalblue"

  property int labelFontPointSize:  8
  property int unitFontPointSize: 8

  property real labelLeftMargin: 2.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  function setStandardDeviation(value) {
    standardDeviationSpinBox.value = 1000 * value;
  }

  function setWindowSize(value) {
    windowSizeSpinBox.value = value;
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
        text: qsTr("Standard deviation")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }

      PidToolkit.RealSpinBox {
        id: standardDeviationSpinBox
        Layout.fillWidth: true
        decimals: 2
        onValueChanged: {
          //if(enableSignalling) {
            standardDeviationChanged(value / 1000);
          //}
        }
      }
    }
    ColumnLayout {
      Label {
        text: qsTr("Window Size")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      SpinBox {
        id: windowSizeSpinBox
        onValueChanged: {
          windowSizeChanged(windowSizeSpinBox.value);
        }
      }
    }
  }
}
