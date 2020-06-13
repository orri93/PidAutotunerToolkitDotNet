import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    ControlGroup {
        title: qsTr("Output")

        ColumnLayout {
            ColumnLayout {
                id: temperatureAccuracyColumn
                Layout.preferredWidth: temperatureComponentUiNumber.width
                Layout.fillWidth: true
                Label {
                    text: qsTr("Temperature")
                    color: Style.labelTextColor
                    Layout.leftMargin: Style.labelLeftMargin
                    font.pointSize: Style.labelFontPointSize
                }
                ComponentUiNumber {
                    id: temperatureComponentUiNumber
                }
            }
            ColumnLayout {
                id: integralAccuracyColumn
                Layout.preferredWidth: integralComponentUiNumber.width
                Layout.fillWidth: true
                Label {
                    text: qsTr("Integral")
                    color: Style.labelTextColor
                    Layout.leftMargin: Style.labelLeftMargin
                    font.pointSize: Style.labelFontPointSize
                }
                ComponentUiNumber {
                    id: integralComponentUiNumber
                }
            }
        }
    }
}



