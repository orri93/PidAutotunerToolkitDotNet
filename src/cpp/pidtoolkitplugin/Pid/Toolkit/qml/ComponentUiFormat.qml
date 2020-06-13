import QtQuick 2.14

ComponentUiFormatForm {

  property var format: null

  onFormatChanged: {
    if(format) {
      precision = format.precision;
      formatConnections.target = format;
      formatConnections.enabled = true;
    }
  }

  onPrecisionChanged: {
    if(format) {
      format.precision = precision;
    }
  }

  Connections {
    id: formatConnections
    enabled: false
    onPrecisionChanged: {
      precision = format.precision;
    }
  }


}
