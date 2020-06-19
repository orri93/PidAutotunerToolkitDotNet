import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    /*** type:string The File Path Field */
    property alias filePathField: filePathTextField

    /*** type:alias The File Path Field */
    property alias filePathButton: filePathBrowseButton

  implicitWidth: 405

    TextField {
        id: filePathTextField
        width: 320.0
        font.pointSize: Style.inputFontPointSize
        color: Style.inputTextColor
    }
    Button {
        id: filePathBrowseButton
        width: 80.0
        x: 325.0
        text: qsTr("Browse")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

