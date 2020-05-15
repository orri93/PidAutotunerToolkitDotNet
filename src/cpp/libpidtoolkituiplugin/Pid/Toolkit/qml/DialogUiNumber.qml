import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

import "PidToolkit.js" as PidToolkitJs

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property string groupTitle: qsTr("Number")

  property var setpointNumber: null
  property var temperatureNumber: null
  property var integralNumber: null

  property var kpNumber: null
  property var kiNumber: null
  property var kdNumber: null

  signal setpointChanged(var number)
  signal temperatureChanged(var number)
  signal integralChanged(var number)

  signal kpChanged(var number)
  signal kiChanged(var number)
  signal kdChanged(var number)

  signal ready()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"
  property color inputTextColor: "darkslateblue"
  property color inputTextErrorColor: "red"

  property int labelFontPointSize:  8
  property int inputFontPointSize: 10
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real inputTextLeftMargin: 5.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  function setSetpointNumber(number) {
    setpointNumber = setpointUiNumberItem.setNumberObject(number);
  }

  function setKpNumber(number) {
    kpNumber = kpUiNumberItem.setNumberObject(number);
  }
  function setKiNumber(number) {
    kiNumber = kiUiNumberItem.setNumberObject(number);
  }

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  Component.onCompleted: {
    ready();
  }

  ColumnLayout {

    PidToolkit.UiNumber {
      id: setpointUiNumberItem
      numberName: qsTr("Setpoint")
      onNumberMinimumChanged: {
        if(setpointNumber) {
          setpointNumber.minimum = minimum;
          setpointChanged(setpointNumber);
        }
      }
      onNumberMaximumChanged: {
        if(setpointNumber) {
          setpointNumber.maximum = maximum;
          setpointChanged(setpointNumber);
        }
      }
      onNumberPrecisionChanged: {
        if(setpointNumber) {
          setpointNumber.precision = precision;
          setpointChanged(setpointNumber);
        }
      }
      onNumberStepSizeChanged: {
        if(setpointNumber) {
          setpointNumber.stepSize = stepSize;
          setpointChanged(setpointNumber);
        }
      }
    }

    PidToolkit.UiNumber {
      id: kpUiNumberItem
      numberName: qsTr("Kp")
      onNumberMinimumChanged: {
        if(kpNumber) {
          kpNumber.minimum = minimum;
          kpChanged(kpNumber);
        }
      }
      onNumberMaximumChanged: {
        if(kpNumber) {
          kpNumber.maximum = maximum;
          kpChanged(kpNumber);
        }
      }
      onNumberPrecisionChanged: {
        if(kpNumber) {
          kpNumber.precision = precision;
          kpChanged(kpNumber);
        }
      }
      onNumberStepSizeChanged: {
        if(kpNumber) {
          kpNumber.stepSize = stepSize;
          kpChanged(kpNumber);
        }
      }
    }

    PidToolkit.UiNumber {
      id: kiUiNumberItem
      numberName: qsTr("Ki")
      onNumberMinimumChanged: {
        if(kiNumber) {
          kiNumber.minimum = minimum;
          kiChanged(kiNumber);
        }
      }
      onNumberMaximumChanged: {
        if(kiNumber) {
          kiNumber.maximum = maximum;
          kiChanged(kiNumber);
        }
      }
      onNumberPrecisionChanged: {
        if(kiNumber) {
          kiNumber.precision = precision;
          kiChanged(kiNumber);
        }
      }
      onNumberStepSizeChanged: {
        if(kiNumber) {
          kiNumber.stepSize = stepSize;
          kiChanged(kiNumber);
        }
      }

    }

  }

}
