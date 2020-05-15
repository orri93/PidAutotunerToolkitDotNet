import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import Pid.Toolkit 1.0 as PidToolkit

Tab {
  id: bbtto
  
  width: parent.width
  height: parent.height

  property var timingItemsHandle: null
  property var otherItemsHandle: null
  property var loggingItemsHandle: null

  property var blackSettings: null

  //property bool enableSignalling: false

  title: qsTr("Timers and Other")

  function prepare() {
    if(timingItemsHandle) {
      if(otherItemsHandle) {
        if(loggingItemsHandle) {
          return true;
        }
      }
    }
    return false;
  }

  function setEnableSignalling(enable) {
  }

  Connections {
    target: orchestration
    onBlackBoxChanged: {
      handleOrchestration("Black Box Changed");
    }
  }

  ColumnLayout {

    PidToolkit.TimingItems {
      id: timingItems
      Layout.fillWidth: true

      onReady: {
        timingItemsHandle = timingItems;
        handleOrchestration("Timing Items ready");
      }

      onStableDurationChanged: {
        if(blackSettings) {
          blackSettings.stableDuration = value;
        }
      }
    }

    PidToolkit.SettingItems {
      id: otherItems
      Layout.fillWidth: true
      onReady: {
        otherItemsHandle = otherItems;
        handleOrchestration("Other Items ready");
      }

      onWindowSizeChanged: {
        if(blackSettings) {
          blackSettings.windowSize = value;
        }
      }

      onStandardDeviationChanged: {
        if(blackSettings) {
          blackSettings.sd = value;
        }
      }
    }

    PidToolkit.LoggingItems {
      id: loggingItems
      Layout.fillWidth: true
      onReady: {
        loggingItemsHandle = loggingItems;
        handleOrchestration("Logging Items ready");
      }
      onChildDialog: {
        bbtto.enabled = false;
      }
      onChildDialogCompleted: {
        bbtto.enabled = true;
      }

      onInternalVariablesChanged: {
        if(blackSettings) {
          blackSettings.internalVariables= value;
        }
      }

      onSeparatorChanged: {
        if(blackSettings) {
          blackSettings.separator = value;
        }
      }
    }

  }

  function resolveUserInterface() {
  }


  function isReady() {
    if(bbtto.blackSettings) {
      if(timingItemsHandle && otherItemsHandle && loggingItemsHandle) {
        return bbtto.blackSettings;
      }
    } else {
      bbtto.blackSettings = orchestration.blackBox;
      if(bbtto.blackSettings) {
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

      timingItemsHandle.setStableDuration(bbs.stableDuration);

      otherItemsHandle.setWindowSize(bbs.windowSize);
      otherItemsHandle.setStandardDeviation(bbs.sd);

      loggingItemsHandle.setInternalVariables(bbs.internalVariables);
      loggingItemsHandle.setSeparator(bbs.separator);
      loggingItemsHandle.setLoggingFile(bbs.file);
      loggingItemsHandle.setLoggingTuningFile(bbs.tuningFile);

      resolveUserInterface();
    } else {
      console.log("Not ready");
    }
  }

}