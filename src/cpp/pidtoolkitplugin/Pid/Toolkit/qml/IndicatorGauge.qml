import QtQuick 2.4
import Pid.Toolkit 1.0

IndicatorGaugeForm {

  property string unit: qsTr("")

  Component.onCompleted: {
    formatUnit(unit);
  }

  onUnitChanged: {
    formatUnit(unit);
  }

  function formatUnit(unit) {
    if(unit.length > 0) {
      unitText = "(" + unit + ")";
      unitVisible = true;
    } else {
      unitVisible = false;
    }
  }

}

