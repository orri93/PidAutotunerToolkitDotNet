import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

import "PidToolkit.js" as PidToolkitScript

GroupBox {
  property string groupTitle: qsTr("Logging")

  signal internalVariablesChanged(bool value)
  signal separatorChanged(string value)
  signal loggingFileChanged(string value)
  signal loggingTuningFileChanged(string value)

  signal ready()
  signal childDialog()
  signal childDialogCompleted()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredSeparatorInputWidth: 40.0

  function setInternalVariables(value) {
    internalVariablesCheckBox.checked = value;
  }

  function setSeparator(value) {
    loggingSeparatorTextInput.text = value;
  }

  function setLoggingFile(value) {
    loggingFilePath.setFilePath(value);
  }

  function setLoggingTuningFile(value) {
    loggingTuningFilePath.setFilePath(value);
  }

  Component.onCompleted: {
    ready();
  }

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  ColumnLayout {

    RowLayout {
      Label {
        text: qsTr("Separator:")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      TextInput {
        id: loggingSeparatorTextInput
        Layout.leftMargin: inputTextLeftMargin
        Layout.fillWidth: true
        Layout.preferredWidth: preferredSeparatorInputWidth
        color: inputTextColor
        font.pointSize: inputFontPointSize
        onEditingFinished: {
          separatorChanged(loggingSeparatorTextInput.text);
        }
      }

      CheckBox {
        id: internalVariablesCheckBox
        text: qsTr("Log Internal Variables")
        onClicked: {
          internalVariablesChanged(internalVariablesCheckBox.checked);
        }
      }
    }

    /*
    PidToolkit.PathValidator {
      id: pathValidator
      typeNumber: PidToolkitScript.PathValidatorType("File")
      restrictionNumber: PidToolkitScript.PathValidatorRestriction("Absolute")
    }
    */

    PidToolkit.FilePath {
      id: loggingFilePath
      //filePathValidator: pathValidator
      fileNameText: qsTr("Logging file path")
      fileDialogTitle: qsTr("Choose a file for the logging")
      onFilePathBrowse: {
        childDialog();
      }
      onFilePathBrowseCompleted: {
        childDialogCompleted();
      }
      onFilePathChanged: {
        loggingFileChanged(path);
      }
    }

    PidToolkit.FilePath {
      id: loggingTuningFilePath
      //filePathValidator: pathValidator
      fileNameText: qsTr("Tuning Logging file path")
      fileDialogTitle: qsTr("Choose a file for the tuning logging")
      onFilePathBrowse: {
        childDialog();
      }
      onFilePathBrowseCompleted: {
        childDialogCompleted();
      }
      onFilePathChanged: {
        loggingTuningFileChanged(path);
      }
    }

  }
}
