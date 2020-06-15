import QtQuick 2.14

import Pid.Toolkit 1.0

ComponentUiAccuracyForm {

  property var accuracy: null

  onAccuracyChanged: {
    if(accuracy) {
      componentNumber.number = accuracy.number;
      componentFormat.format = accuracy.format;
      }
  }
}
