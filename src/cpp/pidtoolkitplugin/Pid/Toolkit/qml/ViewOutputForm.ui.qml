import QtQuick 2.14
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

Item {

    property alias setpointIndicator: setpointIndicatorGauge
    property alias temperatureIndicator: temperatureIndicatorGauge
    property alias outputIndicator: outputIndicatorGauge

    IndicatorGauge {
        id: setpointIndicatorGauge
        name: qsTr("Setpoint")
        unitText: qsTr("°C")
        width: 80
    }

    IndicatorGauge {
        id: temperatureIndicatorGauge
        name: qsTr("Temperature")
        unitText: qsTr("°C")
        width: 80
        x: 90
    }

    IndicatorGauge {
        id: outputIndicatorGauge
        name: qsTr("Output")
        maximumValue: 256.0
        minimumValue: 0.0
        tickmarkStepSize: 32
        minorTickmarkCount: 8
        width: 80
        x: 180
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#808080";height:480;width:640}
}
##^##*/

