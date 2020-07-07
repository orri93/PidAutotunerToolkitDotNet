#include <cstdlib>

#include <iostream>
#include <vector>
#include <atomic>

#ifdef WIN32
#include <Windows.h>
#else
#include <signal.h>
#include <unistd.h>
#endif

#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/options.h>
#include <gos/pid/toolkit/console.h>

namespace po = ::boost::program_options;

namespace gp = ::gos::pid;
namespace gpts = ::gos::pid::toolkit::setting;
namespace gpto = ::gos::pid::toolkit::options;
namespace gptc = ::gos::pid::toolkit::console;

namespace gos {
namespace pid {
namespace toolkit {
namespace console {

namespace go {
std::atomic_bool _instance;
void start() {
  _instance.store(true);
}
bool is() {
  return _instance.load();
}
}

namespace handler {
#if defined(_WIN32)
static DWORD _wait = 0;
static HANDLE _handle = NULL;
/*
 * See Handling Ctrl+C in Windows Console Application
 * https://asawicki.info/news_1465_handling_ctrlc_in_windows_console_application
 *
 */
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType);
#else
struct sigaction _signal_handling;
static void console_handler(int s);
#endif

bool create() {
#if defined(_WIN32)
  return ::SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
#else
  _signal_handling.sa_handler = console_handler;
  sigemptyset(&_signal_handling.sa_mask);
  _signal_handling.sa_flags = 0;

  sigaction(SIGINT, &_signal_handling, NULL);
  return true;
#endif
}
}


namespace handler {
#if defined(_WIN32)
BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType) {
  if (gpts::isverbose()) {
    std::cerr << "Stopping from console control handler" << std::endl;
  }
  go::_instance.store(false);
  if (_handle) {
    SetEvent(_handle);
  }
  return TRUE;
}
#else
void console_handler(int s) {
  if (gpts::isverbose()) {
    std::cerr << "Stopping from console control handler" << std::endl;
  }
  go::_instance.store(false);
}
#endif
}

namespace options {
static po::variables_map _varmap;
namespace custom {
typedef std::vector<po::options_description*> Registry;
Registry _registry;
void add(po::options_description& description) {
  _registry.push_back(&description);
}
} // namespace custom
namespace general {
static po::options_description _description(gpto::general::Name);
po::options_description& create() {
  gpto::general::create(_description);
  return _description;
}
} // namespace general
namespace reporting {
static po::options_description _description(gpto::reporting::Name);
po::options_description& create() {
  gpto::reporting::create(_description);
  return _description;
}
} // namespace reporting
namespace communication {
static po::options_description _description(gpto::communication::Name);
po::options_description& create() {
  gpto::communication::create(_description);
  return _description;
}
} // namespace communication
namespace timer {
static po::options_description _description(gpto::timer::Name);
po::options_description& create(const int& definterval) {
  gpto::timer::create(_description, definterval);
  return _description;
}
} // namespace timer
namespace cli {
void create(po::options_description& description) {
  description
    .add(general::_description)
    .add(reporting::_description)
    .add(communication::_description)
    .add(timer::_description);
  for (po::options_description* item : custom::_registry) {
    description.add(*item);
  }
}
} // namespace cli
namespace round {
namespace first {
po::variables_map& parse(
  po::options_description& description,
  int argc,
  char* argv[]) {
  /* First round with CLI parser only */
  po::command_line_parser cmdlinparser(argc, argv);
  po::parsed_options parseopt = cmdlinparser.options(description)
    .style(po::command_line_style::default_style).run();
  po::store(parseopt, _varmap);
  return _varmap;
}
int handle(
  po::options_description& description,
  const char* name,
  const char* version) {
  if (gpto::handling::help(description, _varmap)) {
    return GOS_PO_EXIT_HELP;
  }

  if (gpto::handling::version(_varmap, name, version)) {
    return GOS_PO_EXIT_VERSION;
  }

  gpto::handling::verbosity(_varmap);

  return EXIT_SUCCESS;
}
} // namespace first
namespace second {
static po::options_description _description;
po::options_description& parse(int& result) {
  /* second round */
  po::notify(_varmap);

  /* Create the configuration file options description */
  _description
    .add(reporting::_description)
    .add(communication::_description)
    .add(timer::_description);
  for (po::options_description* item : custom::_registry) {
    _description.add(*item);
  }

  result = gpto::handling::file(_description, _varmap);

  return _description;
}
} // namespace second
} // namespace round
} // namespace options

bool interval(bool& localgo) {
  if (localgo = gptc::go::_instance.load()) {
#if defined(_WIN32)
    if (handler::_handle) {
      CloseHandle(handler::_handle);
    }
    handler::_handle = CreateEvent(
      NULL,               // Default security attributes
      TRUE,               // Manual-reset event
      FALSE,              // Initial state is non-signaled
      NULL                // Object name
    );
    if (handler::_handle) {
      handler::_wait = WaitForSingleObject(
        handler::_handle,
        gpts::timing::interval::milliseconds::loop);
      switch (handler::_wait) {
      case WAIT_OBJECT_0:
      case WAIT_TIMEOUT:
        return true;
      case WAIT_ABANDONED:
      case WAIT_FAILED:
      default:
        std::cerr << "Waiting for the go lock failed" << std::endl;
        return false;
      }
    } else {
      std::cerr << "Failed to create loop wait event" << std::endl;
      return false;
    }
#else
    std::this_thread::sleep_for(gpts::timing::interval::duration());
#endif
  }
  return true;
}

void shutdown() {
  if (handler::_handle) {
    CloseHandle(handler::_handle);
  }
}

}
}
}
}
