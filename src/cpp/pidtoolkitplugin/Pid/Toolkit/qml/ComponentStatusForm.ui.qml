import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

Item {
    property alias connectivity: connectionIndicator.active
    property alias activity: activityIndicator.active
    property alias logging: loggingIndicator.active
    property alias statusMessage: statusText.text

    Label {
        text: qsTr("Connection")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        y: 5
        x: 5
    }

    StatusIndicator {
        id: connectionIndicator
        color: Style.statusConnectionIndicator
        x: 70
        y: 0
    }

    Label {
        text: qsTr("Activity")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 175
        y: 5
    }

    StatusIndicator {
        id: activityIndicator
        color: Style.statusConnectionIndicator
        x: 240
    }

    Label {
        text: qsTr("Logging")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        y: 65
        x: 5
    }

    StatusIndicator {
        id: loggingIndicator
        color: Style.statusConnectionIndicator
        y: 60
        x: 70
    }

    Text {
        id: statusText
        color: Style.informationTextColor
        font.bold: true
        font.pointSize: Style.informationFontPointSize
        width: parent.width
        y: 100
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:480}
}
##^##*/

