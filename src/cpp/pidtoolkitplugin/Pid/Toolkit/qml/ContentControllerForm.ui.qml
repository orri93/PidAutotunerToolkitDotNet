import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {
    width: settingsConfiguration.width
    height: settingsConfiguration.height

    ConfigurationSettings {
        id: settingsConfiguration
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

