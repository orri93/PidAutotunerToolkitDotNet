import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    property alias manualBox: manualSpinBox
    property alias forceBox: forceComboBox
    property alias setpointBox: setpointRealSpinBox
    property alias settingButton: controllerSettingButton

    Label {
        text: qsTr("Manual")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 5.0
    }
    SpinBox {
        id: manualSpinBox
        editable: true
        width: 190.0
        y: 15.0
    }

    Label {
        text: qsTr("Mode")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 205.0
    }
    ComboBox {
        id: forceComboBox
        width: 120.0
        x: 200.0
        y: 15.0
    }

    Label {
        text: qsTr("Setpoint")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        y: 100.0
        x: 5
    }
    ControlRealSpinBox {
        id: setpointRealSpinBox
        y: 115.0
    }

    Button {
        id: controllerSettingButton
        text: qsTr("Setting")
        enabled: false
        width: 90.0
        y: 115.0
        x: 200.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

