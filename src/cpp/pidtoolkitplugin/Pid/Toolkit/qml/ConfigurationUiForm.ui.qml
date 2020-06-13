import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    ControlGroup {
        title: qsTr("Accuracy")

        ColumnLayout {
            ColumnLayout {
                id: setpointAccuracyColumn
                Layout.preferredWidth: setpointComponentUiAccuracy.width
                Layout.fillWidth: true
                Label {
                    text: qsTr("Setpoint")
                    color: Style.labelTextColor
                    Layout.leftMargin: Style.labelLeftMargin
                    font.pointSize: Style.labelFontPointSize
                }
                ComponentUiAccuracy {
                    id: setpointComponentUiAccuracy
                }
            }
            ColumnLayout {
                id: kpAccuracyColumn
                Layout.preferredWidth: kpComponentUiAccuracy.width
                Layout.fillWidth: true
                Label {
                    text: qsTr("Kp")
                    color: Style.labelTextColor
                    Layout.leftMargin: Style.labelLeftMargin
                    font.pointSize: Style.labelFontPointSize
                }
                ComponentUiAccuracy {
                    id: kpComponentUiAccuracy
                }
            }
            ColumnLayout {
                id: kiAccuracyColumn
                Layout.preferredWidth: kiComponentUiAccuracy.width
                Layout.fillWidth: true
                Label {
                    text: qsTr("Ki")
                    color: Style.labelTextColor
                    Layout.leftMargin: Style.labelLeftMargin
                    font.pointSize: Style.labelFontPointSize
                }
                ComponentUiAccuracy {
                    id: kiComponentUiAccuracy
                }
            }
            ColumnLayout {
                id: kdAccuracyColumn
                Layout.preferredWidth: kdComponentUiAccuracy.width
                Layout.fillWidth: true
                Label {
                    text: qsTr("Kd")
                    color: Style.labelTextColor
                    Layout.leftMargin: Style.labelLeftMargin
                    font.pointSize: Style.labelFontPointSize
                }
                ComponentUiAccuracy {
                    id: kdComponentUiAccuracy
                }
            }
        }
    }

    RowLayout {

        ControlGroup {
            title: qsTr("Range")

            ColumnLayout {
                ColumnLayout {
                    id: kpTuningRangeColumn
                    Layout.preferredWidth: kpTuningComponentUiRange.width
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Kp Tuning")
                        color: Style.labelTextColor
                        Layout.leftMargin: Style.labelLeftMargin
                        font.pointSize: Style.labelFontPointSize
                    }
                    ComponentUiRange {
                        id: kpTuningComponentUiRange
                    }
                }
                ColumnLayout {
                    id: kiTuningRangeColumn
                    Layout.preferredWidth: kiTuningComponentUiRange.width
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Ki Tuning")
                        color: Style.labelTextColor
                        Layout.leftMargin: Style.labelLeftMargin
                        font.pointSize: Style.labelFontPointSize
                    }
                    ComponentUiRange {
                        id: kiTuningComponentUiRange
                    }
                }
            }
        }
        ControlGroup {
            title: qsTr("Format")

            ColumnLayout {
                ColumnLayout {
                    id: temperatureFormatColumn
                    Layout.preferredWidth: temperatureComponentUiFormat.width
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Temperature")
                        color: Style.labelTextColor
                        Layout.leftMargin: Style.labelLeftMargin
                        font.pointSize: Style.labelFontPointSize
                    }
                    ComponentUiFormat {
                        id: temperatureComponentUiFormat
                    }
                }

                ColumnLayout {
                    id: integralFormatColumn
                    Layout.preferredWidth: integralComponentUiFormat.width
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("Integral")
                        color: Style.labelTextColor
                        Layout.leftMargin: Style.labelLeftMargin
                        font.pointSize: Style.labelFontPointSize
                    }
                    ComponentUiFormat {
                        id: integralComponentUiFormat
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/

