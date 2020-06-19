import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

Item {
    id: element
    property alias quiter: quitButton
    property alias connector: connectButton
    property alias setter: settingButton

    property alias controllerComponent: ptControllerComponent

    Text {
        id: pidPanelTitleText
        x: 8
        y: 8
        text: Style.titleText
        color: Style.titleTextColor
        font.pointSize: Style.titleFontPointSize
    }

    ControlGroup {
        id: ptOutputGroup
        x: 10
        y: 50
        width: 380
        height: 250
        title: qsTr("Output")

        ViewOutput {
            id: ptOutputView
            y: 10
        }
    }

    ControlGroup {
        id: ptControllerGroup
        x: 10
        y: 300
        width: 380
        height: 220
        title: qsTr("Controller")

        ComponentController {
            id: ptControllerComponent
            y: 10
        }
    }

    ControlGroup {
        id: ptTuningGroup
        x: 10
        y: 520
        width: 380
        height: 160
        title: qsTr("Tuning")

        ComponentTuning {
            id: ptTuningComponent
            y: 10
        }
    }

    ControlGroup {
        id: ptStatusGroup
        x: 10
        y: 680
        width: 380
        height: 150
        title: qsTr("Status")

        ComponentStatus {
            id: ptStatusComponent
            y: 10
        }
    }

    Item {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        height: 50
        width: 380
        x: 10

        DelayButton {
            id: quitButton
            delay: Style.quitDelay
            text: qsTr("Quit")
            height: 50
            width: 50
        }

        Button {
            id: helpButton
            visible: false
            text: qsTr("Help")
            width: 80
            x: 60
            y: 3
        }

        Item {
            anchors.right: parent.right
            width: 170

            Button {
                id: connectButton
                text: qsTr("Connect")
                width: 80
                y: 3
            }

            Button {
                id: settingButton
                text: qsTr("Setting")
                width: 80
                x: 90
                y: 3
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:900;width:400}
}
##^##*/

