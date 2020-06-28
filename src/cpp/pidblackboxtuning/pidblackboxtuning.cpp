#include <cstdlib>

#include <fstream>
#include <iostream>
#include <thread>
#include <atomic>

#ifdef WIN32
#include <WinSock2.h>
#include <Windows.h>
#else
#include <signal.h>
#include <unistd.h>
#endif

#include <modbus.h>

#include <gos/pid/toolkit/text.h>
#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/options.h>
#include <gos/pid/toolkit/exception.h>

#include <gos/pid/arduino/modbus/master.h>
#include <gos/pid/arduino/modbus/options.h>
#include <gos/pid/arduino/modbus/retry.h>

#include <gos/pid/tuning/setting.h>
#include <gos/pid/tuning/blackbox.h>
#include <gos/pid/tuning/options.h>
#include <gos/pid/tuning/output.h>

#define GOS_ARDUINO_TOOLS_MASTER_NAME "master"
#define GOS_ARDUINO_TOOLS_MASTER_DEFAULT_INTERVAL 1000

#define GOS_ARDT_MOD_TUNING "tuning"
#define GOS_ARDT_MOD_TUNING_MODE_BLACK_BOX "black"
#define GOS_ARDT_MOD_INTERNAL "internal"
#define GOS_ARDT_MOD_OUTPUT "output"
#define GOS_ARDT_MOD_OUTPUT_O "output,o"
#define GOS_ARDT_MOD_SEPARATOR "separator"

#define GOS_ARDT_DEFAULT_SEPARATOR ","

namespace po = ::boost::program_options;

namespace gp = ::gos::pid;
namespace gpts = ::gos::pid::toolkit::setting;
namespace gpto = ::gos::pid::toolkit::options;

namespace gpat = ::gos::pid::arduino::types;
namespace gpam = ::gos::pid::arduino::modbus;
namespace gpammr = ::gos::pid::arduino::modbus::master::retry;

namespace gpt = ::gos::pid::tuning;

static std::atomic_bool go;

#if defined(_WIN32)

static HANDLE handle = NULL;

/*
 * See Handling Ctrl+C in Windows Console Application
 * https://asawicki.info/news_1465_handling_ctrlc_in_windows_console_application
 *
 */
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType) {
  if (gpts::isverbose()) {
    std::cerr << "Stopping from console control handler" << std::endl;
  }
  go.store(false);
  if (handle) {
    SetEvent(handle);
  }
  return TRUE;
}
#else
static void console_handler(int s) {
  if (gpts::isverbose()) {
    std::cerr << "Stopping from console control handler" << std::endl;
  }
  go.store(false);
}
#endif

namespace output {
static std::string separator;
namespace file {
static std::string path;
}
namespace file {
namespace stream {
static gp::toolkit::type::OutputFileStreamPointer pointer;
}
}
}

namespace tune {
static gpt::types::TuningMode mode = gpt::types::TuningMode::undefined;
static gpt::types::Variables variables;
static gpt::types::Initialized initialized;
namespace black {
namespace box {
static gpt::black::box::Variables variables;
static gpt::types::EvaluationPointer evaluation;
}
}
}

namespace force {
static gpt::types::OptionalUnsigned final;
static gpt::types::OptionalUnsigned value;
}

namespace modbus {
static gpam::types::registry::Input input;
static gpam::types::registry::Holding holding;
}

namespace is {
static bool internal;
static bool successful;
}

int main(int argc, char* argv[]) {

  go.store(true);

  int round = 0;
  int retval = EXIT_SUCCESS;
  gpam::types::result result;

  GOS_PID_TUNING_BLACK_BOX_ELAPSED_TYPE elapsed;

#if defined(_WIN32)
  DWORD wait;
  ::SetConsoleCtrlHandler(console_ctrl_handler, TRUE);
#else
  struct sigaction signal_handling;

  signal_handling.sa_handler = console_handler;
  sigemptyset(&signal_handling.sa_mask);
  signal_handling.sa_flags = 0;

  sigaction(SIGINT, &signal_handling, NULL);

#endif

  gpts::create();

  try {
    po::options_description optdescript(gpto::general::Name);
    gpto::general::create(optdescript);

    po::options_description communicationdescript(gpto::communication::Name);
    gpto::communication::create(communicationdescript);

    po::options_description timer(gpto::timer::Name);
    gpto::timer::create(timer, GOS_ARDUINO_TOOLS_MASTER_DEFAULT_INTERVAL);

    po::options_description custom(GOS_ARDUINO_TOOLS_MASTER_NAME);
    gpam::options::create(custom);
    gpt::options::create(custom);
    custom.add_options()
      (GOS_ARDT_MOD_TUNING, po::value<std::string>(),
        "tuning method (black is the only one currently supported)")
      (GOS_ARDT_MOD_OUTPUT_O, po::value<std::string>(),
        "output to file instead of standard out")
      (GOS_ARDT_MOD_SEPARATOR, po::value(&(output::separator))
        ->default_value(GOS_ARDT_DEFAULT_SEPARATOR),
        "value separator")
      (GOS_ARDT_MOD_INTERNAL, GOS_ARDT_MOD_INTERNAL);

    po::options_description clioptions(
      GOS_ARDUINO_TOOLS_MASTER_NAME " " GOST_USAGE, GOS_PO_LINE_LENGTH);
    clioptions
      .add(optdescript)
      .add(communicationdescript)
      .add(timer)
      .add(custom);

    po::variables_map varmap;

    /* First round with CLI parser only */
    po::command_line_parser cmdlinparser(argc, argv);
    po::parsed_options parseopt = cmdlinparser.options(clioptions)
      .style(po::command_line_style::default_style).run();
    po::store(parseopt, varmap);

    if (gpto::handling::help(clioptions, varmap)) {
      return GOS_PO_EXIT_HELP;
    }

    std::string version = "1.0.0.0";
    std::string name = GOS_ARDUINO_TOOLS_MASTER_NAME;

    if (gpto::handling::version(varmap, name, version)) {
      return GOS_PO_EXIT_VERSION;
    }

    gpto::handling::verbosity(varmap);

    /* second round */
    po::notify(varmap);

    /* Create the configuration file options description */
    po::options_description configfdesc;
    configfdesc
      .add(communicationdescript)
      .add(timer)
      .add(custom);
    if (gpto::handling::file(configfdesc, varmap) == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }

    gpto::handling::communication(varmap);
#ifdef GOS_NOT_YET_USED
    gato::handling::tool(varmap);
#endif

    if (varmap.count(GOS_ARDT_MOD_BASE_LINE) > 0) {
      gpt::setting::parameters.BaseLine =
        varmap[GOS_ARDT_MOD_BASE_LINE].as<gpat::Real>();
    }

    if (varmap.count(GOS_ARDT_MOD_TUNING) > 0) {
      std::string tuningmodetext =
        varmap[GOS_ARDT_MOD_TUNING].as<std::string>();
      if (tuningmodetext.compare(GOS_ARDT_MOD_TUNING_MODE_BLACK_BOX) == 0) {
        tune::mode = gpt::types::TuningMode::blackbox;
      } else {
        std::cerr << "'" << tuningmodetext
          << "' is not supported tune mode" << std::endl;
        return EXIT_FAILURE;
      }
    }

    result = gpam::master::initialize(
      gpts::communication::serial::port.c_str(),
      gpts::communication::serial::baud,
      gpts::slave::id);

    if (result != gpam::types::result::success) {
      std::cerr << gpam::master::report::error::last() << std::endl;
      return EXIT_FAILURE;
    }

    result = gpam::master::connect();
    if (result != gpam::types::result::success) {
      std::cerr << "Failed to connect to Modbus Slave " << gpts::slave::id
        << " through " << gpts::communication::serial::port
        << " baud rate " << gpts::communication::serial::baud << std::endl;
      goto gos_arduino_tools_pid_modbus_master_exit_failure;
    }

    if (gpammr::write::interval(static_cast<
      gpat::Unsigned>(gpts::timing::interval::milliseconds::loop))
      != gpam::types::result::success) {
      std::cerr << "Failed to write interval" << std::endl;
      goto gos_arduino_tools_pid_modbus_master_exit_failure;
    }

    std::streambuf* bufferpointer = nullptr;
    if (varmap.count(GOS_ARDT_MOD_OUTPUT) == 0) {
      bufferpointer = std::cout.rdbuf();
      if (bufferpointer == nullptr) {
        std::cerr << "Failed to get buffer pointer from standard out"
          << std::endl;
        goto gos_arduino_tools_pid_modbus_master_exit_failure;
      }
    } else {
      output::file::path = varmap[GOS_ARDT_MOD_OUTPUT].as<std::string>();
      output::file::stream::pointer = std::make_unique<std::ofstream>();
      if (output::file::stream::pointer) {
        output::file::stream::pointer->open(
          output::file::path,
          std::ios::trunc | std::ios::out);
        bufferpointer = output::file::stream::pointer->rdbuf();
        if (bufferpointer == nullptr) {
          std::cerr << "Failed to get buffer pointer from output file"
            << std::endl;
          goto gos_arduino_tools_pid_modbus_master_exit_failure;
        }
      } else {
        std::cerr << "Failed to create an output file" << std::endl;
        goto gos_arduino_tools_pid_modbus_master_exit_failure;
      }
    }
    assert(bufferpointer != nullptr);
    std::ostream output(bufferpointer);

    if (!gpt::black::box::initial::apply::tuning(
      tune::initialized,
      varmap,
      tune::variables,
      tune::black::box::variables,
      gpt::setting::parameters,
      tune::mode)) {
      goto gos_arduino_tools_pid_modbus_master_exit_failure;
    }

    if (varmap.count(GOS_ARDT_MOD_FINAL) > 0) {
      force::final = varmap[GOS_ARDT_MOD_FINAL].as<gpat::Unsigned>();
    }

    switch (tune::mode) {
    case gpt::types::TuningMode::blackbox:
      force::value = GOT_PI_FORCE_AUTO;
      break;
    default:
      if (varmap.count(GOS_ARDT_MOD_FORCE) > 0) {
        force::value = varmap[GOS_ARDT_MOD_FORCE].as<gpat::Unsigned>();
      }
      break;
    }

    if (force::value.is_initialized()) {
      if (gpammr::write::force(force::value.get())
        != gpam::types::result::success) {
        goto gos_arduino_tools_pid_modbus_master_exit_failure;
      }
    }

    is::internal = varmap.count(GOS_ARDT_MOD_INTERNAL) > 0;

    gpt::output::header(
      output,
      output::separator,
      is::internal,
      varmap, tune::mode);

    if (gpammr::read::holding(modbus::holding) != gpam::types::result::success) {
      goto gos_arduino_tools_pid_modbus_master_exit_failure;
    }

    switch (tune::mode) {
    case gpt::types::TuningMode::blackbox:
      gpt::black::box::load(
        tune::black::box::variables,
        tune::initialized,
        modbus::holding,
        output::separator,
        is::internal);
      break;
    }

    gp::toolkit::type::Duration duration;
    std::chrono::milliseconds dms;
    gp::toolkit::type::Time time, starttime =
      gp::toolkit::type::Clock::now();
    bool localgo = go.load();
    while (localgo) {
      time = gp::toolkit::type::Clock::now();

      duration = time - starttime;
      dms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
      elapsed = static_cast<double>(dms.count()) / 1000.0;

      result = gpammr::read::input(modbus::input);
      is::successful = result == gpam::types::result::success;

      if (!is::successful) {
        std::cerr << gpam::master::report::error::last() << std::endl;
      }

      gpt::output::result(
        output,
        modbus::input,
        modbus::holding,
        tune::initialized,
        tune::variables,
        output::separator,
        is::internal,
        is::successful,
        varmap,
        tune::mode);

      gpt::black::box::cycle(
        round,
        tune::variables,
        tune::black::box::variables,
        tune::black::box::evaluation,
        gpt::setting::parameters,
        modbus::input,
        elapsed,
        time,
        output::separator,
        is::successful,
        is::internal);

      if (output::file::stream::pointer) {
        output::file::stream::pointer->flush();
      }

      if (localgo = go.load()) {
#if defined(_WIN32)
        if (handle) {
          CloseHandle(handle);
        }
        handle = CreateEvent(
          NULL,               // Default security attributes
          TRUE,               // Manual-reset event
          FALSE,              // Initial state is non-signaled
          NULL                // Object name
        );
        if (handle) {
          wait = WaitForSingleObject(
            handle,
            gpts::timing::interval::milliseconds::loop);
          switch (wait) {
          case WAIT_OBJECT_0:
          case WAIT_TIMEOUT:
            break;
          case WAIT_ABANDONED:
          case WAIT_FAILED:
          default:
            std::cerr << "Waiting for the go lock failed" << std::endl;
            goto gos_arduino_tools_pid_modbus_master_exit_failure;
          }
        } else {
          std::cerr << "Failed to create loop wait event" << std::endl;
          goto gos_arduino_tools_pid_modbus_master_exit_failure;
        }
#else
        std::this_thread::sleep_for(gpts::timing::interval::duration());
#endif
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

  goto gos_arduino_tools_pid_modbus_master_exit;

gos_arduino_tools_pid_modbus_master_exit_failure:
  retval = EXIT_FAILURE;

gos_arduino_tools_pid_modbus_master_exit:
  if (output::file::stream::pointer) {
    output::file::stream::pointer->flush();
    output::file::stream::pointer->close();
  }
  switch (tune::mode) {
  case gpt::types::TuningMode::blackbox:
    gpt::black::box::shutdown();
    break;
  default:
    if(force::final.is_initialized()) {
      gpammr::write::force(force::final.get());
    }
    break;
  }
  gpam::master::disconnect();
  gpam::master::shutdown();
  return retval;
}
