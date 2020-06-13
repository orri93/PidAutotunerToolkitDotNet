import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {

    property string what: qsTr("...")

    property alias value: intervalSpinBox.value
    property alias isSynchronized: intervalCheckBox.checked
    property alias intervalBox: intervalCheckBox

    SpinBox {
        id: intervalSpinBox
        Layout.preferredWidth: Style.preferredPanelItemWidth
    }

    CheckBox {
        id: intervalCheckBox
        text: "Synchronize with " + what
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

