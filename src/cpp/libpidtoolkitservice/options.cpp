#include <gos/pid/toolkit/setting.h>

#include <gos/pid/toolkit/service/options.h>
#include <gos/pid/toolkit/reporting.h>

namespace gpt = ::gos::pid::toolkit;
namespace gpts = ::gos::pid::toolkit::setting;

namespace gptr = ::gos::pid::toolkit::reporting;

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace options {
static MQTTClient_connectOptions _options =
  GOS_PID_TOOLKIT_SERVICE_MQTT_INITIALIZER;

void create() {
  _options.MQTTVersion = gpts::communication::mqtt::version;
  _options.keepAliveInterval = gpts::communication::mqtt::keepalive;
  _options.connectTimeout = gpts::communication::mqtt::connection::timeout;
  gptr::information::report("Service options created");
}

MQTTClient_connectOptions& get() {
  return _options;
}

}
}
}
}
}