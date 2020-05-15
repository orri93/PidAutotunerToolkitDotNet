import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import Pid.Toolkit 1.0 as PidToolkit

import "pidtoolkit/PidToolkit.js" as PidToolkitJs

Tab {
  id: bbtet
  
  width: parent.width
  height: parent.height

  property var evaluationItemsHandle: null

  property var blackSettings: null

  title: qsTr("Evaluation")

  Connections {
    target: orchestration
    onBlackBoxChanged: {
      handleOrchestration("Black Box Changed");
    }
  }

  ColumnLayout {

    PidToolkit.EvaluationItems {
      id: evaluationItems
      Layout.fillWidth: true
      onReady: {
        bbtet.evaluationItemsHandle = evaluationItems;
        handleOrchestration("Evaluation Items ready");
      }

      onTargetTimeChanged: {
        if(blackSettings) {
          blackSettings.targetTimeFactor = factor;
        }
      }

      onIntegralBuildupChanged: {
        if(blackSettings) {
          blackSettings.integralBuildupFactor = factor;
        }
      }

      onPeakErrorChanged: {
        if(blackSettings) {
          blackSettings.peakErrorFactor = factor;
        }
      }

      onStableChanged: {
        if(blackSettings) {
          blackSettings.stableFactor = factor;
        }
      }

    }

  }

  //function resolveUserInterface() {
  //}


  function isReady() {
    if(bbtet.blackSettings) {
      if(bbtet.evaluationItemsHandle) {
        return bbtet.blackSettings;
      } else {
        PidToolkitJs.log("Evaluation Items Handle is undefined");
      }
    } else {
      bbtet.blackSettings = orchestration.blackBox;
      if(bbtet.blackSettings) {
        console.log("Assigned Black Settings");
        if(bbtet.evaluationItemsHandle) {
         return bbtet.blackSettings;
        } else {
          
        }
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

      bbtet.evaluationItemsHandle.setTargetTimeFactor(bbs.targetTimeFactor);
      bbtet.evaluationItemsHandle.setIntegralBuildupFactor(bbs.integralBuildupFactor);
      bbtet.evaluationItemsHandle.setPeakErrorFactor(bbs.peakErrorFactor);
      bbtet.evaluationItemsHandle.setStableFactor(bbs.stableFactor);

      //resolveUserInterface();
    } else {
      console.log("Black Box Tab Evaluation Not ready");
    }
  }

}
