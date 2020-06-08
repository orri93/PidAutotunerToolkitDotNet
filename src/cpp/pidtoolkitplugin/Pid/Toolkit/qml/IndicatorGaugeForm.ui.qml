import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

ColumnLayout {

    property alias name: nameLabel.text
    property alias value: realGauge.value
    property alias unitText: unitLabel.text
    property alias unitVisible: unitLabel.visible
    property alias maximumValue: realGauge.maximumValue
    property alias minimumValue: realGauge.minimumValue
    property alias tickmarkStepSize: realGauge.tickmarkStepSize
    property alias minorTickmarkCount: realGauge.minorTickmarkCount
    property alias indicatorEnabled: realGauge.enabled

    RowLayout {
        Label {
            id: nameLabel
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }

        Label {
            id: unitLabel
            visible: false
            color: Style.unitTextColor
            font.pointSize: Style.unitFontPointSize
        }
    }

    Gauge {
        id: realGauge
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

