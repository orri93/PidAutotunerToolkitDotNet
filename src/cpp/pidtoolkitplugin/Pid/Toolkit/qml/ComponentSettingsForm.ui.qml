import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

GridLayout {
    columns: 2
    rows: 2

    Button {
        Layout.column: 0
        Layout.row: 1
        text: qsTr("Settings")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

