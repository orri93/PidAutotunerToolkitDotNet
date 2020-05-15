import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

import "PidToolkit.js" as PidToolkitJs

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property string groupTitle: qsTr("Range")

  property var kpTuningRange: null
  property var kiTuningRange: null

  signal kpTuningChanged(var range)
  signal kiTuningChanged(var range)

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

  function setKpTuningRange(range) {
    kpTuningRange = kpTuningUiRangeItem.setRangeObject(range);
  }
  function setKiTuningRange(range) {
    kiTuningRange = kiTuningUiRangeItem.setRangeObject(range);
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

    PidToolkit.UiRange {
      id: kpTuningUiRangeItem
      rangeName: qsTr("Kp Tuning")
      onRangeMinimumChanged: {
        if(kpTuningRange) {
          kpTuningRange.minimum = minimum;
          kpTuningChanged(kpTuningRange);
        }
      }
      onRangeMaximumChanged: {
        if(kpTuningRange) {
          kpTuningRange.maximum = maximum;
          kpTuningChanged(kpTuningRange);
        }
      }
    }

    PidToolkit.UiRange {
      id: kiTuningUiRangeItem
      rangeName: qsTr("Ki Tuning")
      onRangeMinimumChanged: {
        if(kiTuningRange) {
          kiTuningRange.minimum = minimum;
          kiTuningChanged(kiTuningRange);
        }
      }
      onRangeMaximumChanged: {
        if(kiTuningRange) {
          kiTuningRange.maximum = maximum;
          kiTuningChanged(kiTuningRange);
        }
      }
    }


  }

}
