import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Pid.Toolkit 1.0

Item {

    TabBar {
        id: tabBar
        currentIndex: 0

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
        width: 960.0
        height: 450.0
        y: 50

        TabSettingsMain {
          id: mainTab
        }

        TabSettingsUi {
            id: otherTab
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:450;width:960}D{i:6;invisible:true}
}
##^##*/

