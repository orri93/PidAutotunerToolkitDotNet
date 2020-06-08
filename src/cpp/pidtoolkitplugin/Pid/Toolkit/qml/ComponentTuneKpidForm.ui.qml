import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {

    DoubleValidator {
        id: doubleValidator
    }

    ColumnLayout {
        id: kpColumn
        Layout.preferredWidth: Style.preferredWidth
        Layout.fillWidth: true
        Label {
            text: qsTr("Kp")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        TextField {
            id: kpTextField
            Layout.leftMargin: Style.inputTextLeftMargin
            Layout.fillWidth: true
            color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
            font.pointSize: Style.inputFontPointSize
            validator: doubleValidator
        }
    }

    ColumnLayout {
        id: kiColumn
        Layout.preferredWidth: Style.preferredWidth
        Layout.fillWidth: true
        Label {
            text: qsTr("Ki")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        TextField {
            id: kiTextField
            Layout.leftMargin: Style.inputTextLeftMargin
            Layout.fillWidth: true
            color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
            font.pointSize: Style.inputFontPointSize
            validator: doubleValidator
        }
    }
    CheckBox {
        id: useMiddleCheckBox
        text: qsTr("Use middle of range")
    }

    ColumnLayout {
        id: kdColumn
        Layout.preferredWidth: Style.preferredWidth
        Layout.fillWidth: true
        Label {
            text: qsTr("Kd")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        TextField {
            id: kdTextField
            Layout.leftMargin: Style.inputTextLeftMargin
            Layout.fillWidth: true
            color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
            font.pointSize: Style.inputFontPointSize
            validator: doubleValidator
        }
    }

    Button {
        id: useCurrentButton
        text: qsTr("Use current")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

