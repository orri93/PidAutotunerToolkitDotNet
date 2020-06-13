import QtQuick 2.14

import Pid.Toolkit 1.0

ComponentUiAccuracyForm {

  property var accuracy: null

  onAccuracyChanged: {
    if(accuracy) {
      componentNumber.number = accuracy.number;
      componentFormat.format = accuracy.format;
      accuracyConnections.target = accuracy;
      formatConnections.target = accuracy;
      accuracyConnections.enabled = true;
      formatConnections.enabled = true;
    }
  }

  Connections {
    id: accuracyConnections
    enabled: false
    onNumberChanged: {
      componentNumber.number = accuracy.number;
    }
  }


  Connections {
    id: formatConnections
    enabled: false
    onFormatChanged: {
      componentFormat.format = accuracy.format;
    }
  }
}
