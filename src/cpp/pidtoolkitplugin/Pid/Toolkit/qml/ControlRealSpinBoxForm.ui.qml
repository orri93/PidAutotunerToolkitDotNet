import QtQuick 2.4
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Pid.Toolkit 1.0

SpinBox {
  /*** type:int The precision of the real value */
  property int realPrecision: 3

  /*** type:real The minimum real value */
  property real realFrom: 0.0

  /*** type:real The v real value */
  property real realTo: 100.0

  /*** type:real The real value step size is based on the precision */
  property real realStepSize: 0.001

  /*** type:real The real multipler is internal property and is based on the precision */
  property real realMultiplier: 1000.0

  editable: true

  stepSize: realMultiplier * realStepSize
}

/*##^##
Designer {
    D{i:0;formeditorColor:"#4c4e50"}
}
##^##*/
