import QtQuick 2.14

ComponentUiFormatForm {

  property var format: null

  onFormatChanged: {
    if(format) {
      precision = format.precision;
    }
  }

  onPrecisionChanged: {
    if(format) {
      format.precision = precision;
    }
  }

}
