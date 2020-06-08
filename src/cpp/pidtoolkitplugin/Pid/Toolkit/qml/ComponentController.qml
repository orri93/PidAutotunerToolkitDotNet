import QtQuick 2.4
import Pid.Toolkit 1.0
import Pid.Toolkit.Model 1.0 as Ptm

/* Note to use is connected directly as parameter for enabled
 * the is connected property need to implement a notifier
 */

ComponentControllerForm {

  property var orchestration: ptOrchestration
  property var configuration: ptOrchestration.configuration
  property var setpointAccuracy: ptOrchestration.configuration.ui.setpoint
  property var modbus: ptOrchestration.modbus

  manualBox.enabled: false // modbus.isConnected
  //manualBox.value: modbus.manual

  forceBox.model: ptModels.force
  forceBox.enabled: false // modbus.isConnected
  forceBox.textRole: "text"
  forceBox.valueRole: "value"

  setpointBox.enabled: false // modbus.isConnected
  //setpointBox.realValue: modbus.setpoint

  //settingButton.enabled: false // modbus.isConnected

  manualBox.onValueChanged: {
    console.log("Manual box value is " + manualBox.value);
    modbus.manual = manualBox.value;
  }

  forceBox.onActivated: {
    modbus.force = ptModels.force.force(forceBox.currentIndex);
  }

  setpointBox.onRealValueChanged: {
    modbus.setpoint = setpointBox.realValue;
  }

  settingButton.onClicked: {
    console.log("Controller setting button clicked");
  }

  Component.onCompleted: {
    forceBox.currentIndex = ptModels.force.index(modbus.force);
    setpointBox.accuracyObject = setpointAccuracy;
  }

  Connections {
    target: modbus
    onStatusChanged: {
      resolveUserInterface();
    }
  }

  Connections {
    target: modbus
    onManualChanged: {
      console.log("Modbus manual is " + modbus.manual);
      manualBox.value = modbus.manual;
    }
  }

  Connections {
    target: modbus
    onForceChanged: {
      forceBox.currentIndex = ptModels.force.index(modbus.force);
    }
  }

  Connections {
    target: modbus
    onSetpointChanged: {
      console.log("Modbus setpoint is " + modbus.setpoint);
      setpointBox.realValue = modbus.setpoint;
    }
  }

  Connections {
    target: configuration
  }

  function resolveUserInterface() {
    manualBox.enabled = modbus.isConnected;
    forceBox.enabled = modbus.isConnected;
    setpointBox.enabled = modbus.isConnected;
  }
}
