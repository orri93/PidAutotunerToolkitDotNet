import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {
    ColumnLayout {
        id: manualColumn
        Layout.fillWidth: true
        Label {
            text: qsTr("Manual")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        SpinBox {
            id: manualInput
            editable: true
            Layout.fillWidth: true
        }
    }

    ColumnLayout {
        id: setpointColumn
        Layout.fillWidth: true
        Label {
            text: qsTr("Setpoint")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ControlRealSpinBox {
            id: setpointRealSpinBox
            Layout.fillWidth: true
        }
    }

    ColumnLayout {
        id: baseColumn

        Label {
            text: qsTr("Base")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        RowLayout {
            SpinBox {
                id: baseInput
                editable: true
                Layout.fillWidth: true
            }
            CheckBox {
                id: baseCheckBox
            }
        }
    }

    Button {
        id: useCurrentButton
        Layout.alignment: Qt.AlignBottom
        text: qsTr("Use current")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

