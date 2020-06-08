import QtQuick 2.4
import Pid.Toolkit 1.0

PanelMainForm {

  signal quitPid()
  signal connectPid()
  signal settingsPid()

  property var orchestration: ptOrchestration
  property var modbus: ptOrchestration.modbus

  quiter.onClicked: {
    if(modbus.isConnected) {
      orchestration.connectDisconnect();
    }
  }
  quiter.onActivated: quitPid()

  connector.onClicked: connectPid()

  setter.onClicked: settingsPid()

  Connections {
    target: modbus
    onStatusChanged: {
      connector.text = modbus.isConnected ? "Disconnect" : "Connect";
    }
  }
}
