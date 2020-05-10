import QtQuick 2.14
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4

GroupBox {
  Layout.alignment: Qt.AlignTop
  Layout.fillWidth: true

  property string groupTitle: qsTr("Controller Output")

  property alias output: outputGauge.value
  property alias maximumOutput: outputGauge.maximumValue
  
  property color groupTextColor: "gray"
  property color labelTextColor: "white"
  property color informationTextColor: "burlywood"

  property int labelFontPointSize:  8
  property int informationFontPointSize: 10

  property real labelLeftMargin: 2.0
  property real informationTextLeftMargin: 5.0

  property real groupTitleLocation: 10.0

  property real preferredWidth: 140.0

  property int maximumNumber: 10
  property int minimumNumber: 0

  function setSetpoint(value) {
    updateRange(value);
    setpointGauge.value = value;;
  }
  function setTemperture(value) {
    updateRange(value);
    tempertureGauge.value = value;
  }
  function setOutput(value) {
    if(value > 0.0 && value < 256.0) {
      outputGauge.value = value;
    }
  }

  function updateRange(value) {
    updateMinimum(value);
    updateMaximum(value);
  }

  function updateMinimum(value) {
    if(value < minimumNumber * 10.0) {
      minimumNumber = value / 10.0;
      minimumNumber = minimumNumber - 1;
      setpointGauge.minimumValue = minimumNumber * 10.0;
      tempertureGauge.minimumValue = minimumNumber * 10.0;
    }
  }
  function updateMaximum(value) {
    if(value > maximumNumber * 10.0) {
      maximumNumber = value / 10.0;
      maximumNumber = maximumNumber  + 1;
      setpointGauge.maximumValue = maximumNumber * 10.0;
      tempertureGauge.maximumValue = maximumNumber * 10.0;
    }
  }

  label: Label {
    x: groupTitleLocation
    text: groupTitle
    color: groupTextColor
  }

  RowLayout {
    ColumnLayout {
      Layout.fillWidth: true
      Label {
        text: qsTr("Setpoint")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Gauge {
        id: setpointGauge
        formatValue: function(value) {
          return value.toFixed(0);
        }
      }
    }
    ColumnLayout {
      Layout.fillWidth: true
      Label {
        text: qsTr("Temperature")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Gauge {
        id: tempertureGauge
        formatValue: function(value) {
          return value.toFixed(0);
        }
      }
    }
    ColumnLayout {
      Layout.fillWidth: true
      Label {
        text: qsTr("Output")
        color: labelTextColor
        Layout.leftMargin: labelLeftMargin
        font.pointSize: labelFontPointSize
      }
      Gauge {
        id: outputGauge
        maximumValue: 256.0
        minimumValue: 0.0
        tickmarkStepSize: 32
        minorTickmarkCount: 8
        formatValue: function(value) {
          return value.toFixed(0);
        }
      }
    }
  }
}