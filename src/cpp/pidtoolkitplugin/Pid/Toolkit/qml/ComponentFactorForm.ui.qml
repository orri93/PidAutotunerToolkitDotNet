import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {

    property alias name: factorNameLabel.text

    DoubleValidator {
        id: doubleValidator
    }

    ColumnLayout {
        Label {
            id: factorNameLabel
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        RowLayout {
            CheckBox {
                id: factorIncludedCheckBox
                text: qsTr("Factor:")
            }
            TextField {
                id: factorValueTextField
                Layout.preferredWidth: Style.preferredNumberInputWidth
                Layout.leftMargin: Style.inputTextLeftMargin
                color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
                font.pointSize: Style.inputFontPointSize
                validator: doubleValidator
            }
            ComboBox {
                id: factorOperationComboBox
            }
            CheckBox {
                id: factorIsReverseCheckBox
                text: qsTr("Reverse:")
            }
            TextField {
                id: factorReverseTextField
                Layout.preferredWidth: Style.preferredNumberInputWidth
                Layout.leftMargin: Style.inputTextLeftMargin
                color: acceptableInput ? Style.inputTextColor : Style.errorTextColor
                font.pointSize: Style.inputFontPointSize
                validator: doubleValidator
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

