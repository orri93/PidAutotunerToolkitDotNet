import QtQuick 2.4

import Pid.Toolkit 1.0
import Pid.Toolkit.Model 1.0 as Ptm

ComponentCommunicationForm {

  property var orchestration: ptOrchestration
  property var setpointAccuracy: ptOrchestration.configuration.ui.setpoint
  property var modbus: ptOrchestration.modbus

  serialPortBox.model: ptModels.serialPort
  serialPortBox.textRole: "portText"
  serialPortBox.valueRole: "portValue"

  serialBaudBox.model: ptModels.serialBaud
  serialBaudBox.textRole: "baudText"
  serialBaudBox.valueRole: "baudValue"

  serialPortBox.onActivated: {
    modbus.serialPort = ptModels.serialPort.port(serialPortBox.currentIndex);
  }

  serialBaudBox.onActivated: {
    modbus.serialBaud = ptModels.serialBaud.baud(serialBaudBox.currentIndex);
  }

  Component.onCompleted: {
    serialPortBox.currentIndex = ptModels.serialPort.index(modbus.serialPort);
    serialBaudBox.currentIndex = ptModels.serialBaud.index(modbus.serialBaud);
  }

  Connections {
    target: modbus
    onSerialPortChanged: {
      serialPortBox.currentIndex = ptModels.serialPort.index(modbus.serialPort);
    }
  }

  Connections {
    target: modbus
    onSerialBaudChanged: {
      serialBaudBox.currentIndex = ptModels.serialBaud.index(modbus.serialBaud);
    }
  }

}
