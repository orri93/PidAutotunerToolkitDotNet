#include <cstdlib>

#include <string>

#include <iostream>

#include <boost/filesystem.hpp>

#include <gos/pid/toolkit/default.h>
#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/options.h>
#include <gos/pid/toolkit/stream.h>
#include <gos/pid/toolkit/text.h>

namespace po = ::boost::program_options;

namespace gpt = ::gos::pid::toolkit;
namespace gptt = ::gos::pid::toolkit::text;


namespace gptd = ::gos::pid::toolkit::defval;
namespace gptdr = ::gos::pid::toolkit::defval::reporting;
namespace gptdrl = ::gos::pid::toolkit::defval::reporting::logging;
namespace gpttcf = ::gos::pid::toolkit::text::capitalised::first;
namespace gptto = ::gos::pid::toolkit::text::option;
namespace gpttoc = ::gos::pid::toolkit::text::option::composite;
namespace gpttod = ::gos::pid::toolkit::text::option::description;
namespace gpts = ::gos::pid::toolkit::setting;
namespace gptscf = ::gos::pid::toolkit::setting::configuration::file;
namespace gptsr = ::gos::pid::toolkit::setting::reporting;
namespace gptsrl = ::gos::pid::toolkit::setting::reporting::logging;

namespace gos {
namespace pid {
namespace toolkit {
namespace options {

namespace general {
const char* Name = gpttcf::General;
void create(po::options_description& description, const bool& file) {
  description.add_options()
    (gpttoc::general::Help, gpttod::general::Help)
    (gpttoc::general::Version, gpttod::general::Version)
    (gptto::general::Verbose, gpttod::general::Verbose)
    (gptto::general::Silent, gpttod::general::Silent)
    (gptto::general::Quiet, gpttod::general::Quiet);
  if (file) {
    description.add_options()
      (gpttoc::general::Config, po::value<std::string>(),
        gpttod::general::Config);
  }
}
}

namespace reporting {
const char* Name = gpttcf::Reporting;
void create(::boost::program_options::options_description& description) {
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
  description.add_options()
    (gpttoc::reporting::logging::Level, po::value(&gptsrl::level)
      ->default_value(gptdrl::Level), gpttod::reporting::logging::Level)
    (gptto::reporting::logging::Format, po::value(&gptsrl::format)
      ->default_value(gptdrl::Format), gpttod::reporting::logging::Format)
    (gptto::reporting::logging::file::Path, po::value(&gptsrl::file::path)
      ->default_value(gptdrl::file::Path), gpttod::reporting::logging::file::Path)
    (gptto::reporting::logging::file::Pattern, po::value(&gptsrl::file::pattern)
      ->default_value(gptdrl::file::Pattern), gpttod::reporting::logging::file::Pattern)
    (gptto::reporting::logging::file::rotation::Size, po::value(&gptsrl::file::rotation::size)
      ->default_value(gptdrl::file::rotation::Size), gpttod::reporting::logging::file::rotation::Size);
#endif
  /* PLACEHOLDER other reporting options */
}
}


namespace communication {
const char* Name = gpttcf::Communication;
void create(po::options_description& description) {
  description.add_options()
    (gpttoc::communication::modbus::serial::Port,
      po::value(&(gpts::communication::serial::port))
      ->default_value(gptd::communication::serial::Port),
      gpttod::communication::modbus::serial::Port)
    (gpttoc::communication::modbus::serial::Baud,
      po::value(&(gpts::communication::serial::baud))
      ->default_value(gptd::communication::serial::Baud),
      gpttod::communication::modbus::serial::Baud)
    (gpttoc::communication::modbus::slave::Id,
      po::value(&(gpts::slave::id)) ->default_value(gptd::slave::Id),
      gpttod::communication::modbus::slave::Id);
#ifdef GOS_PID_TOOLKIT_MQTT
  description.add_options()
    (gptto::communication::mqtt::topic::Prefix,
      po::value(&(gpts::communication::mqtt::topic::prefix))
      ->default_value(gptd::communication::mqtt::topic::Prefix),
      gpttod::communication::mqtt::topic::Prefix)
    (gptto::communication::mqtt::client::Id,
      po::value(&(gpts::communication::mqtt::client::id))
      ->default_value(gptd::communication::mqtt::client::Id),
      gpttod::communication::mqtt::client::Id)
    (gptto::communication::mqtt::Qos,
      po::value(&(gpts::communication::mqtt::qos))
      ->default_value(gptd::communication::mqtt::Qos),
      gpttod::communication::mqtt::Qos)
    (gpttoc::communication::mqtt::Host,
      po::value(&(gpts::communication::mqtt::host))
      ->default_value(gptd::communication::mqtt::Host),
      gpttod::communication::mqtt::Host)
    (gpttoc::communication::mqtt::Port,
      po::value(&(gpts::communication::mqtt::port))
      ->default_value(gptd::communication::mqtt::Port),
      gpttod::communication::mqtt::Port)
    (gptto::communication::mqtt::connection::Timeout,
      po::value(&(gpts::communication::mqtt::connection::timeout))
      ->default_value(gptd::communication::mqtt::connection::Timeout),
      gpttod::communication::mqtt::connection::Timeout);
#endif
}
}

namespace timer {
const char* Name = gpttcf::Timer;
void create(::boost::program_options::options_description& description,
  const int& defaultloopinterval) {
  description.add_options()
    (gptto::timing::Interval, po::value(&(gpts::timing::interval::milliseconds::loop))
      ->default_value(defaultloopinterval), gpttod::timing::Interval);
}
}

namespace handling {

static std::string lasterrortext_;

bool help(
  ::boost::program_options::options_description& description,
  ::boost::program_options::variables_map& map) {
  if (map.count(gptt::Help)) {
    std::cout << description << std::endl;
    return true;
  } else {
    return false;
  }
}

bool version(
  ::boost::program_options::variables_map& map,
  const std::string& name,
  const std::string& version) {
  if (map.count(gptt::Version)) {
    std::cout << name << " version " << version << std::endl;
    return true;
  } else {
    return false;
  }
}

void verbosity(::boost::program_options::variables_map& map) {
  if (map.count(gptt::Quiet) || map.count(gptt::Silent)) {
    gpts::reporting::verbosity = gpt::type::reporting::level::silent;
  } else if (map.count(gptt::Verbose)) {
    gpts::reporting::verbosity = gpt::type::reporting::level::verbose;
  }
}

int file(
  ::boost::program_options::options_description& filedescription,
  ::boost::program_options::variables_map& map) {
  if (map.count(gptto::general::Config)) {
    if (!gptscf::apply(map[gptto::general::Config].as<std::string>())) {
      lasterrortext_ = gptscf::lasterrortext();
      std::cerr << lasterrortext_ << std::endl;
      return EXIT_FAILURE;
    }
  } else if (map.count(gptto::general::Configuration)) {
    if (!gptscf::apply(map[gptto::general::Configuration].
      as<std::string>())) {
      lasterrortext_ = gptscf::lasterrortext();
      std::cerr << lasterrortext_ << std::endl;
      return EXIT_FAILURE;
    }
  }
  if (gptscf::iswithfile()) {
    if (gpts::isverbose()) {
      std::cout << "Using '" << gptscf::configurationfilename()
        << "' as configuration file" << std::endl;
    }
    std::ifstream& stream = gptscf::stream();
    po::store(po::parse_config_file(stream, filedescription), map);
    po::notify(map);
    gptscf::close();
  }
  return EXIT_SUCCESS;
}

void reporterror(const ::std::string& errortext) {
  lasterrortext_ = errortext;
}

::std::string lasterrortext() {
  return lasterrortext_;
}

void communication(po::variables_map& map) {
#ifdef NOT_NEEDED
  if (map.count(gptt::Port)) {
    gpts::endpoint.second = map[gptt::Port].as<uint16_t>();
  }
  if (map.count(gptt::option::ListenIpAddress)) {
    gpts::endpoint.first = map[gptt::option::ListenIpAddress].as<std::string>();
  }
  if (map.count(gptt::option::MaximumConnection)) {
    gpts::maximum_number_of_connection =
      map[gptt::option::MaximumConnection].as<int>();
  }
  if (map.count(gptt::option::SlaveId)) {
    gpts::slave_id = map[gptt::option::SlaveId].as<int>();
  }
#endif
}

}

}
}
}
}

