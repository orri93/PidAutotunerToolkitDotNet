import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Pid.Toolkit 1.0

ColumnLayout {
    width: stackLayout.width
    height: stackLayout.height

    TabBar {
        id: tabBar
        currentIndex: stackLayout.currentIndex
        Layout.preferredWidth: stackLayout.width

        TabButton {
            text: qsTr("Main")
        }

        TabButton {
            text: qsTr("Ui")
        }
    }

    StackLayout {
        id: stackLayout
        currentIndex: tabBar.currentIndex
        Layout.preferredHeight: 600.0
        Layout.preferredWidth: 600.0

        ColumnLayout {
            ConfigurationModbus {
                id: modbusConfiguration
            }

            ConfigurationController {
                id: controllerConfiguration
            }

            ConfigurationTimer {
                id: timerConfiguration
            }
        }

        ConfigurationUi {
            id: uiConfiguration
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/
