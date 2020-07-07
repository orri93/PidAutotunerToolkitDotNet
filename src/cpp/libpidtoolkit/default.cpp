/* To get rid of C4005 warning when modbus-tcp.h defines some error macros */

#include <gos/pid/toolkit/default.h>

#ifdef GOS_PID_TOOLKIT_MQTT
#include <MQTTClient.h>
#endif

namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;

namespace gpttr = ::gos::pid::toolkit::type::reporting;


namespace gos {
namespace pid {
namespace toolkit {
namespace defval {

namespace reporting {
const gpttr::level Verbosity = gpttr::level::normal;
namespace logging {
const gpttr::logging::level Level = gpttr::logging::level::none;
const std::string Format = GOS_PID_TOOLKIT_DEFAULT_LOG_FORMAT;
namespace file {
const std::string Path = GOS_PID_TOOLKIT_DEFAULT_LOG_PATH;
const std::string Pattern = GOS_PID_TOOLKIT_DEFAULT_LOG_PATTERN;
namespace rotation {
const size_t Size = GOS_PID_TOOLKIT_DEFAULT_LOG_SIZE;
} // namespace rotation
} // namespace file
} // namespace logging
namespace repeate {
const int Silence = GOS_PID_TOOLKIT_DEFAULT_REPORTING_REPEATE_SILENCE;
} // namespace repeate
} // namespace reporting

namespace communication {
namespace serial {
const char* Port = DEFAULT_SERIAL_PORT;
const int Baud = DEFAULT_BAUD;
} // namespace serial
#ifdef GOS_PID_TOOLKIT_MQTT
namespace mqtt {
/* MQTT options */
const int Version = MQTTVERSION_DEFAULT;
namespace topic {
const char* Prefix = GOS_PID_TOOLKIT_DEFAULT_MQTT_TOPIC_PREFIX;
} // namespace topic
namespace client {
const char* Id = GOS_PID_TOOLKIT_DEFAULT_MQTT_CLIENT_ID;
} // namespace client
const int Qos = GOS_PID_TOOLKIT_DEFAULT_MQTT_QOS;
const int Retained = 0;
//const char* Username = nullptr;
//const char* Password = nullptr;
const char* Host = GOS_PID_TOOLKIT_DEFAULT_MQTT_HOST;
const int Port = GOS_PID_TOOLKIT_DEFAULT_MQTT_PORT;
//const char* connection;
const int Keepalive = GOS_PID_TOOLKIT_DEFAULT_MQTT_KEEP_ALIVE;
namespace connection {
const int Timeout = GOS_PID_TOOLKIT_DEFAULT_MQTT_TIMEOUT;
}
namespace tls {
/* TLS options */
//const int Insecure = 0;
//const char* Capath;
//const char* Cert;
//const char* Cafile;
//const char* Key;
//const char* Keypass;
//const char* Ciphers;
//const char* Psk_identity;
//const char* Psk;
} // namespace tls
} // namespace mqtt
#endif
} // namespace communication

namespace slave {
const int Id = 1;
} // namespace slave

namespace timing {
namespace interval {
namespace milliseconds {
const int Loop = 0;
} // namespace milliseconds
} // namespace interval
} // namespace timing


} // namespace default
} // namespace toolkit
} // namespace pit
} // namespace gos
