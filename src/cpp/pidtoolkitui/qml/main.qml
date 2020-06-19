import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Window 2.14

import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12

import Pid.Toolkit 1.0 as Pt

Window {
  id: pidMainWindow

  width: Pt.Style.mainWindowWidth
  height: Pt.Style.mainWindowHeight
  color: Pt.Style.mainWindowColor

  title: Pt.Style.titleText
  visible: true

  property var orchestration: ptOrchestration
  property var modbus: ptOrchestration.modbus

  Component.onCompleted: {}

  Pt.PanelMain {
    id: mainPanel
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    onQuitPid: Qt.quit()
    width: 400

    onConnectPid: orchestration.connectDisconnect()
  }

  //Pt.PanelMulty {
  //  id: multyPanel
  //  anchors.top: parent.top
  //  anchors.bottom: parent.bottom
  //  anchors.right: parent.right
  //}

  PidChartPanel {
    id: pidChart
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    
    /* Switch for multy panel  */
    //anchors.right: multyPanel.left
    anchors.right: parent.right

    anchors.left: mainPanel.right
    height: pidMainWindow.height
  }
}
