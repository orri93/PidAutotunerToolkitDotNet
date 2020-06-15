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
      restrictionBox.currentIndex = ptModels.restriction.index(number.restriction);
    }
  }

  restrictionBox.onActivated: {
    if(number) {
      number.restriction = ptModels.restriction.restriction(restrictionBox.currentIndex);
    }
  }


}
