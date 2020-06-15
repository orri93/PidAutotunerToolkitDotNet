import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    property alias kpid: kpidComponent

    width: 540.0
    height: 80.0

    ControlGroup {
        title: qsTr("PID")
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        Layout.preferredHeight: parent.height - 10.0
        Layout.preferredWidth: parent.width - 10.0

        ComponentKpid {
            id: kpidComponent
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

