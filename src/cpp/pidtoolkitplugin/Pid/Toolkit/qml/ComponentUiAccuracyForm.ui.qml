import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {
    property alias componentNumber: componentUiNumber
    property alias componentFormat: componentUiFormat

    ComponentUiFormat {
        id: componentUiFormat
        width: 170.0
    }

    ComponentUiNumber {
        id: componentUiNumber
        width: 340.0
        x: 180.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

