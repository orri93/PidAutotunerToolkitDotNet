import QtQuick 2.14

import Pid.Toolkit 1.0
import Pid.Toolkit.Model 1.0 as Ptm

ComponentUiNumberForm {

  property var number: null

  restrictionBox.model: ptModels.restriction
  restrictionBox.textRole: "text"
  restrictionBox.valueRole: "value"

  onNumberChanged: {
    if(number) {
      componentRange.range = number.range;
      rangeConnections.target = number.range;
      rangeConnections.enabled = true;
      restrictionBox.currentIndex = ptModels.restriction.index(number.restriction);
      numberConnections.target = number;
      numberConnections.enabled = true;
    }
  }

  restrictionBox.onActivated: {
    if(number) {
      number.restriction = ptModels.restriction.restriction(restrictionBox.currentIndex);
    }
  }

  Connections {
    id: rangeConnections
    enabled: false
    onRangeChanged: {
      componentRange.range = number.range;
    }
  }

  Connections {
    id: numberConnections
    enabled: false
    onRestrictionChanged: {
      restrictionBox.currentIndex = ptModels.restriction.index(number.restriction);
    }
  }

}
