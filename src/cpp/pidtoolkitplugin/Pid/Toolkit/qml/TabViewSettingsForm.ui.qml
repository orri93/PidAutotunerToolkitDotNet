import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Pid.Toolkit 1.0

Item {

    TabBar {
        id: tabBar
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
        currentIndex: tabBar.currentIndex

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
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
