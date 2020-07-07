#ifndef GOS_PID_TOOLKIT_TEXT_H_
#define GOS_PID_TOOLKIT_TEXT_H_

#include <string>
#include <vector>

#include <gos/pid/toolkit/types.h>

#define GOST_NUL ""

#define GOST_ADDRESS "address"
#define GOST_BAUD "baud"
#define GOST_CLIENT "client"
#define GOST_COMMUNICATION "communication"
#define GOST_CONFIG "config"
#define GOST_CONFIGURATION "configuration"
#define GOST_CONNECTION "connection"
#define GOST_DEBUG "debug"
#define GOST_FILE "file"
#define GOST_FLAG "flag"
#define GOST_FORMAT "format"
#define GOST_HELP "help"
#define GOST_HOST "host"
#define GOST_ID "id"
#define GOST_INTERVAL "interval"
#define GOST_IP "ip"
#define GOST_MAXIMUM "maximum"
#define GOST_MODBUS "modbus"
#define GOST_MQTT "mqtt"
#define GOST_LEVEL "level"
#define GOST_LISTEN "listen"
#define GOST_LOG "log"
#define GOST_LOGGING "logging"
#define GOST_LOOP "loop"
#define GOST_NOISE "noise"
#define GOST_PATH "path"
#define GOST_PATTERN "pattern"
#define GOST_PORT "port"
#define GOST_PREFIX "prefix"
#define GOST_QOS "qos"
#define GOST_QUIET "quiet"
#define GOST_RANDOM "random"
#define GOST_REPORTING "reporting"
#define GOST_ROTATION "rotation"
#define GOST_SERIAL "serial"
#define GOST_SILENT "silent"
#define GOST_SIZE "size"
#define GOST_SLAVE "slave"
#define GOST_TABLE "table"
#define GOST_TIMEOUT "timeout"
#define GOST_TOOL "tool"
#define GOST_TOPIC "topic"
#define GOST_USAGE "usage"
#define GOST_VALUE "value"
#define GOST_VERBOSE "verbose"
#define GOST_VERSION "version"
#define GOST_WAIT "wait"
#define GOST_WORK "work"

#define GOST_C_COMMUNICATION "Communication"
#define GOST_C_REPORTING "Reporting"
#define GOST_C_GENERAL "General"
#define GOST_C_TIMER "Timer"
#define GOST_C_TOOL "Tool"

#define GOST_OSC ","
#define GOST_DASH "-"

#define GOST_OS_1 "1"
#define GOST_OS_2 "2"
#define GOST_OS_3 "3"
#define GOST_OS_4 "4"

//#define GOST_OS_A "a"
#define GOST_OS_B "b"
#define GOST_OS_C "c"
#define GOST_OS_D "d"
#define GOST_OS_F "f"
#define GOST_OS_H "h"
#define GOST_OS_I "i"
#define GOST_OS_L "l"
//#define GOST_OS_N "n"
//#define GOST_OS_M "m"
#define GOST_OS_P "p"
//#define GOST_OS_R "r"
#define GOST_OS_T "t"
#define GOST_OS_V "v"

#define GOST_C_OS_H "H"
#define GOST_C_OS_P "P"


/* Option */
/* General */
#define GOST_OS_OPT_CONFIGURATION_FILE GOST_CONFIGURATION GOST_DASH GOST_FILE
#define GOST_OS_OPT_CONFIG GOST_CONFIG
#define GOST_OS_OPT_FILE GOST_FILE
#define GOST_OS_OPT_HELP GOST_HELP
#define GOST_OS_OPT_QUIET GOST_QUIET
#define GOST_OS_OPT_SILENT GOST_SILENT
#define GOST_OS_OPT_VERSION GOST_VERSION
#define GOST_OS_OPT_VERBOSE GOST_VERBOSE

/* Reporting */
#define GOST_OS_OPT_LOGGING_LEVEL GOST_LOGGING GOST_DASH GOST_LEVEL
#define GOST_OS_OPT_LOGGING_FORMAT GOST_LOGGING GOST_DASH GOST_FORMAT
#define GOST_OS_OPT_LOGGING_PATH GOST_LOGGING GOST_DASH GOST_PATH
#define GOST_OS_OPT_LOGGING_PATTERN GOST_LOGGING GOST_DASH GOST_PATTERN
#define GOST_OS_OPT_LOGGING_ROTATION_SIZE GOST_LOGGING GOST_DASH GOST_ROTATION GOST_DASH GOST_SIZE

/* Communication */
/* Modbus */
#define GOST_OS_OPT_MODBUS_SLAVE_ID GOST_MODBUS GOST_DASH GOST_SLAVE GOST_DASH GOST_ID
#define GOST_OS_OPT_MODBUS_SERIAL_PORT GOST_MODBUS GOST_DASH GOST_SERIAL GOST_DASH GOST_PORT
#define GOST_OS_OPT_MODBUS_SERIAL_BAUD GOST_MODBUS GOST_DASH GOST_SERIAL GOST_DASH GOST_BAUD
/* MQTT */
#define GOST_OS_OPT_MQTT_HOST GOST_MQTT GOST_DASH GOST_HOST
#define GOST_OS_OPT_MQTT_PORT GOST_MQTT GOST_DASH GOST_PORT
#define GOST_OS_OPT_MQTT_TOPIC_PREFIX GOST_MQTT GOST_DASH GOST_TOPIC GOST_DASH GOST_PREFIX
#define GOST_OS_OPT_MQTT_CLIENT_ID GOST_MQTT GOST_DASH GOST_CLIENT GOST_DASH GOST_ID
#define GOST_OS_OPT_MQTT_QOS GOST_MQTT GOST_DASH GOST_QOS
#define GOST_OS_OPT_MQTT_TIMEOUT GOST_MQTT GOST_DASH GOST_TIMEOUT


/* Timing*/
#define GOST_OS_OPT_INTERVAL GOST_INTERVAL


/* Composite */
/* General */
#define /* -c */ GOST_OS_OCM_CONFIG GOST_OS_OPT_CONFIG GOST_OSC GOST_OS_C
#define /* -f */ GOST_OS_OCM_FILE GOST_OS_OPT_FILE GOST_OSC GOST_OS_F
#define /* -h */ GOST_OS_OCM_HELP GOST_OS_OPT_HELP GOST_OSC GOST_OS_H
#define /* -v */ GOST_OS_OCM_VERSION GOST_OS_OPT_VERSION GOST_OSC GOST_OS_V;

/* Reporting */
#define /* -l */ GOST_OS_OCM_LOGGING_LEVEL GOST_OS_OPT_LOGGING_LEVEL GOST_OSC GOST_OS_L;

/* Communication */
/* Modbus */
#define /* -i */ GOST_OS_OCM_MODBUS_SLAVE_ID GOST_OS_OPT_MODBUS_SLAVE_ID GOST_OSC GOST_OS_I
#define /* -p */ GOST_OS_OCM_MODBUS_SERIAL_PORT GOST_OS_OPT_MODBUS_SERIAL_PORT GOST_OSC GOST_OS_P
#define /* -b */ GOST_OS_OCM_MODBUS_SERIAL_BAUD GOST_OS_OPT_MODBUS_SERIAL_BAUD GOST_OSC GOST_OS_B
/* MQTT */
#define /* -H */ GOST_OS_OCM_MQTT_HOST GOST_OS_OPT_MQTT_HOST GOST_OSC GOST_C_OS_H
#define /* -P */ GOST_OS_OCM_MQTT_PORT GOST_OS_OPT_MQTT_PORT GOST_OSC GOST_C_OS_P
#define /* -t */ GOST_OS_OCM_MQTT_TIMEOUT GOST_OS_OPT_MQTT_TIMEOUT GOST_OSC GOST_OS_T


/* Timing*/


namespace gos {
namespace pid {
namespace toolkit {
namespace text {

/* lower: lower case, first: first letter uppercase, every: first letter of ever work is uppercase, all: all is uppercase*/
enum class format { lower, first, /* every, */ all };

typedef std::vector<format> FormatVector;

extern const FormatVector All;

std::string formating(const std::string& text, const format& format);
namespace wide {
std::wstring formating(const std::wstring& text, const format& format);
}

namespace is {
bool equal(const std::string& a, const std::string& b);
bool equal(const std::string& a, const std::string& b, const FormatVector& formats);
namespace wide {
bool equal(const std::wstring& a, const std::wstring& b);
bool equal(const std::wstring& a, const std::wstring& b, const FormatVector& formats);
}
}

namespace to {
std::string text(const ::gos::pid::toolkit::type::reporting::logging::level& level);
namespace wide {
std::wstring text(const ::gos::pid::toolkit::type::reporting::logging::level& level);
}
}

extern const char* Address;
extern const char* Baud;
extern const char* Client;
extern const char* Communication;
extern const char* Config;
extern const char* Configuration;
extern const char* Connection;
extern const char* Debug;
extern const char* Flag;
extern const char* File;
extern const char* Format;
extern const char* Help;
extern const char* Host;
extern const char* Id;
extern const char* Interval;
extern const char* Ip;
extern const char* Level;
extern const char* Listen;
extern const char* Log;
extern const char* Logging;
extern const char* Loop;
extern const char* Noise;
extern const char* Maximum;
extern const char* Modbus;
extern const char* Mqtt;
extern const char* Qos;
extern const char* Quiet;
extern const char* Path;
extern const char* Pattern;
extern const char* Port;
extern const char* Prefix;
extern const char* Random;
extern const char* Reporting;
extern const char* Rotation;
extern const char* Serial;
extern const char* Silent;
extern const char* Size;
extern const char* Slave;
extern const char* Table;
extern const char* Timeout;
extern const char* Tool;
extern const char* Topic;
extern const char* Usage;
extern const char* Value;
extern const char* Verbose;
extern const char* Version;
extern const char* Wait;
extern const char* Work;

namespace capitalised {
namespace first {
extern const char* Communication;
extern const char* Reporting;
extern const char* General;
extern const char* Timer;
extern const char* Tool;
}
}

namespace option {

namespace general {
extern const char* Configuration;
extern const char* Config;
extern const char* File;
extern const char* Help;
extern const char* Quiet;
extern const char* Silent;
extern const char* Version;
extern const char* Verbose;
}

namespace reporting {
namespace logging {
extern const char* Level;
extern const char* Format;
namespace file {
extern const char* Path;
extern const char* Pattern;
namespace rotation {
extern const char* Size;
} // namespace rotation
} // namespace file
} // namespace logging
} // namespace reporting

namespace communication {
namespace modbus {
namespace slave {
extern const char* Id;
}
namespace serial {
extern const char* Port;
extern const char* Baud;
}
}
namespace mqtt {
namespace topic {
extern const char* Prefix;
} // namespace topic
namespace client {
extern const char* Id;
} // namespace client
extern const char* Qos;
extern const char* Host;
extern const char* Port;
namespace connection {
extern const char* Timeout;
}
}
}
namespace timing {
extern const char* Interval;
}

namespace composite {
namespace general {
extern const char* Config;
extern const char* Help;
extern const char* Version;
}
namespace reporting {
namespace logging {
extern const char* Level;
} // namespace logging
} // namespace reporting
namespace communication {
namespace modbus {
namespace slave {
extern const char* Id;
}
namespace serial {
extern const char* Port;
extern const char* Baud;
}
}
namespace mqtt {
extern const char* Host;
extern const char* Port;
namespace connection {
extern const char* Timeout;
}
}
}
namespace timing {
}
}

namespace description {
namespace general {
extern const char* Configuration;
extern const char* Config;
extern const char* Help;
extern const char* Quiet;
extern const char* Silent;
extern const char* Version;
extern const char* Verbose;
}
namespace reporting {
namespace logging {
extern const char* Level;
extern const char* Format;
namespace file {
extern const char* Path;
extern const char* Pattern;
namespace rotation {
extern const char* Size;
} // namespace rotation
} // namespace file
} // namespace logging
} // namespace reporting
namespace communication {
namespace modbus {
namespace slave {
extern const char* Id;
}
namespace serial {
extern const char* Port;
extern const char* Baud;
}
}
namespace mqtt {
extern const char* Host;
extern const char* Port;
namespace topic {
extern const char* Prefix;
} // namespace topic
namespace client {
extern const char* Id;
} // namespace client
extern const char* Qos;
namespace connection {
extern const char* Timeout;
}
}
}
namespace timing {
extern const char* Interval;
}
}
}

} // namespace text
} // namespace toolkit
} // namespace pid 
} // namespace gos

#endif
