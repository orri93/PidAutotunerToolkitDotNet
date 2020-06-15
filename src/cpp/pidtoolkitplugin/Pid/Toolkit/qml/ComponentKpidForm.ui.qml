import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {

  property alias kpRealBox: kpRealSpinBox
  property alias kiRealBox: kiRealSpinBox
  property alias kdRealBox: kdRealSpinBox

    DoubleValidator {
        id: doubleValidator
    }

    ColumnLayout {
        id: kpColumn
        Layout.preferredWidth: Style.preferredPanelItemWidth
        Layout.fillWidth: true
        Label {
            text: qsTr("Kp")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ControlRealSpinBox {
            id: kpRealSpinBox
            Layout.preferredWidth: Style.preferredPanelItemWidth
        }
    }

    ColumnLayout {
        id: kiColumn
        Layout.preferredWidth: Style.preferredPanelItemWidth
        Layout.fillWidth: true
        Label {
            text: qsTr("Ki")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ControlRealSpinBox {
            id: kiRealSpinBox
            Layout.preferredWidth: Style.preferredPanelItemWidth
        }
    }

    ColumnLayout {
        id: kdColumn
        Layout.preferredWidth: Style.preferredPanelItemWidth
        Layout.fillWidth: true
        Label {
            text: qsTr("Kd")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ControlRealSpinBox {
            id: kdRealSpinBox
            Layout.preferredWidth: Style.preferredPanelItemWidth
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

