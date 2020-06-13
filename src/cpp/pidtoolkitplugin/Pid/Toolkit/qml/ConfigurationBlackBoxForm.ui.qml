import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

  property alias controllerTune: controllerComponentTune
  property alias kpidTune: kpidComponentTune
  property alias kpiRangeTune: kpiRangeComponentTune
  property alias evaluationTune: evaluationComponentTune

    ControlGroup {
        title: qsTr("Controller")

        ComponentTuneController {
            id: controllerComponentTune
        }
    }

    ControlGroup {
        title: qsTr("PID")

        ComponentTuneKpid {
            id: kpidComponentTune
        }
    }

    ControlGroup {
        title: qsTr("Range")

        ComponentTuneKpiRange {
            id: kpiRangeComponentTune
        }
    }

    ControlGroup {
        title: qsTr("Evaluation")

        ComponentTuneEvaluation {
            id: evaluationComponentTune
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

