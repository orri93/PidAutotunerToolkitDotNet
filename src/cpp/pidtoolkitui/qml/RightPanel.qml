import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ColumnLayout {
  id: pidRightPanel

  property int currentRightPanel: 0

  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true
  Layout.fillHeight: true
  Layout.minimumWidth: 16.0

  function showRightPanel(index) {
    switch(index) {
    case 0:
      hideCurrent();
      currentRightPanel = 0;
      break;
    case 1:
      hideCurrent();
      realTimePanel.visible = true;
      currentRightPanel = 1;
      break;
    case 2:
      hideCurrent();
      tuningPanel.visible = true;
      currentRightPanel = 2;
      break;
    }
  }

  function hideCurrent() {
    switch(currentRightPanel) {
    case 0:
      break;
    case 1:
      realTimePanel.visible = false;
      break;
    case 2:
      tuningPanel.visible = false;
      break;
    }
  }

  RealTimePanel {
    id: realTimePanel
    visible: false
  }

  TuningPanel {
    id: tuningPanel
    visible: false
  }

}