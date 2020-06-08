import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    ControlGroup {
        title: qsTr("Controller")

        ComponentTuneController {
            id: componentTuneController
        }
    }

    ControlGroup {
        title: qsTr("PID")

        ComponentTuneKpid {
            id: componentTuneKpid
        }
    }

    ControlGroup {
        title: qsTr("Range")

        ComponentTuneKpiRange {
            id: componentTuneKpiRange
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

