#ifndef GOS_PID_TOOLKIT_CONSOLE_H_
#define GOS_PID_TOOLKIT_CONSOLE_H_

#include <boost/program_options.hpp>

namespace gos {
namespace pid {
namespace toolkit {
namespace console {

namespace go {
void start();
bool is();
}

namespace handler {
bool create();
}

namespace options {
namespace custom {
void add(::boost::program_options::options_description& description);
} // namespace custom
namespace general {
::boost::program_options::options_description& create();
} // namespace general
namespace reporting {
::boost::program_options::options_description& create();
}
namespace communication {
::boost::program_options::options_description& create();
} // namespace communication
namespace timer {
::boost::program_options::options_description& create(const int& definterval);
} // namespace timer
namespace cli {
void create(::boost::program_options::options_description& description);
} // namespace cli
namespace round {
namespace first {
::boost::program_options::variables_map& parse(
  ::boost::program_options::options_description& description,
  int argc,
  char* argv[]);
int handle(
  ::boost::program_options::options_description& description,
  const char* name,
  const char* version);
} // namespace first
namespace second {
::boost::program_options::options_description& parse(int& result);
} // namespace second
} // namespace round
} // namespace options

bool interval(bool& localgo);
void shutdown();

}
}
}
}

#endif
