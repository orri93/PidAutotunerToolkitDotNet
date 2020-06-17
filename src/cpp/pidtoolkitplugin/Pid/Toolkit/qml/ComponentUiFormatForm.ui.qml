import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {
    property alias precision: precisionSpinBox.value

    implicitWidth: 190.0

    Label {
        text: qsTr("Precision")
        color: Style.labelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 2.0
    }
    SpinBox {
        id: precisionSpinBox
        width: 190.0
        y: 15.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

