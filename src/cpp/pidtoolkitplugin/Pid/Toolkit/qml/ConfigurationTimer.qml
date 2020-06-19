import QtQuick 2.14
import Pid.Toolkit 1.0

ConfigurationTimerForm {

  property var orchestration: ptOrchestration
  property var setpointAccuracy: ptOrchestration.configuration.ui.setpoint
  property var settings: ptOrchestration.settings
  property var timer: ptOrchestration.settings.timer

  interval.intervalSpin.onValueModified: {
    timer.interval = interval.value;
  }

  interval.intervalBox.onToggled: {
    timer.synchronizeWithController = interval.isSynchronized;
  }

  Component.onCompleted: {
    interval.value = timer.interval;
    interval.isSynchronized = timer.synchronizeWithController;
  }

  Connections {
    target: timer
    onIntervalChanged: {
      interval.value = timer.interval;
    }
  }

  Connections {
    target: timer
    onSynchronizeWithControllerChanged: {
      interval.isSynchronized = timer.synchronizeWithController;
    }
  }

}
