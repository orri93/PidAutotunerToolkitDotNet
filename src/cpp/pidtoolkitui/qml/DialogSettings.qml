import QtQuick 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0

Dialog {
  focus: true
  modal: true
  title: "Settings"
  standardButtons: Dialog.Ok | Dialog.Cancel

  ContentSettings {
    spacing: 20
    anchors.fill: parent
  }

}
