import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import Pid.Toolkit 1.0 as PidToolkit

import "pidtoolkit/PidToolkit.js" as PidToolkitJs

Tab {
  id: uitm
  
  width: parent.width
  height: parent.height

  property var uiNumberItemsHandle: null
  property var uiRangeItemsHandle: null

  property var uiSettings: null

  title: qsTr("Ui")

  Connections {
    target: orchestration
    onUiChanged: {
      handleOrchestration("Ui Changed");
    }
  }

  ColumnLayout {

    PidToolkit.UiNumberItems {
      id: uiNumberItems
      Layout.fillWidth: true
      onReady: {
        uitm.uiNumberItemsHandle = uiNumberItems;
        handleOrchestration("UI Number Items ready");
      }
    }

    PidToolkit.UiRangeItems {
      id: uiRangeItems
      Layout.fillWidth: true
      onReady: {
        uitm.uiRangeItemsHandle = uiRangeItems;
        handleOrchestration("UI Range Items ready");
      }

    }

  }

  //function resolveUserInterface() {
  //}


  function isReady() {
    if(uitm.uiSettings) {
      if(uitm.uiNumberItemsHandle) {
        if(uitm.uiRangeItemsHandle) {
          return uitm.uiSettings;
        } else {
          PidToolkitJs.log("UI Range Items Handle is undefined");
        }
      } else {
        PidToolkitJs.log("UI Number Items Handle is undefined");
      }
    } else {
      uitm.uiSettings = orchestration.ui;
      if(uitm.uiSettings) {
        console.log("Assigned Ui Settings");
        if(uitm.uiNumberItemsHandle) {
          if(uitm.uiRangeItemsHandle) {
            return uitm.uiSettings;
          } else {
            PidToolkitJs.log("UI Range Items Handle is undefined");
          }
        } else {
          PidToolkitJs.log("UI Number Items Handle is undefined");
        }
      } else {
        console.log("Ui Settings undefined from Orchestration");
      }
    }
    return null;
  }

  function handleOrchestration(what) {
    console.log(what);
    var uis = isReady();
    if(uis) {

      uitm.uiNumberItemsHandle.setSetpointNumber(uis.setpoint);

      uitm.uiNumberItemsHandle.setKpNumber(uis.kp);
      uitm.uiNumberItemsHandle.setKiNumber(uis.ki);

      uitm.uiRangeItemsHandle.setKpTuningRange(uis.kpTuning);
      uitm.uiRangeItemsHandle.setKiTuningRange(uis.kiTuning);

      //resolveUserInterface();
    } else {
      console.log("Ui Tab Evaluation Not ready");
    }
  }

}
