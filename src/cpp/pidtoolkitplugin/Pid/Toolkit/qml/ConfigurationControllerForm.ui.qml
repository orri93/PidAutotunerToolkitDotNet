import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

  property alias integralNumber: integralComponentUiNumber
  property alias temperatureNumber: temperatureComponentUiNumber

    ControlGroup {
        title: qsTr("Output")
        height: 200.0
        width: 370

        Label {
            text: qsTr("Temperature")
            color: Style.labelTextColor
            font.pointSize: Style.labelFontPointSize
        }
        ComponentUiNumber {
            id: temperatureComponentUiNumber
            height: 70.0
            width: 340
            y: 15.0
        }

        Label {
            text: qsTr("Integral")
            color: Style.labelTextColor
            font.pointSize: Style.labelFontPointSize
            y: 100.0
        }
        ComponentUiNumber {
            id: integralComponentUiNumber
            height: 70.0
            width: 340
            y: 115.0
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

