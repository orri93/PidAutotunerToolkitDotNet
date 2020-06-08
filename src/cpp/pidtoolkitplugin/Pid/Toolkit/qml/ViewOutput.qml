import QtQuick 2.4
import Pid.Toolkit 1.0

ViewOutputForm {

  property var orchestration: ptOrchestration
  property var modbus: ptOrchestration.modbus

  setpointIndicator.indicatorEnabled: false
  temperatureIndicator.indicatorEnabled: false
  outputIndicator.indicatorEnabled: false

  setpointIndicator.value: modbus.setpoint
  temperatureIndicator.value: modbus.temperature
  outputIndicator.value: modbus.output

  Connections {
    target: modbus
    onStatusChanged: {
      setpointIndicator.indicatorEnabled = modbus.isConnected;
      temperatureIndicator.indicatorEnabled = modbus.isConnected;
      outputIndicator.indicatorEnabled = modbus.isConnected;
    }
  }
}
