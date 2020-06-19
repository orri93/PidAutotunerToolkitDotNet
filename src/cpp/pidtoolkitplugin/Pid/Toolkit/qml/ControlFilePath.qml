import QtQuick 2.4
import QtQuick.Dialogs 1.2

ControlFilePathForm {

  property string filePath: qsTr("")

  FileDialog {
      id: fileDialog
      title: qsTr("Please choose a file")
      visible: false
      height: Style.fileDialogHeight
      width: Style.fileDialogWidth
      selectExisting: false
      selectMultiple: false
      folder: shortcuts.home

      onAccepted: console.log("Fiel Dialog Ok clicked")
      onRejected: console.log("Fiel Dialog Cancel clicked")
  }


  filePathField.text: filePath

  filePathButton.onClicked: {
    fileDialog.open();
  }

  filePathField.onTextChanged: {
    filePath = filePathField.text;
  }

  onFilePathChanged: {
    filePathField.text = filePath;
  }

  Component.onCompleted: {
    filePathField.text = filePath;
  }

}
