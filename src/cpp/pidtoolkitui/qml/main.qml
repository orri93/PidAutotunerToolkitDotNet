import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Window 2.14

Window {
  id: pidMainWindow

  width: 1024
  height: 800

  color: "#404040"

  title: pidParameterPanel.titleText

  visible: true

  PidPanel {
    id: pidParameterPanel
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
  }

  PidChart {
    id: pidChart
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: pidParameterPanel.right
    height: pidMainWindow.height
  }
}
