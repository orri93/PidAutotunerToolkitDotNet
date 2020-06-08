import QtQuick 2.14
import Pid.Toolkit 1.0
import Pid.Toolkit.Model.Tuning 1.0 as Ptmt

ComponentTuningForm {

  property var orchestration: ptOrchestration
  property var tuning: ptOrchestration.tuning

  tuningBox.model: ptModels.tuningMethod
  tuningBox.textRole: "text"
  tuningBox.valueRole: "value"

  Connections {
    target: tuning
    onStatusChanged: {
      tuningActive = tuning.status == Ptmt.Status.Tuning;
      completed = tuning.status == Ptmt.Status.Completed;
    }
  }
}
