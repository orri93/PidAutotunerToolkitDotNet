import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

GroupBox {
    id: controlGroupForm

    property alias titleVerticalLocation: groupBoxLabel.x
    property alias titleColor: groupBoxLabel.color

    label: Label {
        id: groupBoxLabel
        text: controlGroupForm.title
        x: Style.groupTitleLocation
        color: Style.groupTextColor
    }
}
