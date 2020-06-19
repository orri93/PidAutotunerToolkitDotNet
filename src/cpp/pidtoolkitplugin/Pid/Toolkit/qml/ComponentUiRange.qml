import QtQuick 2.14
import Pid.Toolkit 1.0

ComponentUiRangeForm {

  property var range: null

  property bool fromEnabled: true
  property bool toEnabled: true


  rangeFromField.enabled: fromEnabled
  rangeToField.enabled: toEnabled

  onRangeChanged: {
    if(range) {
      rangeFromField.text = range.from;
      rangeToField.text = range.to;
    }
  }

  onFromEnabledChanged: {
    rangeFromField.enabled = fromEnabled;
  }

  onToEnabledChanged: {
    rangeToField.enabled = toEnabled;
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
