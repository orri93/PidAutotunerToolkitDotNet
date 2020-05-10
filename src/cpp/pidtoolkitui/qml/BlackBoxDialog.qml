import QtQuick 2.14
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Extras 1.4
import Pid.Toolkit 1.0 as PidToolkit

Dialog  {
  id: blackBoxDialog

  property string titleText: qsTr("Black Box Settings")

  title: titleText

  height: 500
  width: 680

  standardButtons: StandardButton.Ok | StandardButton.Cancel

  BlackBoxTabView {
    id: blackBoxTabView
  }

  function prepare() {
    return blackBoxTabView.prepare();
  }

  function resetSignalling() {
    blackBoxTabView.resetSignalling();
  }

  onAccepted: {
    console.log("Saving the date ")
    orchestration.applyBlackBoxDialog();
    resetSignalling();
  }

  onRejected: {
    console.log("Rejecting the date ")
    orchestration.rejectBlackBoxDialog();
    resetSignalling();
  }
}
