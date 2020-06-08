import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12

import Pid.Toolkit 1.0

ColumnLayout {
    id: column

    property alias quiter: quitButton
    property alias connector: connectButton
    property alias setter: settingButton

    width: Style.panelWidth

    Text {
        id: pidPanelTitleText
        text: Style.titleText
        color: Style.titleTextColor
        font.pointSize: Style.titleFontPointSize
        Layout.margins: Style.panelMargin
    }

    ColumnLayout {
      Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

      ControlGroup {
        id: ptOutputGroup
        title: qsTr("Output")
        Layout.preferredWidth: Style.groupWidth

        ViewOutput {
          id: ptOutputView
        }
      }

      ControlGroup {
        id: ptControllerGroup
        title: qsTr("Controller")
        Layout.preferredWidth: Style.groupWidth

          ComponentController {
            id: ptControllerComponent
          }
        }

      ControlGroup {
        id: ptTuningGroup
        title: qsTr("Tuning")
        Layout.preferredWidth: Style.groupWidth

        ComponentTuning {
          id: ptTuningComponent
        }
      }

      ControlGroup {
        id: ptStatusGroup
        title: qsTr("Status")
        Layout.preferredWidth: Style.groupWidth

        ComponentStatus {
          id: ptStatusComponent
        }
      }
    }

    RowLayout {
      id: pidPanelButtonRow
      Layout.fillWidth: true
      Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
      Layout.preferredWidth: Style.groupWidth
      Layout.margins: Style.panelMargin

      RowLayout {
        id: pidPanelMainButtonRow
        DelayButton {
              id: quitButton
              delay: Style.quitDelay
              Layout.preferredHeight: Style.preferredButtonSize
              Layout.preferredWidth: Style.preferredButtonSize
              text: qsTr("Quit")
          }

        Button {
            id: helpButton
            visible: false
            Layout.preferredHeight: Style.preferredButtonSize
            text: qsTr("Help")
        }

      }

      RowLayout {
        id: pidPanelOtherButtonRow
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

        Button {
            id: connectButton
            Layout.preferredHeight: Style.preferredButtonSize
            text: qsTr("Connect")
        }

        Button {
            id: settingButton
            Layout.preferredHeight: Style.preferredButtonSize
            text: qsTr("Setting")
        }
      }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:900;width:640}
}
##^##*/

