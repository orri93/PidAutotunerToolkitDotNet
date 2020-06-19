import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Pid.Toolkit 1.0

Item {
    id: element

    TabBar {
        id: tabBar
        width: parent.width
        currentIndex: stackLayout.currentIndex
        TabButton {
            text: qsTr("Main")
        }

        TabButton {
            text: qsTr("Ui")
        }
    }

    StackLayout {
        id: stackLayout
        //currentIndex: 1
        currentIndex: tabBar.currentIndex
        anchors.top: tabBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        TabSettingsMain {
            id: mainTab
            height: 370
            width: 840
            x: 70
            y: 10
        }

        TabSettingsUi {
            id: otherTab
            height: 400
            width: 960
            x: 10
            y: 10
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:600;width:980}D{i:6;invisible:true}
}
##^##*/

