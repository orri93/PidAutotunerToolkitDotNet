import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

GroupBox {
  property alias serialPortBoxIndex: serialPortComboBox.currentIndex
  property alias serialBaudBoxIndex: serialBaudComboBox.currentIndex
  property alias statusText: connectionStatusText.text
  property alias serialPortComboBox: serialPortComboBox
  property alias serialBaudComboBox: serialBaudComboBox
  property alias serialPortModel: serialPortComboBox.model
  property alias serialBaudModel: serialBaudComboBox.model

  signal serialPortIndexChanged(int value)
  signal serialBaudIndexChanged(int value)
  signal connectButtonPressed()

  property string groupTitle: qsTr("Connection")
  
  property color groupTextColor: "gray"
  property color labelTextColor: "white"
  property color informationTextColor: "burlywood"

  property int labelFontPointSize:  8
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  function setConnectionState(state) {
    connectionStatusIndicator.active = state;
    if(state) {
      connectDisconnectButton.text = qsTr("Disconnect");
      enableSerialSettings(false);
    } else {
      connectDisconnectButton.text = qsTr("Connect");
      enableSerialSettings(true);
    }
  }

  function enableSerialSettings(isenable) {
    serialPortComboBox.enabled = isenable;
    serialBaudComboBox.enabled = isenable;
  }

  GridLayout {
    columns: 2
    rows: 2

    ColumnLayout {
      Layout.column: 0
      Layout.row: 0
      Label {
        text: qsTr("Serial Port")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      ComboBox {
        id: serialPortComboBox
        Layout.fillWidth: true
        Layout.column: 0
        Layout.row: 0
        onCurrentIndexChanged: {
          serialPortIndexChanged(currentIndex);
        }
      }
    }

    ColumnLayout {
      Layout.column: 1
      Layout.row: 0

      Label {
        text: qsTr("Serial Baud")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
        Layout.column: 1
        Layout.row: 0
      }
      ComboBox {
        id: serialBaudComboBox
        Layout.fillWidth: true
        Layout.column: 1
        Layout.row: 0
        onCurrentIndexChanged: {
          serialBaudIndexChanged(currentIndex);
        }
      }
    }

    Button {
      id: connectDisconnectButton
      Layout.fillWidth: true
      Layout.column: 0
      Layout.row: 1
      text: qsTr("Connect")
      onClicked: {
        connectButtonPressed();
      }
    }

    GridLayout {
      Layout.column: 1
      Layout.row: 1
      columns: 2
      rows: 1

      ColumnLayout {
        Layout.column: 0
        Layout.row: 0

        Label {
          text: qsTr("Status")
          color: labelTextColor
          Layout.leftMargin: labelLeftMargin
          font.pointSize: labelFontPointSize
        }
        Text {
          id: connectionStatusText
          text: qsTr("Starting")
          color: informationTextColor
          Layout.leftMargin: informationTextLeftMargin
          font.pointSize: informationFontPointSize
          Layout.fillWidth: true
        }
      }
      StatusIndicator {
        id: connectionStatusIndicator
        Layout.fillWidth: true
        Layout.column: 1
        Layout.row: 0
        color: "blue"
      }
    }
  }
}
