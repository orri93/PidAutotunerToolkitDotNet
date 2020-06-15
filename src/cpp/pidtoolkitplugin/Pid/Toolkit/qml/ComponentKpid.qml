import QtQuick 2.4
import Pid.Toolkit 1.0

ComponentKpidForm {

  property var orchestration: ptOrchestration
  property var configuration: ptOrchestration.configuration
  property var ui: ptOrchestration.configuration.ui

  kpRealBox.accuracyObject: ui.kp
  kiRealBox.accuracyObject: ui.ki
  kdRealBox.accuracyObject: ui.kd

}
