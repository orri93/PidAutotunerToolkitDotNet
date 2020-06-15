import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {
    ColumnLayout {
        Layout.preferredWidth: Style.preferredSeparatorInputWidth
        Label {
            text: qsTr("Separator")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        TextField {
            id: loggingSeparatorTextField
            Layout.leftMargin: Style.inputTextLeftMargin
            font.pointSize: Style.inputFontPointSize
            color: Style.inputTextColor
        }
    }
    ColumnLayout {
        Layout.preferredWidth: 410.0
        Label {
            text: qsTr("File")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ControlFilePath {
            id: logControlFilePath
        }
    }
}

