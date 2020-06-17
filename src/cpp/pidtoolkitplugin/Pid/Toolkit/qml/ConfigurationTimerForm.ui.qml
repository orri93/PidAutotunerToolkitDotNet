import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    ControlGroup {
        width: 410
        height: 80
        title: qsTr("Timer")

        ControlInterval {
            id: intervalControl
            what: qsTr("controller")
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:60;width:410}
}
##^##*/

