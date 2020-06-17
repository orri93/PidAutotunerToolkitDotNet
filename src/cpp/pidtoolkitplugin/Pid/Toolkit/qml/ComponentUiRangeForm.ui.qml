import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    property alias rangeFromField: rangeFromTextField
    property alias rangeToField: rangeToTextField

    property real labelVerticalPosition: 10.0
    property real labelWidth: 40.0
    property real fieldWidth: 60.0

    property real labelMargin: 2.0
    property real fieldMargin: 5.0

    implicitWidth: 212.0

    DoubleValidator {
        id: doubleValidator
    }

    Label {
        id: rangeFromLabel
        text: qsTr("From: ")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        width: labelWidth
        y: labelVerticalPosition
        x: 2.0
    }
    TextField {
        id: rangeFromTextField
        color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
        font.pointSize: Style.inputFontPointSize
        validator: doubleValidator
        width: fieldWidth
        x: 47.0
    }

    Label {
        id: rangeToLabel
        text: qsTr("To: ")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        width: labelWidth
        y: labelVerticalPosition
        x: 109
    }
    TextField {
        id: rangeToTextField
        color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
        font.pointSize: Style.inputFontPointSize
        validator: doubleValidator
        width: fieldWidth
        x: 152
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#808080";height:480;width:640}
}
##^##*/

