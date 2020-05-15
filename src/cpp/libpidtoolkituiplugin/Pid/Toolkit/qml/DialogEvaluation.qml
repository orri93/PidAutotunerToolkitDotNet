import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

import "PidToolkit.js" as PidToolkitJs

GroupBox {
  id: eigb
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property string groupTitle: qsTr("Evaluation")

  property var targetTimeFactor: null
  property var integralBuildupFactor: null
  property var peakErrorFactor: null
  property var stableFactor: null

  signal targetTimeChanged(var factor)
  signal integralBuildupChanged(var factor)
  signal peakErrorChanged(var factor)
  signal stableChanged(var factor)

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

  function setTargetTimeFactor(factor) {
    targetTimeFactor =
      targetTimeControlFactorItem.setFactorObject(factor);
  }
  function setIntegralBuildupFactor(factor) {
    integralBuildupFactor =
      integralBuildupControlFactorItem.setFactorObject(factor);
  }
  function setPeakErrorFactor(factor) {
    peakErrorFactor =
      peakErrorControlFactorItem.setFactorObject(factor);
  }
  function setStableFactor(factor) {
    stableFactor =
      stableControlFactorItem.setFactorObject(factor);
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

    PidToolkit.EvaluationFactor {
      id: targetTimeControlFactorItem
      factorName: qsTr("Target time")
      onFactorChanged: {
        if(targetTimeFactor) {
          targetTimeChanged(targetTimeFactor);
        }
      }
    }

    PidToolkit.EvaluationFactor {
      id: integralBuildupControlFactorItem
      factorName: qsTr("Integral buildup")
      onFactorChanged: {
        if(integralBuildupFactor) {
          integralBuildupChanged(integralBuildupFactor);
        }
      }
    }

    PidToolkit.EvaluationFactor {
      id: peakErrorControlFactorItem
      factorName: qsTr("Peak error")
      onFactorChanged: {
        if(peakErrorFactor) {
          peakErrorChanged(peakErrorFactor);
        }
      }
    }

    PidToolkit.EvaluationFactor {
      id: stableControlFactorItem
      factorName: qsTr("Stable")
      onFactorChanged: {
        if(stableFactor) {
          stableChanged(stableFactor);
        }
      }
    }

  }

}
