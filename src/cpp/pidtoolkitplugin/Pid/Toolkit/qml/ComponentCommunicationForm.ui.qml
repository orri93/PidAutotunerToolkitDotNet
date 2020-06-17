import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

Item {

    property alias serialPortBox: serialPortComboBox
    property alias serialBaudBox: serialBaudComboBox

    Label {
        text: "Serial Port"
        color: Style.dialogLabelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 5.0
    }

    ComboBox {
        id: serialPortComboBox
        width: 120.0
        y: 15.0
    }

    Label {
        text: "Baud Rate"
        color: Style.dialogLabelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 135.0
    }

    ComboBox {
        id: serialBaudComboBox
        width: 120.0
        x: 130.0
        y: 15.0
    }

    Label {
        text: "Slave ID"
        color: Style.dialogLabelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 265.0
    }

    SpinBox {
        from: 0
        to: 255
        width: 190.0
        x: 260.0
        y: 15.0
    }

    Label {
        text: "Data Bits"
        color: Style.dialogLabelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 5.0
        y: 70.0
    }

    ComboBox {
        id: dataBitsComboBox
        model: [8, 7]
        width: 120.0
        y: 85.0
    }

    Label {
        text: "Stop Bit"
        color: Style.dialogLabelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 135.0
        y: 70.0
    }

    ComboBox {
        id: stopBitComboBox
        model: [1, 1.5, 2]
        width: 120.0
        x: 130.0
        y: 85.0
    }

    Label {
        text: "Parity"
        color: Style.dialogLabelTextColor
        font.pointSize: Style.labelFontPointSize
        x: 265.0
        y: 70.0
    }

    ComboBox {
        id: parityComboBox
        model: ["None", "Odd", "Even"]
        width: 120.0
        x: 260.0
        y: 85.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:130;width:450}
}
##^##*/

