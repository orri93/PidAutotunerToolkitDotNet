import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

import Pid.Toolkit 1.0

ColumnLayout {

  property alias connectivity: connectionIndicator.active
  property alias activity: activityIndicator.active
  property alias logging: loggingIndicator.active
  property alias statusMessage: statusText.text

  RowLayout {

    ColumnLayout {
      Layout.rightMargin: Style.panelItemMargin

      StatusIndicator {
          id: connectionIndicator
          color: Style.statusConnectionIndicator
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          Layout.preferredWidth: Style.preferredPanelItemWidth
      }

      Label {
        text: qsTr("Connection")
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          color: Style.labelTextColor
          font.pointSize: Style.labelFontPointSize
      }
    }

    ColumnLayout {
      Layout.leftMargin: Style.panelItemMargin

      StatusIndicator {
          id: activityIndicator
          color: Style.statusConnectionIndicator
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          Layout.preferredWidth: Style.preferredPanelItemWidth
      }

      Label {
          text: qsTr("Activity")
          color: Style.labelTextColor
          font.pointSize: Style.labelFontPointSize
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      }

    }
  }

  RowLayout {

    ColumnLayout {
      Layout.rightMargin: Style.panelItemMargin

      StatusIndicator {
          id: loggingIndicator
          color: Style.statusConnectionIndicator
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
          Layout.preferredWidth: Style.preferredPanelItemWidth
      }

      Label {
          text: qsTr("Logging")
          color: Style.labelTextColor
          font.pointSize: Style.labelFontPointSize
          Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
      }
    }

    Item {
      Layout.leftMargin: Style.panelItemMargin
      Layout.preferredWidth: Style.preferredPanelItemWidth
    }
  }

    ColumnLayout {
//        Label {
//            text: qsTr("Message")
//            color: Style.labelTextColor
//            Layout.leftMargin: Style.labelLeftMargin
//            font.pointSize: Style.labelFontPointSize
//        }
        Text {
            id: statusText
            color: Style.informationTextColor
            Layout.preferredWidth: Style.preferredPanelDoubleItemWidth
            font.pointSize: Style.informationFontPointSize
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#4c4e50";height:480;width:480}
}
##^##*/

