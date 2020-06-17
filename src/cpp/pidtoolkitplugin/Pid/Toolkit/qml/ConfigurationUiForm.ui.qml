import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    implicitWidth: 960.0
    implicitHeight: 400.0

    ControlGroup {
        width: 640
        height: 400
        title: qsTr("Accuracy")

        Label {
            text: qsTr("Setpoint")
            color: Style.labelTextColor
            font.pointSize: 12.0
            width: 60.0
            y: 30
        }
        ComponentUiAccuracy {
            id: setpointComponentUiAccuracy
            x: 70.0
            y: 0.0
        }

        Label {
            text: qsTr("Kp")
            color: Style.labelTextColor
            font.pointSize: 12.0
            width: 60.0
            y: 130
        }
        ComponentUiAccuracy {
            id: kpComponentUiAccuracy
            x: 70.0
            y: 100.0
        }

        Label {
            text: qsTr("Ki")
            color: Style.labelTextColor
            font.pointSize: 12.0
            width: 60.0
            y: 230
        }
        ComponentUiAccuracy {
            id: kiComponentUiAccuracy
            x: 70.0
            y: 200.0
        }

        Label {
            text: qsTr("Kd")
            color: Style.labelTextColor
            font.pointSize: 12.0
            width: 60.0
            y: 330
        }
        ComponentUiAccuracy {
            id: kdComponentUiAccuracy
            x: 70.0
            y: 300.0
        }
    }

    ControlGroup {
        title: qsTr("Range")
        height: 190
        width: 310
        x: 650

        Label {
            text: qsTr("Kp Tuning")
            color: Style.labelTextColor
            font.pointSize: 12
            width: 70.0
            y: 30.0
        }
        ComponentUiRange {
            id: kpTuningComponentUiRange
            x: 80.0
            y: 0.0
        }

        Label {
            text: qsTr("Kp Tuning")
            color: Style.labelTextColor
            font.pointSize: 12
            width: 70.0
            y: 130.0
        }
        ComponentUiRange {
            id: kiTuningComponentUiRange
            x: 80.0
            y: 100.0
        }
    }

    ControlGroup {
        title: qsTr("Format")
        height: 190.0
        width: 310.0
        x: 650.0
        y: 210.0

        Label {
            text: qsTr("Temperature")
            color: Style.labelTextColor
            font.pointSize: 12
            width: 90.0
            y: 30.0
        }
        ComponentUiFormat {
            id: temperatureComponentUiFormat
            x: 100.0
            y: 0.0
        }

        Label {
            text: qsTr("Integral")
            color: Style.labelTextColor
            font.pointSize: 12
            width: 90.0
            y: 130.0
        }
        ComponentUiFormat {
            id: integralComponentUiFormat
            x: 100.0
            y: 100.0
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:400;width:960}
}
##^##*/

