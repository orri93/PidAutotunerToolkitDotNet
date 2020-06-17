import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    property alias restrictionBox: restrictionComboBox
    property alias componentRange: componentUiRange

    implicitWidth: 340.0

    ComponentUiRange {
        id: componentUiRange
        width: 210
    }

    Label {
        text: qsTr("Restriction")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 222.0
    }

    ComboBox {
        id: restrictionComboBox
        width: 120.0
        x: 220.0
        y: 15.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

