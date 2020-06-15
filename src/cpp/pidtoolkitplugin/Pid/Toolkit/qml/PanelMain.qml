import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

PanelMainForm {

  property int mainWidth: parent.width
  property int mainHeight: parent.height

  Dialog {
    id: settingsDialog

    width: 980
    height: 600

    x: (parent.mainWidth - width) / 2
    y: (parent.mainHeight - height) / 2

    focus: true
    modal: true
    title: "Settings"
    standardButtons: Dialog.Ok | Dialog.Cancel

    TabViewSettings {
      anchors.fill: parent
    }

    onAccepted: console.log("Ok clicked")
    onRejected: console.log("Cancel clicked")
  }


  signal quitPid()
  signal connectPid()

  property var orchestration: ptOrchestration
  property var modbus: ptOrchestration.modbus

  quiter.onClicked: {
    if(modbus.isConnected) {
      orchestration.connectDisconnect();
    }
  }
  quiter.onActivated: quitPid()

  connector.onClicked: connectPid()

  setter.onClicked: {
    settingsDialog.open();
  }


  Connections {
    target: modbus
    onStatusChanged: {
      connector.text = modbus.isConnected ? "Disconnect" : "Connect";
    }
  }
}
