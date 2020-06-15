import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Pid.Toolkit 1.0

ColumnLayout {
    width: 600.0
    height: 600.0

    TabBar {
      id: tabBar
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
        Layout.preferredHeight: parent.height
        Layout.preferredWidth: parent.width

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

            ControlGroup {
                title: qsTr("Logging")

                ComponentLog {
                    id: logComponent
                }
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

