#include <algorithm>

#include <gos/pid/toolkit/text.h>

namespace gpt = ::gos::pid::toolkit;
namespace gptt = ::gos::pid::toolkit::type;
namespace gpttr = ::gos::pid::toolkit::type::reporting;
namespace gpttrl = ::gos::pid::toolkit::type::reporting::logging;

namespace gos {
namespace pid {
namespace toolkit {
namespace text {

const FormatVector All({ format::lower, format::first, format::all });

const char* Address = GOST_ADDRESS;
const char* Client = GOST_CLIENT;
const char* Communication = GOST_COMMUNICATION;
const char* Config = GOST_CONFIG;
const char* Configuration = GOST_CONFIGURATION;
const char* Connection = GOST_CONNECTION;
const char* Debug = GOST_DEBUG;
const char* Flag = GOST_FILE;
const char* Format = GOST_FORMAT;
const char* Help = GOST_HELP;
const char* Host = GOST_HOST;
const char* Id = GOST_ID;
const char* Interval = GOST_INTERVAL;
const char* Ip = GOST_IP;
const char* Level = GOST_LEVEL;
const char* Listen = GOST_LISTEN;
const char* Log = GOST_LOG;
const char* Logging = GOST_LOGGING;
const char* Loop = GOST_LOOP;
const char* Noise = GOST_NOISE;
const char* Maximum = GOST_MAXIMUM;
const char* Modbus = GOST_MODBUS;
const char* Mqtt = GOST_MQTT;
const char* Qos = GOST_QOS;
const char* Quiet = GOST_QUIET;
const char* File = GOST_FILE;
const char* Path = GOST_PATH;
const char* Pattern = GOST_PATTERN;
const char* Port = GOST_PORT;
const char* Prefix = GOST_PREFIX;
const char* Random = GOST_RANDOM;
const char* Reporting = GOST_REPORTING;
const char* Rotation = GOST_ROTATION;
const char* Silent = GOST_SILENT;
const char* Size = GOST_SIZE;
const char* Slave = GOST_SLAVE;
const char* Table = GOST_TABLE;
const char* Timeout = GOST_TIMEOUT;
const char* Tool = GOST_TOOL;
const char* Topic = GOST_TOPIC;
const char* Usage = GOST_USAGE;
const char* Value = GOST_VALUE;
const char* Verbose = GOST_VERBOSE;
const char* Version = GOST_VERSION;
const char* Wait = GOST_WAIT;
const char* Work = GOST_WORK;

namespace capitalised {
namespace first {
const char* Communication = GOST_C_COMMUNICATION;
const char* Reporting = GOST_C_REPORTING;
const char* General = GOST_C_GENERAL;
const char* Timer = GOST_C_TIMER;
const char* Tool = GOST_C_TOOL;
}
}

namespace option {

namespace general {
const char* Configuration = GOST_OS_OPT_CONFIGURATION_FILE;
const char* Config = GOST_OS_OPT_CONFIG;
const char* File = GOST_OS_OPT_FILE;
const char* Help = GOST_OS_OPT_HELP;
const char* Quiet = GOST_OS_OPT_QUIET;
const char* Silent = GOST_OS_OPT_SILENT;
const char* Version = GOST_OS_OPT_VERSION;
const char* Verbose = GOST_OS_OPT_VERBOSE;
}
namespace reporting {
namespace logging {
const char* Level = GOST_OS_OPT_LOGGING_LEVEL;
const char* Format = GOST_OS_OPT_LOGGING_FORMAT;
namespace file {
const char* Path = GOST_OS_OPT_LOGGING_PATH;
const char* Pattern = GOST_OS_OPT_LOGGING_PATTERN;
namespace rotation {
const char* Size = GOST_OS_OPT_LOGGING_ROTATION_SIZE;
} // namespace rotation
} // namespace file
} // namespace logging
} // namespace reporting
namespace communication {
namespace modbus {
namespace slave {
const char* Id = GOST_OS_OPT_MODBUS_SLAVE_ID;
}
namespace serial {
const char* Port = GOST_OS_OPT_MODBUS_SERIAL_PORT;
const char* Baud = GOST_OS_OPT_MODBUS_SERIAL_BAUD;
}
}
namespace mqtt {
namespace topic {
const char* Prefix = GOST_OS_OPT_MQTT_TOPIC_PREFIX;
} // namespace topic
namespace client {
const char* Id = GOST_OS_OPT_MQTT_CLIENT_ID;
} // namespace client
const char* Qos = GOST_OS_OPT_MQTT_QOS;
const char* Host = GOST_OS_OPT_MQTT_HOST;
const char* Port = GOST_OS_OPT_MQTT_PORT;
namespace connection {
const char* Timeout = GOST_OS_OPT_MQTT_TIMEOUT;
}
}
}
namespace timing {
const char* Interval = GOST_OS_OPT_INTERVAL;
}

namespace composite {
namespace general {
const char* Config = GOST_OS_OCM_CONFIG;
const char* File = GOST_OS_OCM_FILE;
const char* Help = GOST_OS_OCM_HELP;
const char* Version = GOST_OS_OCM_VERSION;
}
namespace reporting {
namespace logging {
const char* Level = GOST_OS_OCM_LOGGING_LEVEL;
} // namespace logging
} // namespace reporting
namespace communication {
namespace modbus {
namespace slave {
const char* Id = GOST_OS_OCM_MODBUS_SLAVE_ID;
}
namespace serial {
const char* Port = GOST_OS_OCM_MODBUS_SERIAL_PORT;
const char* Baud = GOST_OS_OCM_MODBUS_SERIAL_BAUD;
}
}
namespace mqtt {
const char* Host = GOST_OS_OCM_MQTT_HOST;
const char* Port = GOST_OS_OCM_MQTT_PORT;
namespace connection {
const char* Timeout = GOST_OS_OCM_MQTT_TIMEOUT;
}
}
}
namespace timing {
}
}

namespace description {
namespace general {
const char* Config = "configuration file";
const char* Configuration = Config;
const char* Help = "produce help message";
const char* Quiet = Silent;
const char* Silent = "inhibit all outputs besides the requested";
const char* Version = "print version string";
const char* Verbose = "print more information about the progress";
}
namespace reporting {
namespace logging {
const char* Level = "log level (debug, info, warning, critical)";
const char* Format = "log format";
namespace file {
const char* Path = "log file path";
const char* Pattern = "log file name pattern";
namespace rotation {
const char* Size = "log file rotation size";
} // namespace rotation
} // namespace file
} // namespace logging
} // namespace reporting
namespace communication {
namespace modbus {
namespace slave {
const char* Id = "Modbus slave ID";
}
namespace serial {
const char* Port = "Modbus serial port";
const char* Baud = "Modbus serial baud";
}
}
namespace mqtt {
namespace topic {
const char* Prefix = "MQTT topic prefix";
} // namespace topic
namespace client {
const char* Id = "MQTT client ID";
} // namespace client
const char* Qos = "MQTT QOS";
const char* Host = "MQTT host";
const char* Port = "MQTT port";
namespace connection {
const char* Timeout = "MQTT connection timeout";
}
}
}
namespace timing {
const char* Interval = "cycle interval";
}
}
}

std::string formating(const std::string& text, const format& format) {
  if (!text.empty()) {
    std::string result(text);
    switch (format) {
    case format::lower:
      std::transform(result.begin(), result.end(), result.begin(), ::tolower);
      return result;
    case format::all:
      std::transform(result.begin(), result.end(), result.begin(), ::toupper);
      return result;
    case format::first:
      std::transform(result.begin(), result.begin() + 1, result.begin(), ::toupper);
      return result;
    default:
      return "Unknown format in formating";
    }
  } else {
    return text;
  }
}
namespace wide {
std::wstring formating(const std::wstring& text, const format& format) {
  if (!text.empty()) {
    std::wstring result(text);
    switch (format) {
    case format::lower:
      std::transform(result.begin(), result.end(), result.begin(), ::tolower);
      return result;
    case format::all:
      std::transform(result.begin(), result.end(), result.begin(), ::toupper);
      return result;
    case format::first:
      std::transform(result.begin(), result.begin() + 1, result.begin(), ::toupper);
      return result;
    default:
      return L"Unknown format in formating";
    }
  } else {
    return text;
  }
}
}

namespace is {
bool equal(const std::string& a, const std::string& b) {
  return equal(a, b, All);
}
bool equal(
  const std::string& a,
  const std::string& b,
  const FormatVector& formats) {
  if (a.compare(b) == 0) {
    return true;
  }
  std::string fa, fb;
  for (const format& f : formats) {
    fa = formating(a, f);
    fb = formating(b, f);
    if (fa.compare(fb) == 0) {
      return true;
    }
  }
  return false;
}
namespace wide {
bool equal(const std::wstring& a, const std::wstring& b) {
  return equal(a, b, All);
}
bool equal(
  const std::wstring& a,
  const std::wstring& b,
  const FormatVector& formats) {
  if (a.compare(b) == 0) {
    return true;
  }
  std::wstring fa, fb;
  for (const format& f : formats) {
    fa = gpt::text::wide::formating(a, f);
    fb = gpt::text::wide::formating(b, f);
    if (fa.compare(fb) == 0) {
      return true;
    }
  }
  return false;
}
}
}

namespace to {
std::string text(const gpttrl::level& level) {
  switch (level) {
  case gpttrl::level::none:
    return "none";
  case gpttrl::level::debug:
    return "debug";
  case gpttrl::level::info:
    return "info";
  case gpttrl::level::warning:
    return "warning";
  case gpttrl::level::critical:
    return "critical";
  default:
    return "unknown";
  }
}
namespace wide {
std::wstring text(const gpttrl::level& level) {
  switch (level) {
  case gpttrl::level::none:
    return L"none";
  case gpttrl::level::debug:
    return L"debug";
  case gpttrl::level::info:
    return L"info";
  case gpttrl::level::warning:
    return L"warning";
  case gpttrl::level::critical:
    return L"critical";
  default:
    return L"unknown";
  }
}
}
}

}
}
}
}
