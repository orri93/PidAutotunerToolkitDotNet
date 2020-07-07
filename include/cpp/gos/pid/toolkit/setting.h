#ifndef GOS_PID_TOOLKIT_SETTINGS_H_
#define GOS_PID_TOOLKIT_SETTINGS_H_

#include <string>
#include <chrono>

//#include <boost/program_options.hpp>

#include <gos/pid/toolkit/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace setting {

namespace reporting {
extern ::gos::pid::toolkit::type::reporting::level verbosity;
namespace logging {
extern ::gos::pid::toolkit::type::reporting::logging::level level;
extern std::string format;
namespace file {
extern std::string path;
extern std::string pattern;
namespace rotation {
extern size_t size;
} // namespace rotation
} // namespace file
} // namespace logging
namespace repeate {
extern int silence;
std::chrono::milliseconds Between();
} // namespace repeate
} // namespace reporting

namespace communication {
namespace serial {
extern std::string port;
extern int baud;
} // namespace serial
#ifdef GOS_PID_TOOLKIT_MQTT
namespace mqtt {
/* MQTT options */
extern int version;
namespace topic {
extern std::string prefix;
} // namespace topic
namespace client {
extern std::string id;
} // namespace client
extern int qos;
extern int retained;
//  extern std::string username;
//  extern std::string password;
extern std::string host;
extern int port;
//  extern std::string connection;
extern int keepalive;
namespace connection {
extern int timeout;
}
namespace tls {
/* TLS options */
//extern int insecure;
//  extern std::string capath;
//  extern std::string cert;
//  extern std::string cafile;
//  extern std::string key;
//  extern std::string keypass;
//  extern std::string ciphers;
//  extern std::string psk_identity;
//  extern std::string psk;
} // namespace tls
} // namespace mqtt
#endif
} // namespace communication

namespace slave {
extern int id;
} // namespace slave

namespace timing {
namespace interval {
namespace milliseconds {
extern int loop;
} // namespace milliseconds
std::chrono::milliseconds duration();
} // namespace interval
} // namespace timing

void create();

bool issilent();
bool isnormal();
bool isverbose();

namespace configuration {
namespace file {
bool check(std::string& filename, const char* name);
bool apply(const std::string& configurationfilename);
std::string configurationfilename();
std::string& lasterrortext();
std::ifstream& stream();
bool iswithfile();
void close();
} // namespace file
} // namespace configuration

} // namespace setting
} // namespace tools
} // namespace arduino 
} // namespace gos

#endif
