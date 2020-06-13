import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

    property alias serialPortBox: serialPortComboBox
    property alias serialBaudBox: serialBaudComboBox

    RowLayout {
        ColumnLayout {
            Label {
                text: "Serial Port"
                color: Style.dialogLabelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }

            ComboBox {
                id: serialPortComboBox
                Layout.preferredWidth: 111.0
            }
        }

        ColumnLayout {
            Label {
                text: "Baud Rate"
                color: Style.dialogLabelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }

            ComboBox {
                id: serialBaudComboBox
                Layout.preferredWidth: 111.0
            }
        }

        ColumnLayout {
            Label {
                text: "Slave ID"
                color: Style.dialogLabelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }

            SpinBox {
                from: 0
                to: 255
                Layout.preferredWidth: 111.0
            }
        }
    }
    RowLayout {
        ColumnLayout {
            Label {
                text: "Data Bits"
                color: Style.dialogLabelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }

            ComboBox {
                id: dataBitsComboBox
                model: [8, 7]
                Layout.preferredWidth: 111.0
            }
        }

        ColumnLayout {
            Label {
                text: "Stop Bit"
                color: Style.dialogLabelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }

            ComboBox {
                id: stopBitComboBox
                model: [1, 1.5, 2]
            }
        }

        ColumnLayout {
            Label {
                text: "Parity"
                color: Style.dialogLabelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }

            ComboBox {
                id: parityComboBox
                model: ["None", "Odd", "Even"]
                Layout.preferredWidth: 111.0
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#c0c0c0"}
}
##^##*/

