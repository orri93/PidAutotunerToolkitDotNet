import QtQuick 2.14
import Pid.Toolkit 1.0

ConfigurationModbusForm {

  property var modbus: null

  onModbusChanged: {
    if(modbus) {
    }
  }
}
