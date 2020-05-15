import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4
import Pid.Toolkit 1.0 as PidToolkit

Dialog  {
  id: uiDialog

  property string titleText: qsTr("Black Box Settings")

  title: titleText

  signal uiAccepted()

  height: 500
  width: 680

  standardButtons: StandardButton.Ok | StandardButton.Cancel

  UiTabView {
    id: uiTabView
  }

  //function prepare() {
  //  return uiTabView.prepare();
  //}

  //function resetSignalling() {
  //  uiTabView.resetSignalling();
  //}

  onAccepted: {
    console.log("Saving the date ")
    orchestration.applyUiDialog();
    //resetSignalling();
    uiAccepted();
  }

  onRejected: {
    console.log("Rejecting the date ")
    orchestration.rejectUiDialog();
    //resetSignalling();
  }
}
