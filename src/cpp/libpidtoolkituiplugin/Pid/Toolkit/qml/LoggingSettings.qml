import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  signal loggingButtonPressed()

  property string groupTitle: qsTr("Logging")
  
  property color groupTextColor: "gray"

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  function setLoggingState(state) {
    loggingStatusIndicator.active = state;
    if(state) {
      startStopLoggingButton.text = "Stop logging";
    } else {
      startStopLoggingButton.text = "Start logging";
    }
  }

  GridLayout {
    columns: 2
    rows: 1

    Button {
      id: startStopLoggingButton
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 0
      text: qsTr("Start logging")
      onClicked: {
        loggingButtonPressed();
      }
    }

    StatusIndicator {
      id: loggingStatusIndicator
      Layout.fillWidth: true
      Layout.column: 1
      Layout.row: 0
      color: "green"
    }
  }
}
