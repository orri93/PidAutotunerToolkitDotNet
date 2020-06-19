import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    /** type:string The what text */
    property string what: qsTr("...")

    property alias value: intervalSpinBox.value
    property alias intervalSpin: intervalSpinBox
    property alias isSynchronized: intervalCheckBox.checked
    property alias intervalBox: intervalCheckBox

    SpinBox {
        id: intervalSpinBox
        width: 195.0
        to: 99999.0
        from: 0.0
    }

    CheckBox {
        x: 200.0
        width: 240.0
        id: intervalCheckBox
        text: "Synchronize with " + what
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

