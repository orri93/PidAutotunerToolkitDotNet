import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

RowLayout {

  property alias restrictionBox: restrictionComboBox
  property alias componentRange: componentUiRange

    ComponentUiRange {
        id: componentUiRange
    }

    ColumnLayout {
        Label {
            text: qsTr("Restriction")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ComboBox {
            id: restrictionComboBox
            Layout.preferredWidth: Style.preferredPanelItemWidth
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/
