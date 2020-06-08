import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    ComponentFactor {
        id: targetTimeFactor
        name: qsTr("Target time")
    }

    ComponentFactor {
        id: integralBuildupTimeFactor
        name: qsTr("Integral buildup")
    }

    ComponentFactor {
        id: peakErrorTimeFactor
        name: qsTr("Peak error")
    }

    ComponentFactor {
        id: stableTimeFactor
        name: qsTr("Stable")
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

