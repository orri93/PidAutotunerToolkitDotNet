#ifndef GOS_PID_TOOLKIT_DEFAULT_H_
#define GOS_PID_TOOLKIT_DEFAULT_H_

#include <string>

#include <gos/pid/toolkit/types.h>

#ifndef DEFAULT_SERIAL_PORT
#ifdef WIN32
#define DEFAULT_SERIAL_PORT "COM32"
#else
#define DEFAULT_SERIAL_PORT "/dev/ttyS0"
#endif
#endif
#ifndef DEFAULT_BAUD
#define DEFAULT_BAUD 9600
#endif

#ifdef GOS_PID_TOOLKIT_MQTT
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_TOPIC_PREFIX "pidtoolkit"
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_CLIENT_ID "pidtoolkit"
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_HOST "localhost"
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_PORT 1883
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_QOS 1
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_KEEP_ALIVE 10
#define GOS_PID_TOOLKIT_DEFAULT_MQTT_TIMEOUT 10000
#endif

#define GOS_PID_TOOLKIT_DEFAULT_LOG_FORMAT "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%"
#define GOS_PID_TOOLKIT_DEFAULT_LOG_PATH ""
#define GOS_PID_TOOLKIT_DEFAULT_LOG_PATTERN "%Y%m%d%H%M%S.log"
#define GOS_PID_TOOLKIT_DEFAULT_LOG_SIZE 5 * 1024 * 1024 /* 5 MB */

#define GOS_PID_TOOLKIT_DEFAULT_REPORTING_REPEATE_SILENCE 5 /* 5 minutes */

namespace gos {
namespace pid {
namespace toolkit {
namespace defval {

namespace reporting {
extern const ::gos::pid::toolkit::type::reporting::level Verbosity;
namespace logging {
extern const ::gos::pid::toolkit::type::reporting::logging::level Level;
extern const std::string Format;
namespace file {
extern const std::string Path;
extern const std::string Pattern;
namespace rotation {
extern const size_t Size;
} // namespace rotation
} // namespace file
} // namespace logging
namespace repeate {
extern const int Silence;
} // namespace repeate
} // namespace reporting

namespace communication {
namespace serial {
extern const char* Port;
extern const int Baud;
} // namespace serial
#ifdef GOS_PID_TOOLKIT_MQTT
namespace mqtt {
/* MQTT options */
extern const int Version;
namespace topic {
extern const char* Prefix;
} // namespace topic
namespace client {
extern const char* Id;
} // namespace client
extern const int Qos;
extern const int Retained;
//  extern const char* username;
//  extern const char* password;
extern const char* Host;
extern const int Port;
//  extern const char* connection;
extern const int Keepalive;
namespace connection {
extern const int Timeout;
}
namespace tls {
/* TLS options */
//extern const int Insecure;
//  extern const char* capath;
//  extern const char* cert;
//  extern const char* cafile;
//  extern const char* key;
//  extern const char* keypass;
//  extern const char* ciphers;
//  extern const char* psk_identity;
//  extern const char* psk;
} // namespace tls
} // namespace mqtt
#endif
} // namespace communication

namespace slave {
extern const int Id;
} // namespace slave

namespace timing {
namespace interval {
namespace milliseconds {
extern const int Loop;
} // namespace milliseconds
} // namespace interval
} // namespace timing

} // namespace default
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
