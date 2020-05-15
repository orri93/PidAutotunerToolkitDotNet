import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

import "PidToolkit.js" as PidToolkitJs

RowLayout {
  id: factorControlRowLayout

  property alias factorName: factorNameLabel.text

  property var factorObject: null

  signal factorIncludedChanged(bool value)
  signal operationIndexChanged(int index)
  signal factorValueChanged(real value)
  signal factorIsReverseChanged(bool value)
  signal factorReverseChanged(real value)

  signal factorChanged(var factor)

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"
  property color inputTextErrorColor: "red"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  property real preferredNumberInputWidth: 60.0

  function setFactorObject(factor) {
    if(factor) {
      factorControlRowLayout.factorObject = factor;
      setFactorIncluded(factor.isIncluded);
      PidToolkitJs.log("ControlFactor.qml", "Is included is " + factor.isIncluded);
      setOperationIndex(factor.operationIndex);
      PidToolkitJs.log("ControlFactor.qml", "Operation Index" + factor.operationIndex);
      setFactorValue(factor.value);
      setFactorIsReverse(factor.isReverse);
      setFactorReverse(factor.reverse);
      resolveUserInterface();
    } else {
      console.log("Setting undefined factor for " +
        factorControlRowLayout.factorName);
    }
    return factor;
  }

  function setFactorIncluded(value) {
    factorIncludedCheckBox.checked = value;
  }
  function setOperationIndex(index) {
    factorOperationComboBox.currentIndex = index;
  }
  function setFactorValue(value) {
    factorValueTextInput.text = value.toString();
  }
  function setFactorIsReverse(value) {
    factorIsReverseCheckBox.checked = value;
  }
  function setFactorReverse(value) {
    factorReverseTextInput.text = value.toString();
  }

  DoubleValidator {
    id: doubleValidator
  }

  ColumnLayout {
    Label {
      id: factorNameLabel
      color: labelTextColor
      Layout.leftMargin: labelLeftMargin
      font.pointSize: labelFontPointSize
    }
    RowLayout {
      CheckBox {
        id: factorIncludedCheckBox
        text: qsTr("Factor:")
        onClicked: {
          resolveUserInterface();
          if(factorControlRowLayout.factorObject) {
            factorControlRowLayout.factorObject.isIncluded =
              factorIncludedCheckBox.checked;
            factorChanged(factorControlRowLayout.factorObject);
          } else {
            factorIncludedChanged(factorIncludedCheckBox.checked);
          }
        }
      }
      TextInput {
        id: factorValueTextInput
        Layout.preferredWidth: preferredNumberInputWidth
        Layout.leftMargin: inputTextLeftMargin
        color: acceptableInput ? inputTextColor : inputTextErrorColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          if(factorControlRowLayout.factorObject) {
            factorControlRowLayout.factorObject.value =
              factorValueTextInput.text;
            factorChanged(factorControlRowLayout.factorObject);
          } else {
            factorValueChanged(factorValueTextInput.text);
          }
        }
      }
      ComboBox {
        id: factorOperationComboBox
        model: operationModel
        onCurrentIndexChanged: {
          if(factorControlRowLayout.factorObject) {
            PidToolkitJs.log("ControlFactor.qml", "Operation Combo Box Changed" +
              factorControlRowLayout.factorObject.operationIndex);
            factorControlRowLayout.factorObject.operationIndex =
              factorOperationComboBox.currentIndex;
            factorChanged(factorControlRowLayout.factorObject);
          }
          operationIndexChanged(factorOperationComboBox.currentIndex);
        }
      }
      CheckBox {
        id: factorIsReverseCheckBox
        text: qsTr("Reverse:")
        onClicked: {
          if(factorControlRowLayout.factorObject) {
            factorControlRowLayout.factorObject.isReverse =
              factorIsReverseCheckBox.checked;
            factorChanged(factorControlRowLayout.factorObject);
          }
          factorIsReverseChanged(factorIsReverseCheckBox.checked);
          resolveUserInterface();
        }
      }
      TextInput {
        id: factorReverseTextInput
        Layout.preferredWidth: preferredNumberInputWidth
        Layout.leftMargin: inputTextLeftMargin
        color: acceptableInput ? inputTextColor : inputTextErrorColor
        font.pointSize: inputFontPointSize
        validator: floatValidator
        onEditingFinished: {
          if(factorControlRowLayout.factorObject) {
            factorControlRowLayout.factorObject.reverse =
              factorReverseTextInput.text;
            factorChanged(factorControlRowLayout.factorObject);
          }
          factorReverseChanged(factorReverseTextInput.text);
        }
      }
    }
  }

  function resolveUserInterface() {
    if(factorIncludedCheckBox.checked) {
      factorValueTextInput.enabled = true;
      factorOperationComboBox.enabled = true;
      factorIsReverseCheckBox.enabled = true;
      factorReverseTextInput.enabled = factorIsReverseCheckBox.checked;
    } else {
      factorValueTextInput.enabled = false;
      factorOperationComboBox.enabled = false;
      factorIsReverseCheckBox.enabled = false;
      factorReverseTextInput.enabled = false;
    }
  }

}

