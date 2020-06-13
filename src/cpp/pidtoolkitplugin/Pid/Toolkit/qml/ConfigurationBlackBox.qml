import QtQuick 2.14
import Pid.Toolkit 1.0

ConfigurationBlackBoxForm {

  property var blackbox: null

  onBlackBoxChanged: {
    if(blackbox) {
    }
  }
}
