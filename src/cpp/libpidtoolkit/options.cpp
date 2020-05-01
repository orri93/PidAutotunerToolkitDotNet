#include <cstdlib>

#include <string>

#include <iostream>

#include <boost/filesystem.hpp>

#include <gos/pid/toolkit/default.h>
#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/options.h>
#include <gos/pid/toolkit/text.h>

namespace po = ::boost::program_options;

namespace gpt = ::gos::pid::toolkit;
namespace gptt = ::gos::pid::toolkit::text;

namespace gptd = ::gos::pid::toolkit::default;
namespace gpttcf = ::gos::pid::toolkit::text::capitalised::first;
namespace gptto = ::gos::pid::toolkit::text::option;
namespace gpts = ::gos::pid::toolkit::setting;
namespace gptscf = ::gos::pid::toolkit::setting::configuration::file;

namespace gos {
namespace pid {
namespace toolkit {
namespace options {

namespace general {
const char* Name = gpttcf::General;
void create(po::options_description& description, const bool& file) {
  description.add_options()
    (gptto::composite::Help, gptto::description::Help)
    (gptto::composite::Version, gptto::description::Version)
    (gptt::Verbose, gptto::description::Verbose)
    (gptt::Silent, gptto::description::Silent)
    (gptt::Quiet, gptto::description::Quiet);
  if (file) {
    description.add_options()
      (gptto::composite::Config, po::value<std::string>(),
        gptto::description::Config);
  }
}
}

namespace communication {
const char* Name = gpttcf::Communication;
void create(po::options_description& description) {
  description.add_options()
    (gptt::option::composite::SerialPort,
      po::value(&(gpts::communication::serial::port))
      ->default_value(gpt::default::communication::serial::Port),
      gptt::option::description::SerialPort)
    (gptt::option::composite::SerialBaud,
      po::value(&(gpts::communication::serial::baud))
      ->default_value(gpt::default::communication::serial::Baud),
      gptt::option::description::SerialBaud)
    (gptt::option::composite::SlaveId,
      po::value(&(gpts::slave::id)) ->default_value(gpt::default::slave::Id),
      gptt::option::description::SlaveId);
}
}

namespace timer {
const char* Name = gpttcf::Timer;
void create(::boost::program_options::options_description& description,
  const int& defaultloopinterval) {
  description.add_options()
    (gptt::option::LoopInterval,
      po::value(&(gpts::timing::interval::milliseconds::loop))
      ->default_value(defaultloopinterval),
      gptt::option::description::LoopInterval);
}
}

#ifdef GOS_NOT_USED_YET
namespace tool {
const char* Name = gpttcf::Tool;
void create(::boost::program_options::options_description& description) {
  description.add_options()
    (gptt::option::composite::Table, gptt::option::description::Table);
}
}
#endif


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
    gpts::verbosity = gpt::type::level::silent;
  } else if (map.count(gptt::Verbose)) {
    gpts::verbosity = gpt::type::level::verbose;
  }
}

int file(
  ::boost::program_options::options_description& filedescription,
  ::boost::program_options::variables_map& map) {
  if (map.count(gptt::Config)) {
    if (!gptscf::apply(map[gptt::Config].as<std::string>())) {
      lasterrortext_ = gptscf::lasterrortext();
      std::cerr << lasterrortext_ << std::endl;
      return EXIT_FAILURE;
    }
  } else if (map.count(gptto::ConfigurationFile)) {
    if (!gptscf::apply(map[gptto::ConfigurationFile].
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

void tool(po::variables_map& map) {
  if (map.count(gptt::Table)) {
  }
}

}

}
}
}
}

