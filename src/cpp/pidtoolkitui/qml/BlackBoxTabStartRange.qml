import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import Pid.Toolkit 1.0 as PidToolkit

Tab {
  id: bbtsar
  
  width: parent.width
  height: parent.height

  property var pidReady: null
  property var controllerReady: null
  property var tuningReady: null

  property var blackSettings: null
  property var blackKpRange: null
  property var blackKiRange: null

  property bool enableSignalling: false

  title: qsTr("Start and Range")

  function prepare() {
    if(bbtsar.controllerReady) {
      if(bbtsar.pidReady) {
        if(bbtsar.tuningReady) {
          setEnableSignalling(true);
          resolveUserInterface();
          return true;
        } else {
          console.log("Tuning not ready");
        }
      } else {
        console.log("PID not ready");
      }
    } else {
      console.log("Controller not ready");
    }
    return false;
  }

  function setEnableSignalling(enable) {
    if(bbtsar.controllerReady) {
      bbtsar.controllerReady.enableSignalling = enable;
    }
    if(bbtsar.pidReady) {
      bbtsar.pidReady.enableSignalling = enable;
    }
    if(bbtsar.tuningReady) {
      bbtsar.tuningReady.setEnableSignalling(enable);
    }
    enableSignalling = enable;
  }

  Connections {
    target: orchestration
    onBlackBoxChanged: {
      handleOrchestration("Black Box Changed");
    }
  }
  Connections {
    target: orchestration
    onStatusChanged: {
      if(orchestration.isConnected) {
        console.log("Status Changed - Is Connected");
      } else {
        console.log("Status Changed - Is not Connected");
      }
      bbtsar.resolveUserInterface();
    }
  }

  ColumnLayout {
    PidToolkit.ControllerItems {
      id: controllerItems
      Layout.fillWidth: true
      onReady: {
        bbtsar.controllerReady = controllerItems;
        handleOrchestration("Controller Items ready");
      }
      onManualChanged: {
        if(blackSettings) {
          blackSettings.manual = value;
        }
      }
      onSetpointChanged: {
        if(blackSettings) {
          blackSettings.setpoint = value;
        }
      }
      onUseCurrent: {
        if(orchestration.isConnected) {
          if(controllerItems.isBaseChecked) {
            controllerItems.setBase(orchestration.temperature);
          }
          controllerItems.setManual(orchestration.manual);
          controllerItems.setSetpoint(orchestration.setpoint);
        }
      }
    }

    PidToolkit.PidItems {
      id: pidItems
      Layout.fillWidth: true
      onReady: {
        bbtsar.pidReady = pidItems;
        handleOrchestration("PID Items ready");
      }
      onKpChanged: {
        if(bbtsar.blackSettings) {
          bbtsar.blackSettings.kp = kp;
        }
      }
      onKiChanged: {
        if(bbtsar.blackSettings) {
          bbtsar.blackSettings.ki = ki;
        }
      }
      onKdChanged: {
        if(bbtsar.blackSettings) {
          bbtsar.blackSettings.kd = kd;
        }
      }
      onMiddleChanged: {
        bbtsar.resolveUserInterface();
      }
      onUseCurrent: {
        if(orchestration.isConnected) {
          pidItems.setKp(orchestration.kp);
          pidItems.setKi(orchestration.ki);
        }
      }
    }

    PidToolkit.TuningItems {
      id: tuningItems
      onReady: {
        bbtsar.tuningReady = tuningItems;
        handleOrchestration("Tuning Items ready");
      }
      onKpRangeChanged: {
        if(bbtsar.blackSettings) {
          bbtsar.blackSettings.kpRange.minimum = tuningItems.kpTuningRangeFirstValue;
          bbtsar.blackSettings.kpRange.maximum = tuningItems.kpTuningRangeSecondValue;
        }
        resolveUserInterface();
      }
      onKiRangeChanged: {
        if(bbtsar.blackSettings) {
          bbtsar.blackSettings.kiRange.minimum = tuningItems.kiTuningRangeFirstValue;
          bbtsar.blackSettings.kiRange.maximum = tuningItems.kiTuningRangeSecondValue;
        }
        resolveUserInterface();
      }
    }
  }

  function resolveUserInterface() {
    if(bbtsar.controllerReady) {
      console.log("Update: Controller enable current set to " + orchestration.isConnected);
      bbtsar.controllerReady.setEnabledCurrent(orchestration.isConnected);
    } else {
      console.log("Update: Controller not Ready");
    }
    if(bbtsar.pidReady) {
      console.log("Update: PID enable current set to " + orchestration.isConnected);
      
      bbtsar.pidReady.setEnabledCurrent(
        orchestration.isConnected && !bbtsar.pidReady.isUseMiddleChecked);

      if(bbtsar.tuningReady) {
        console.log("Update: Tuning enable set range to " + bbtsar.pidReady.isUseMiddleChecked);
        bbtsar.tuningReady.setEnabledRange(bbtsar.pidReady.isUseMiddleChecked);

        bbtsar.pidReady.setKpRange(
          bbtsar.tuningReady.kpTuningRangeFirstValue,
          bbtsar.tuningReady.kpTuningRangeSecondValue);
        
        bbtsar.pidReady.setKiRange(
          bbtsar.tuningReady.kiTuningRangeFirstValue,
          bbtsar.tuningReady.kiTuningRangeSecondValue);

      } else {
        console.log("Update: Tuning not Ready");
      }
    } else {
      console.log("Update: PID not Ready");
    }
  }

  function isReady() {
    if(bbtsar.blackSettings) {
      if(
        bbtsar.controllerReady && 
        bbtsar.pidReady && 
        bbtsar.tuningReady) {
        return bbtsar.blackSettings;
      }
    } else {
      bbtsar.blackSettings = orchestration.blackBox;
      if(bbtsar.blackSettings) {
        bbtsar.blackKpRange =
          bbtsar.blackSettings.kpRange;
        bbtsar.blackKiRange =
          bbtsar.blackSettings.kiRange;

        console.log("Assigned Black Settings");
      } else {
        console.log("Black Settings undefined from Orchestration");
      }
    }
    return null;
  }

  function handleOrchestration(what) {
    console.log(what);
    var bbs = isReady();
    if(bbs) {
      var ci = bbtsar.controllerReady;
      var pi = bbtsar.pidReady;
      var ti = bbtsar.tuningReady;
      var kpr = bbtsar.blackKpRange;
      var kir = bbtsar.blackKpRange;

      var isBase = bbs.isBase;
      ci.setBase(bbs.base);
      ci.setIsBase(isBase);
      ci.setManual(bbs.manual);
      ci.setSetpoint(bbs.setpoint);

      pi.setKp(bbs.kp);
      pi.setKi(bbs.ki);
      pi.setKd(bbs.kd);

      pi.setKpRange(kpr.minimum, kpr.maximum);
      pi.setKiRange(kir.minimum, kir.maximum);

      ti.setKpRange(kpr.minimum, kpr.maximum);
      ti.setKiRange(kir.minimum, kir.maximum);

      resolveUserInterface();
    } else {
      console.log("Not ready");
    }
  }

}