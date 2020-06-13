import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    ControlGroup {
        title: qsTr("Timer")

        ControlInterval {
          id: intervalControl
          what: qsTr("controller")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

