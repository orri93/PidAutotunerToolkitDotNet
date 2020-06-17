import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {
    ConfigurationModbus {
        id: modbusConfiguration
        width: 460.0
        height: 170
    }

    ConfigurationController {
        id: controllerConfiguration
        x: 470.0
    }

    ConfigurationTimer {
        id: timerConfiguration
        y: 180.0
    }

    ControlGroup {
        title: qsTr("Logging")
        y: 280
        width: 555
        height: 90

        ComponentLog {
          id: logComponent
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:400;width:960}D{i:2;invisible:true}
D{i:3;invisible:true}
}
##^##*/

