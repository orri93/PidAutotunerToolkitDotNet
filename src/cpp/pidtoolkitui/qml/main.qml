import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Window 2.14

Window {
  id: pidMainWindow

  width: 1600
  height: 900

  color: "#404040"

  title: pidParameterPanel.titleText

  property bool isComponentCompleted: false

  visible: true

  Component.onCompleted: {
    isComponentCompleted = true
  }

  PidPanel {
    id: pidParameterPanel
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    onRightPanelChanged: {
      rightTimePanel.showRightPanel(panelIndex);
    }
  }

  RightPanel {
    id: rightTimePanel
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: parent.right
  }

  PidChart {
    id: pidChart
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: rightTimePanel.left
    anchors.left: pidParameterPanel.right
    height: pidMainWindow.height
  }
}
