import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

ColumnLayout {
  id: rangeControlRowLayout

  property alias rangeName: rangeNameLabel.text

  property var rangeObject: null

  signal rangeMinimumChanged(real minimum)
  signal rangeMaximumChanged(real minimum)

  signal rangeChanged(var range)

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"
  property color inputTextErrorColor: "red"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0

  property real preferredRangeInputWidth: 60.0

  function setRangeObject(range) {
    if(range) {
      rangeControlRowLayout.rangeObject = range;
      setRangeMinimum(rangeControlRowLayout.rangeObject.minimum);
      setRangeMaximum(rangeControlRowLayout.rangeObject.maximum);
      //resolveUserInterface();
    } else {
      console.log("Setting undefined range for " +
        rangeControlRowLayout.rangeName);
    }
    return range;
  }

  function setRangeMinimum(minimum) {
    rangeMinimumTextInput.text = minimum.toString();
  }
  function setRangeMaximum(maximum) {
    rangeMaximumTextInput.text = maximum.toString();
  }

  DoubleValidator {
    id: doubleValidator
  }

  Label {
    id: rangeNameLabel
    color: labelTextColor
    Layout.leftMargin: labelLeftMargin
    font.pointSize: labelFontPointSize
  }
  RowLayout {

    Label {
      id: rangeMinimumLabel
      text: qsTr("Minimum: ")
      color: labelTextColor
      Layout.leftMargin: labelLeftMargin
      font.pointSize: labelFontPointSize
    }
    TextInput {
      id: rangeMinimumTextInput
      Layout.preferredWidth: preferredRangeInputWidth
      Layout.leftMargin: inputTextLeftMargin
      color: acceptableInput ? inputTextColor : inputTextErrorColor
      font.pointSize: inputFontPointSize
      validator: doubleValidator
      onEditingFinished: {
        if(rangeControlRowLayout.rangeObject) {
          rangeMinimumChanged(rangeMinimumTextInput.text);
        }
      }
    }

    Label {
      id: rangeMaximumLabel
      text: qsTr("Maximum: ")
      color: labelTextColor
      Layout.leftMargin: labelLeftMargin
      font.pointSize: labelFontPointSize
    }
    TextInput {
      id: rangeMaximumTextInput
      Layout.preferredWidth: preferredRangeInputWidth
      Layout.leftMargin: inputTextLeftMargin
      color: acceptableInput ? inputTextColor : inputTextErrorColor
      font.pointSize: inputFontPointSize
      validator: doubleValidator
      onEditingFinished: {
        if(rangeControlRowLayout.rangeObject) {
          rangeMaximumChanged(rangeMaximumTextInput.text);
        }
      }
    }
  }

}

