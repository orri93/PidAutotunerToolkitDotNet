import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

  width: Style.panelWidth

  SwipeView {
    id: swipeView
    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
    currentIndex: 0

        ControlGroup {
            title: qsTr("Output")
            Layout.preferredWidth: Style.groupWidth

            ViewOutput {
                id: viewOutput
            }
        }

        ControlGroup {
            title: qsTr("Tuning")
            Layout.preferredWidth: Style.groupWidth

            ComponentTuning {
                id: tuning
            }
        }
    }

    TabBar {
        id: tabBar
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
        currentIndex: swipeView.currentIndex

        TabButton {
            id: outputTabButton
            text: qsTr("Output")
        }

        TabButton {
            id: tuningTabButton
            text: qsTr("Tuning")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

