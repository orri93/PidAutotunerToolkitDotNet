import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

GridLayout {
    columns: 2
    rows: 2

    ControlGroup {
        title: qsTr("Accuracy")
        Layout.rowSpan: 2
        Layout.column: 0
        Layout.row: 0

        ColumnLayout {
            ColumnLayout {
                id: setpointAccuracyColumn
                Layout.preferredWidth: setpointComponentUiAccuracy.width
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

        ControlGroup {
            title: qsTr("Range")
            Layout.column: 1
            Layout.row: 0

            ColumnLayout {
                ColumnLayout {
                    id: kpTuningRangeColumn
                    Layout.preferredWidth: kpTuningComponentUiRange.width
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
            Layout.column: 1
            Layout.row: 1

            ColumnLayout {
                ColumnLayout {
                    id: temperatureFormatColumn
                    Layout.preferredWidth: temperatureComponentUiFormat.width
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
