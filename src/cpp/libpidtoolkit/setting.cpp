#include <sstream>
#include <iostream>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#ifdef GOS_NOT_YET_NEEDED
#include <modbus.h>
#endif

#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/exception.h>
#include <gos/pid/toolkit/default.h>
#include <gos/pid/toolkit/types.h>
#include <gos/pid/toolkit/text.h>

#ifdef NOV_USE_BOOST_MAKE_UNIQUE
namespace mu = ::boost;
#else
namespace mu = ::std;
#endif

namespace gpt = ::gos::pid::toolkit;
namespace gptd = ::gos::pid::toolkit::defval;
namespace gptt = ::gos::pid::toolkit::text;

namespace gpttr = ::gos::pid::toolkit::type::reporting;

namespace gptdr = ::gos::pid::toolkit::defval::reporting;

namespace gos {
namespace pid {
namespace toolkit {
namespace setting {

namespace reporting {
gpttr::level verbosity = gptdr::Verbosity;
namespace logging {
gpttr::logging::level level = gptdr::logging::Level;
std::string format = gptdr::logging::Format;
namespace file {
std::string path = gptdr::logging::file::Path;
std::string pattern = gptdr::logging::file::Pattern;
namespace rotation {
size_t size = gptdr::logging::file::rotation::Size;
} // namespace rotation
} // namespace file
} // namespace logging
namespace repeate {
int silence = gptdr::repeate::Silence;
std::chrono::milliseconds Between() {
  return std::chrono::minutes(silence);
}
} // namespace repeate
} // namespace reporting

namespace communication {
namespace serial {
std::string port = gptd::communication::serial::Port;
int baud = gptd::communication::serial::Baud;
} // namespace serial
#ifdef GOS_PID_TOOLKIT_MQTT
namespace mqtt {
/* MQTT options */
int version = gptd::communication::mqtt::Version;
namespace topic {
std::string prefix = gptd::communication::mqtt::topic::Prefix;
} // namespace topic
namespace client {
std::string id = gptd::communication::mqtt::client::Id;
} // namespace client
int qos = gptd::communication::mqtt::Qos;
int retained = gptd::communication::mqtt::Retained;
//std::string username = nullptr;
//std::string password = nullptr;
std::string host = gptd::communication::mqtt::Host;
int port = gptd::communication::mqtt::Port;
//std::string connection;
int keepalive = gptd::communication::mqtt::Keepalive;
namespace connection {
int timeout = gptd::communication::mqtt::connection::Timeout;
}
namespace tls {
/* TLS options */
//int insecure = gptd::communication::mqtt::tls::Insecure;
//std::string capath;
//std::string cert;
//std::string cafile;
//std::string key;
//std::string keypass;
//std::string ciphers;
//std::string psk_identity;
//std::string psk;
} // namespace tls
} // namespace mqtt
#endif
} // namespace communication

namespace slave {
int id = gpt::defval::slave::Id;
} // namespace slave

namespace timing {
namespace interval {
namespace milliseconds {
int loop = gpt::defval::timing::interval::milliseconds::Loop;
} // namespace milliseconds
std::chrono::milliseconds duration() {
  return std::chrono::milliseconds(gpt::setting::timing::interval::milliseconds::loop);
}
} // namespace interval
} // namespace timing

void create() {
}

bool issilent() { return reporting::verbosity == gpttr::level::silent; }
bool isnormal() { return reporting::verbosity != gpttr::level::silent; }
bool isverbose() { return reporting::verbosity == gpttr::level::verbose; }

namespace configuration {
namespace file {
namespace details {
typedef std::unique_ptr<std::ifstream> FileStreamPointer;
static std::string last_error_;
static std::string configuration_file_name_;
static FileStreamPointer configuration_stream_;
static bool is_configurateion_file_valid_;
bool check(std::string& filename, const char* name) {
  ::boost::algorithm::trim(filename);
  std::stringstream errstrm;
  if (filename.size() > 0) {
    if (::boost::filesystem::exists(filename)) {
      return true;
    } else {
      errstrm << "The specified " << name << " file '" << filename
        << "' doesn't exist" << std::ends;
    }
  } else {
    errstrm << "The specified " << name
      << " file name is not valid" << std::ends;
  }
  details::last_error_ = errstrm.str();
  return false;
}
} // namespace details

bool apply(const std::string& configurationfilename) {
  details::configuration_file_name_ = configurationfilename;
  std::stringstream errstrm;
  if (details::check(details::configuration_file_name_, gptt::Configuration)) {
    details::configuration_stream_ =
      mu::make_unique<std::ifstream>(details::configuration_file_name_);
    if (details::configuration_stream_) {
      if (details::configuration_stream_->is_open()) {
        details::is_configurateion_file_valid_ = true;
        return true;
      } else {
        errstrm << "The specified configuration file '"
          << details::configuration_file_name_
          << "' is not opened" << std::ends;
      }
    } else {
      errstrm << "Failed to open the specified configuration file '"
        << details::configuration_file_name_ << "'" << std::ends;
    }
    details::last_error_ = errstrm.str();
  }
  return false;
}

std::string configurationfilename() {
  return details::configuration_file_name_;
}

std::string& lasterrortext() {
  return details::last_error_;
}

std::ifstream& stream() {
  if (details::configuration_stream_) {
    return *(details::configuration_stream_);
  } else {
    throw gpt::exception(
      "Configuration file stream is undefined");
  }
}

bool iswithfile() {
  return details::is_configurateion_file_valid_;
}

void close() {
  if (details::configuration_stream_) {
    details::configuration_stream_->close();
  }
}

} // namespace file
} // namespace configuration

} // namespace setting
} // namespace toolkit
} // namespace pid 
} // namespace gos
