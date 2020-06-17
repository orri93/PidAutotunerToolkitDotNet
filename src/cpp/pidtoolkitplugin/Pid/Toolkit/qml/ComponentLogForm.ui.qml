import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    Label {
        text: qsTr("Separator")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 5.0
    }
    TextField {
        id: loggingSeparatorTextField
        font.pointSize: Style.inputFontPointSize
        color: Style.inputTextColor
        y: 15.0
    }

    Label {
        text: qsTr("File")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 135.0
    }
    ControlFilePath {
        id: logControlFilePath
        height: 44.0
        width: 410
        y: 15.0
        x: 130.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:60;width:540}
}
##^##*/

