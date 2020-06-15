import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

GridLayout {
    columns: 2
    rows: 2

    ConfigurationModbus {
        id: modbusConfiguration
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        Layout.column: 0
        Layout.row: 0
    }

    ConfigurationController {
        id: controllerConfiguration
        Layout.alignment: Qt.AlignRight | Qt.AlignTop
        Layout.column: 1
        Layout.row: 0
    }

    ConfigurationTimer {
        id: timerConfiguration
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        Layout.column: 0
        Layout.row: 1
    }

    ControlGroup {
        Layout.alignment: Qt.AlignRight | Qt.AlignTop
        title: qsTr("Logging")
        Layout.column: 1
        Layout.row: 1

        ComponentLog {
            id: logComponent
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

