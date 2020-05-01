#ifndef GOS_PID_TOOLKIT_SETTINGS_H_
#define GOS_PID_TOOLKIT_SETTINGS_H_

#include <string>

#include <boost/program_options.hpp>

#include <gos/pid/toolkit/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace setting {

extern ::gos::pid::toolkit::type::level verbosity;

namespace communication {
namespace serial {
extern std::string port;
extern int baud;
} // namespace serial
} // namespace communication

namespace slave {
extern int id;
} // namespace slave

namespace timing {
namespace interval {
namespace milliseconds {
extern int loop;
} // namespace milliseconds
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
} // namespace file
} // namespace configuration

} // namespace setting
} // namespace tools
} // namespace arduino 
} // namespace gos

#endif
