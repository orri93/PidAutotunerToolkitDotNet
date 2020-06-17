import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    property alias modbusCommunicationComponent: communicationComponent

    ControlGroup {
        width: 460
        height: 170
        title: qsTr("Modbus Communication")

        ComponentCommunication {
            id: communicationComponent
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:150;width:460}
}
##^##*/

