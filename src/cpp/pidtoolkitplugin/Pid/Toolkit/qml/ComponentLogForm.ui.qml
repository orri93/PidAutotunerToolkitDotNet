import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    RowLayout {
        Label {
            text: qsTr("Separator:")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        TextField {
            id: loggingSeparatorTextField
            Layout.leftMargin: Style.inputTextLeftMargin
            Layout.fillWidth: true
            Layout.preferredWidth: Style.preferredSeparatorInputWidth
            color: Style.inputTextColor
            font.pointSize: Style.inputFontPointSize
        }
    }

    ComponentFilePath {}
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

