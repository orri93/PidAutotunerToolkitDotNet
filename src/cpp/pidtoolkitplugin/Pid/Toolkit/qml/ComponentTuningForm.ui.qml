import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

ColumnLayout {

  property alias tuningActive: tuningIndicator.active
  property alias completed: completedIndicator.active

  property alias tuningBox: tuningComboBox

  RowLayout {

    ColumnLayout {
      Layout.rightMargin: Style.panelItemMargin
      Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
        Label {
            text: qsTr("Method")
            color: Style.labelTextColor
            Layout.leftMargin: Style.labelLeftMargin
            font.pointSize: Style.labelFontPointSize
        }
        ComboBox {
            id: tuningComboBox
            Layout.preferredWidth: Style.preferredPanelItemWidth
        }
    }

    Item {
      id: element
      Layout.leftMargin: Style.panelItemMargin
      Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
      Layout.preferredWidth: Style.preferredPanelItemWidth
      Layout.preferredHeight: tuningSettingButton.height

      RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        Button {
          id: tuningStartButton
          text: qsTr("Start")

        }
        Button {
            id: tuningSettingButton
            text: qsTr("Setting")
        }
      }
    }
  }


  RowLayout {

    ColumnLayout {
      Layout.rightMargin: Style.panelItemMargin

      StatusIndicator {
          id: tuningIndicator
          color: Style.statusConnectionIndicator
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          Layout.preferredWidth: Style.preferredPanelItemWidth
      }

      Label {
        text: qsTr("Tuning")
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          color: Style.labelTextColor
          font.pointSize: Style.labelFontPointSize
      }
    }

    ColumnLayout {
      Layout.leftMargin: Style.panelItemMargin

      StatusIndicator {
          id: completedIndicator
          color: Style.statusConnectionIndicator
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          Layout.preferredWidth: Style.preferredPanelItemWidth
      }

      Label {
          text: qsTr("Completed")
          color: Style.labelTextColor
          font.pointSize: Style.labelFontPointSize
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      }

    }
  }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:640}
}
##^##*/

