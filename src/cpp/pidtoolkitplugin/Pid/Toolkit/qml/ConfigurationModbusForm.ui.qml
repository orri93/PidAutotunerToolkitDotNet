import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    property alias modbusCommunicationComponent: communicationComponent

    ControlGroup {
        title: qsTr("Modbus Communication")

        ComponentCommunication {
            id: communicationComponent
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

