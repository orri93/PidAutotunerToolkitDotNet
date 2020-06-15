import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

ColumnLayout {

  property alias manualBox: manualSpinBox
  property alias forceBox: forceComboBox
  property alias setpointBox: setpointRealSpinBox
  property alias settingButton: controllerSettingButton

    RowLayout {

        ColumnLayout {
            id: manualColumn
            Layout.rightMargin: Style.panelItemMargin

            Label {
                text: qsTr("Manual")
                color: Style.labelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }
            SpinBox {
                id: manualSpinBox
                editable: true
                Layout.preferredWidth: Style.preferredPanelItemWidth
            }
        }

        ColumnLayout {
            id: forceColumn
            Layout.leftMargin: Style.panelItemMargin

            Label {
                text: qsTr("Mode")
                color: Style.labelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }
            ComboBox {
                id: forceComboBox
                Layout.preferredWidth: Style.preferredPanelItemWidth
            }
        }
    }

    RowLayout {

        ColumnLayout {
            id: setpointColumn
            Layout.rightMargin: Style.panelItemMargin
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom

            Label {
                text: qsTr("Setpoint")
                color: Style.labelTextColor
                Layout.leftMargin: Style.labelLeftMargin
                font.pointSize: Style.labelFontPointSize
            }
            ControlRealSpinBox {
                id: setpointRealSpinBox
                Layout.preferredWidth: Style.preferredPanelItemWidth
            }
        }

        Item {
            id: element
            Layout.leftMargin: Style.panelItemMargin
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.preferredWidth: Style.preferredPanelItemWidth
            Layout.preferredHeight: controllerSettingButton.height

            RowLayout {
              anchors.horizontalCenter: parent.horizontalCenter
              Button {
                  id: controllerSettingButton
                  enabled: false
                  text: qsTr("Setting")
              }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

