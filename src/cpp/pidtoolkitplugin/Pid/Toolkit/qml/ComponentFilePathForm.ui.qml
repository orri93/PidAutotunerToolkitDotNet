import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {
    ColumnLayout {
        Label {
            id: filePathLabel
            text: qsTr("file")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }

        RowLayout {
            TextField {
                id: filePathTextField
                Layout.preferredWidth: Style.fileTextFieldWidth
                Layout.leftMargin: Style.inputTextLeftMargin
                Layout.fillHeight: true
                color: Style.inputTextColor
                font.pointSize: Style.inputFontPointSize
            }
            Button {
                id: filePathBrowseButton
                text: qsTr("Browse")
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

