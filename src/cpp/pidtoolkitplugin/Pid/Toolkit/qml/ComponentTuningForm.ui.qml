import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

Item {

    property alias tuningActive: tuningIndicator.active
    property alias completed: completedIndicator.active

    property alias tuningBox: tuningComboBox

    Label {
        text: qsTr("Method")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 5
    }
    ComboBox {
        id: tuningComboBox
        width: 120
        y: 15
    }

    Button {
        id: tuningStartButton
        text: qsTr("Start")
        width: 80.0
        x: 170
        y: 15
    }
    Button {
        id: tuningSettingButton
        text: qsTr("Setting")
        width: 80.0
        x: 260
        y: 15
    }

    Label {
        text: qsTr("Tuning")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        y: 80
        x: 5
    }

    StatusIndicator {
        id: tuningIndicator
        color: Style.statusConnectionIndicator
        x: 70
        y: 75
    }

    Label {
        text: qsTr("Completed")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 175
        y: 80
    }

    StatusIndicator {
        id: completedIndicator
        color: Style.statusConnectionIndicator
        x: 240
        y: 75
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:120;width:380}
}
##^##*/

