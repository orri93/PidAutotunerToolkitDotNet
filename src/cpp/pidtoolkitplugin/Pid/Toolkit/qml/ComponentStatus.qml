import QtQuick 2.14
import Pid.Toolkit 1.0
import Pid.Toolkit.Model 1.0 as Ptm

ComponentStatusForm {

  property var ptmodels: ptModels
  property var orchestration: ptOrchestration
  property var modbus: ptOrchestration.modbus

  Connections {
    target: ptOrchestration
    onIsLoggingChanged: {
      logging = ptOrchestration.isLogging;
    }
  }

  Connections {
    target: modbus
    onStatusChanged: {
      connectivity = modbus.isConnected;
    }
  }

  Connections {
    target: modbus
    onForceChanged: {
      activity = modbus.force == Ptm.Force.Auto;
    }
  }
}
