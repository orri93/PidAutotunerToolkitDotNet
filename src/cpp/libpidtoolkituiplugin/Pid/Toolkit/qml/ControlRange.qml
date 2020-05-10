import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12

RowLayout {
  id: crrl

  property alias tuningRangeSlider: rangeSlider

  property alias tuningRangeFirstValue: rangeSlider.first.value
  property alias tuningRangeSecondValue: rangeSlider.second.value

  property alias rangeMaximum: rangeSlider.to
  property alias rangeStep: rangeSlider.stepSize

  signal rangeChanged(real from, real to, real maximum)

  property color labelTextColor: "midnightblue"
  property color indicatorsTextColor: "indigo"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10

  property real rangeIndicatorWidth: 40.0
  property real rangeMaximumWidth: 20.0

  property bool enableSignalling: false

  DoubleValidator { id: doubleValidator }

  function setEnabled(enable) {
    maximumTextInput.enabled = enable;
    rangeSlider.enabled = enable;
  }

  function setRange(from, to) {
    rangeSlider.first.value = from;
    rangeSlider.second.value = to;
  }

  function setMaximum(maximum) {
    rangeSlider.to = maximum;
  }

  function setStep(step) {
    rangeSlider.stepSize = step;
  }

  Component.onCompleted: {
    maximumTextInput.text = rangeMaximum.toString();
    firstIndicator.text = rangeSlider.first.value.toString();
    secondIndicator.text = rangeSlider.second.value.toString();
  }

  RowLayout {
    Label {
      color: labelTextColor
      font.pointSize: labelFontPointSize
      text: qsTr("Maximum: ")
    }
    TextInput {
      id: maximumTextInput
      validator: doubleValidator
      Layout.preferredWidth: rangeMaximumWidth
      font.pointSize: inputFontPointSize
      onEditingFinished: {
        rangeSlider.to = maximumTextInput.text;
        if(crrl.enableSignalling) {
          rangeChanged(
            rangeSlider.first.value,
            rangeSlider.second.value,
            rangeSlider.to);
        }
      }
    }
  }

  RangeSlider {
    id: rangeSlider
    first.onValueChanged: {
      firstIndicator.text = rangeSlider.first.value.toString();
      if(crrl.enableSignalling) {
        rangeChanged(
        rangeSlider.first.value,
        rangeSlider.second.value,
        rangeSlider.to);
      }
    }
    second.onValueChanged: {
      secondIndicator.text = rangeSlider.second.value.toString();
      if(crrl.enableSignalling) {
        rangeChanged(
        rangeSlider.first.value,
        rangeSlider.second.value,
        rangeSlider.to);
      }
    }
  }

  RowLayout {
    Label {
      id: firstIndicator
      horizontalAlignment: Text.AlignRight
      Layout.preferredWidth: rangeIndicatorWidth
      Layout.alignment: Qt.AlignRight
      color: indicatorsTextColor
    }
    Label {
      horizontalAlignment: Text.AlignHCenter
      Layout.alignment: Qt.AlignHCenter
      color: labelTextColor
      text: qsTr(" - ")
    }
    Label {
      id: secondIndicator
      horizontalAlignment: Text.AlignLeft
      Layout.preferredWidth: rangeIndicatorWidth
      Layout.alignment: Qt.AlignLeft
      color: indicatorsTextColor
    }
  }
}
