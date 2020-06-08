import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    ColumnLayout {
        Label {
            text: qsTr("Kp Range")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ComponentRange {
            id: kpRange
            //rangeMaximum: 10.0
            //rangeStep: 0.1
        }
    }

    ColumnLayout {
        Label {
            text: qsTr("Ki Range")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ComponentRange {
            id: kiRange
            //rangeMaximum: 10.0
            //rangeStep: 0.1
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

