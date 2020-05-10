import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import Pid.Toolkit 1.0 as PidToolkit

GroupBox {
  property string groupTitle: qsTr("Tuning")

  property alias kpTuningRangeFirstValue: kpTuningRange.tuningRangeFirstValue
  property alias kpTuningRangeSecondValue: kpTuningRange.tuningRangeSecondValue
  property alias kiTuningRangeFirstValue: kiTuningRange.tuningRangeFirstValue
  property alias kiTuningRangeSecondValue: kiTuningRange.tuningRangeSecondValue

  signal kpRangeChanged(real from, real to, real maximum)
  signal kiRangeChanged(real from, real to, real maximum)

  signal ready()

  property color groupTextColor: "navy"
  property color labelTextColor: "midnightblue"

  property int labelFontPointSize:  8
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  property bool enableSignalling: false

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  function setEnableSignalling(enable) {
    enableSignalling = enable;
    kpTuningRange.enableSignalling = enable;
    kiTuningRange.enableSignalling = enable;
  }

  function setEnabledRange(enable) {
    kpTuningRange.setEnabled(enable);
    kiTuningRange.setEnabled(enable);
  }

  function setKpRange(from, to) {
    kpTuningRange.enableSignalling = false
    kpTuningRange.setRange(from, to);
    kpTuningRange.enableSignalling = enableSignalling
  }
  function setKiRange(from, to) {
    kiTuningRange.enableSignalling = false
    kiTuningRange.setRange(from, to);
    kiTuningRange.enableSignalling = enableSignalling
  }
  function setKpMaximum(maximum) {
    kpTuningRange.enableSignalling = false
    kpTuningRange.setMaximum(maximum);
    kpTuningRange.enableSignalling = enableSignalling
  }
  function setKiMaximum(maximum) {
    kiTuningRange.enableSignalling = false
    kiTuningRange.setMaximum(maximum);
    kiTuningRange.enableSignalling = enableSignalling
  }

  Component.onCompleted: {
    ready();
  }

  ColumnLayout {
    ColumnLayout {
      Label {
        text: qsTr("Kp Range")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      PidToolkit.TuningRange {
        id: kpTuningRange
        rangeMaximum: 10.0
        rangeStep: 0.1
        onRangeChanged: {
          if(enableSignalling) {
            kpRangeChanged(from, to, maximum);
          }
        }
      }
    }
    ColumnLayout {
      Label {
        text: qsTr("Kd Range")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      PidToolkit.TuningRange {
        id: kiTuningRange
        rangeMaximum: 1.0
        rangeStep: 0.01
        onRangeChanged: {
          if(enableSignalling) {
            kiRangeChanged(from, to, maximum);
          }
        }
      }
    }
  }

}
