import QtQuick 2.14
import Pid.Toolkit 1.0

ComponentUiRangeForm {

  property var range: null

  onRangeChanged: {
    if(range) {
      rangeFromField.text = range.from;
      rangeToField.text = range.to;
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
}
