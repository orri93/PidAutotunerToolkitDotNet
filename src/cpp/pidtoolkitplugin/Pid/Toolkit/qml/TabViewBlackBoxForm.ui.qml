import QtQuick 2.14
//import QtQuick.Controls 1.4 as Qc140
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Pid.Toolkit 1.0

Item {

    TabBar {
        id: tabBar

        TabButton {
            text: qsTr("Main")
        }

        TabButton {
            text: qsTr("Other")
        }

        TabButton {
            text: qsTr("Evaluation")
        }

    }

    StackLayout {
        currentIndex: tabBar.currentIndex

        TabBlackBoxMain {
            id: mainTab
        }

        TabBlackBoxOther {
          id: otherTab
        }

        TabBlackBoxEvaluation {
          id: evaluationTab
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

