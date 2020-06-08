import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

RowLayout {

  property alias setpointIndicator: setpointIndicatorGauge
  property alias temperatureIndicator: temperatureIndicatorGauge
  property alias outputIndicator: outputIndicatorGauge

  IndicatorGauge {
    id: setpointIndicatorGauge
    name: qsTr("Setpoint")
    unitText: qsTr("°C")
    Layout.preferredWidth: Style.gaugeWidth
  }

  IndicatorGauge {
    id: temperatureIndicatorGauge
    name: qsTr("Temperature")
    unitText: qsTr("°C")
    Layout.preferredWidth: Style.gaugeWidth
  }

  IndicatorGauge {
    id: outputIndicatorGauge
    name: qsTr("Output")
    maximumValue: 256.0
    minimumValue: 0.0
    tickmarkStepSize: 32
    minorTickmarkCount: 8
    Layout.preferredWidth: Style.gaugeWidth
  }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

