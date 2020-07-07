#ifndef GOS_PID_TOOLKIT_SERVICE_OPTIONS_H_
#define GOS_PID_TOOLKIT_SERVICE_OPTIONS_H_

#include <MQTTClient.h>

#define GOS_PID_TOOLKIT_SERVICE_MQTT_INITIALIZER MQTTClient_connectOptions_initializer

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace options {
void create();
MQTTClient_connectOptions& get();
}
}
}
}
}

#endif
