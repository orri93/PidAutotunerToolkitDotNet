import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2

ColumnLayout {

  property alias fileDialogBrowse: fileDialog
  property alias fileNameText: filePathLabel.text
  property alias fileDialogTitle: fileDialog.title
  property alias filePathValidator: filePathTextInput.validator

  signal filePathChanged(string path)
  signal filePathBrowse()
  signal filePathBrowseCompleted(bool result, string path)

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"
  property color inputTextErrorColor: "red"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  property real fileTextInputWidth: 320.0

  function setFilePath(path) {
    filePathTextInput.text = path;
  }

  FileDialog {
    id: fileDialog
    visible: false
    height: 600
    width: 800
    selectExisting: false
    selectMultiple: false
    title: qsTr("Please choose a file")
    folder: shortcuts.home
    onAccepted: {
      var urltext = fileDialog.fileUrl.toString();
      // Remove prefixed "file://"
      var path = urltext.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
      // Unescape html code like '%23' for '#'
      var cleanpath = decodeURIComponent(path);
      filePathTextInput.text = cleanpath;
      filePathChanged(filePathTextInput.text);
      filePathBrowseCompleted(true, filePathTextInput.text);
      filePathBrowseButton.enabled = true;
      filePathTextInput.enabled = true;
    }
    onRejected: {
      filePathBrowseCompleted(false, "");
      filePathBrowseButton.enabled = true;
      filePathTextInput.enabled = true;
    }
  }

  ColumnLayout {
    Label {
      id: filePathLabel
      text: qsTr("file")
      color: labelTextColor
      Layout.leftMargin: labelLeftMargin
      font.pointSize: labelFontPointSize
    }

    RowLayout {
      TextInput {
        id: filePathTextInput
        Layout.preferredWidth: fileTextInputWidth
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillHeight: true
        color: inputTextColor 
        //color: acceptableInput ? inputTextColor : inputTextErrorColor
        font.pointSize: inputFontPointSize;
        onEditingFinished: {
          filePathChanged(filePathTextInput.text);
        }
      }
      Button {
        id: filePathBrowseButton
        text: qsTr("Browse")
        onClicked: {
          filePathBrowseButton.enabled = false;
          filePathTextInput.enabled = false;
          filePathBrowse();
          fileDialog.open();
        }
      }
    }
  }
}

