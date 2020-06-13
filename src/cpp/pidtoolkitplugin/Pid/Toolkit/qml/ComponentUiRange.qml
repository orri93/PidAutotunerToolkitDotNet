import QtQuick 2.14
import Pid.Toolkit 1.0

ComponentUiRangeForm {

  property var range: null

  onRangeChanged: {
    if(range) {
      rangeFromField.text = range.from;
      rangeToField.text = range.to;
      rangeFromConnections.target = range;
      rangeToConnections.target = range;
      rangeFromConnections.enabled = true;
      rangeToConnections.enabled = true;
    }
  }

  rangeFromField.onAccepted: {
    if(range) {
      range.from = rangeFromField.text;
    }
  }

  rangeToField.onAccepted: {
    if(range) {
      range.to = rangeToField.text;
    }
  }


  Connections {
    id: rangeFromConnections
    enabled: false
    onFromChanged: {
      rangeFromField.text = range.from;
    }
  }

  Connections {
    id: rangeToConnections
    enabled: false
    onToChanged: {
      rangeToField.text = range.to;
    }
  }
}
