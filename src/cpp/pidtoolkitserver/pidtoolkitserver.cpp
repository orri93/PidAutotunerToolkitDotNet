#include <cstdlib>

#include <fstream>
#include <iostream>
#include <thread>

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include <signal.h>
#include <unistd.h>
#endif

#include <gos/pid/toolkit/text.h>
#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/options.h>
#include <gos/pid/toolkit/console.h>
#include <gos/pid/toolkit/version.h>
#include <gos/pid/toolkit/reporting.h>
#include <gos/pid/toolkit/exception.h>

#include <gos/pid/toolkit/service/service.h>

#define GOS_ARDUINO_TOOLS_SERVER_NAME "pidtoolkitservice"
#define GOS_ARDUINO_TOOLS_SERVER_DEFAULT_INTERVAL 1000

namespace po = ::boost::program_options;

namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;
namespace gpts = ::gos::pid::toolkit::setting;
namespace gpto = ::gos::pid::toolkit::options;
namespace gptc = ::gos::pid::toolkit::console;
namespace gptr = ::gos::pid::toolkit::reporting;

int main(int argc, char* argv[]) {

  gptc::go::start();

  int round = 0;
  int retval = EXIT_SUCCESS;

  if (!gptc::handler::create()) {
    return EXIT_FAILURE;
  }
  gpts::create();

  try {
    po::options_description& optdescript = gptc::options::general::create();
    po::options_description& repdescript = gptc::options::reporting::create();
    po::options_description& communicationdescript = gptc::options::communication::create();
    po::options_description& timer = gptc::options::timer::create(GOS_ARDUINO_TOOLS_SERVER_DEFAULT_INTERVAL);

    po::options_description clioptions(
      GOS_ARDUINO_TOOLS_SERVER_NAME " " GOST_USAGE, GOS_PO_LINE_LENGTH);
    gptc::options::cli::create(clioptions);

    po::variables_map& varmap = gptc::options::round::first::parse(clioptions, argc, argv);

    if (retval = gptc::options::round::first::handle(
      clioptions,
      GOS_ARDUINO_TOOLS_SERVER_NAME,
      GPT_VERSION_STRING)) {
      return retval;
    }

    po::options_description& configfdesc = gptc::options::round::second::parse(retval);
    if (retval) {
      return retval;
    }

    gpto::handling::communication(varmap);
#ifdef GOS_NOT_YET_USED
    gato::handling::tool(varmap);
#endif

    gptr::initialize(GOS_ARDUINO_TOOLS_SERVER_NAME);
    gptr::welcome();

    if (gpt::service::create()) {
      if (gpt::service::start()) {
        gptr::information::report("Service MQTT has been started");
      } else {
        goto gos_arduino_tools_pid_service_exit_failure;
      }
    } else {
      goto gos_arduino_tools_pid_service_exit_failure;
    }

    gp::toolkit::type::Duration duration;
    std::chrono::milliseconds dms;
    gp::toolkit::type::Time time, starttime =
      gp::toolkit::type::Clock::now();
    bool localgo = gptc::go::is();
    while (localgo) {
      time = gp::toolkit::type::Clock::now();

      duration = time - starttime;
      dms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

      if (!gpt::service::cycle()) {
        goto gos_arduino_tools_pid_service_exit_failure;
      }

      if (!gptc::interval(localgo)) {
        goto gos_arduino_tools_pid_service_exit_failure;
      }
    }
  } catch (::gos::pid::toolkit::exception& er) {
    std::cerr << "Tool exception: "
      << er.what() << std::endl;
    return EXIT_FAILURE;
  } catch (po::error& er) {
    std::cerr << "Boost parsing program option exception: "
      << er.what() << std::endl;
    return EXIT_FAILURE;
  } catch (std::exception& ex) {
    std::cerr << "General parsing option exception: "
      << ex.what() << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "General parsing option exception" << std::endl;
    return EXIT_FAILURE;
  }

  goto gos_arduino_tools_pid_service_exit;

gos_arduino_tools_pid_service_exit_failure:
  retval = EXIT_FAILURE;

gos_arduino_tools_pid_service_exit:
  gpt::service::shutdown(); /* Shutdown service*/
  gptc::shutdown();         /* Shutdown console */
  gptr::shutdown();         /* Shutdown reporting */
  //gpam::master::disconnect();
  //gpam::master::shutdown();
  return retval;
}
