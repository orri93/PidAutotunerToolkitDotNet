import QtQuick 2.14
import Pid.Toolkit 1.0

ConfigurationControllerForm {

  property var orchestration: ptOrchestration
  property var settings: ptOrchestration.settings
  property var controller: ptOrchestration.settings.controller


  integralNumber.number: controller.integral
  temperatureNumber.number: controller.temperature;



}
