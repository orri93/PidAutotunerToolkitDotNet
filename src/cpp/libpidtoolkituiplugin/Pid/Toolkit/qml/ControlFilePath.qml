import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ColumnLayout {

  property string fileNameText: qsTr("file")

  signal filePathChanged(string path)

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  property real fileTextInputWidth: 320.0

  function setFilePath(path) {
    filePathTextEdit.text = path;
  }

  FileDialog {
    id: fileDialog
    visible: false
    height: 600
    width: 800
    selectExisting: false
    selectMultiple: false
    defaultSuffix: "log"
    title: "Please choose a " + fileNameText
    folder: shortcuts.home
    onAccepted: {
      filePathTextEdit.text = fileDialog.fileUrl;
      console.log("You chose: " + fileDialog.fileUrl)
      Qt.quit()
    }
    onRejected: {
      console.log("Canceled")
      Qt.quit()
    }
  }

  ColumnLayout {
    Label {
      text: qsTr("File Path")
      color: labelTextColor
      Layout.leftMargin: labelLeftMargin
      font.pointSize: labelFontPointSize
    }

    RowLayout {
      TextEdit {
        id: filePathTextEdit
        Layout.preferredWidth: fileTextInputWidth
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillHeight: true
        color: inputTextColor
        font.pointSize: inputFontPointSize
        onEditingFinished: {
          filePathChanged(filePathTextEdit.text);
        }
      }
      Button {
        id: filePathBrowseButton
        text: qsTr("Browse")
        onClicked: {
          fileDialog.fileUrl = filePathTextEdit.text
          fileDialog.open();
        }
      }
    }
  }
}

