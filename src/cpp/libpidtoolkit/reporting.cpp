#include <iostream>
#include <chrono>
#include <mutex>
#include <map>

#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/filesystem.hpp>
#endif

#include <gos/pid/toolkit/reporting.h>
#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/version.h>

#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
namespace b = ::boost;
namespace bl = ::boost::log;
namespace blk = ::boost::log::keywords;
namespace bf = ::boost::filesystem;
#endif

namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;
namespace gptt = ::gos::pid::toolkit::type;
namespace gpttr = ::gos::pid::toolkit::type::reporting;
namespace gpttrl = ::gos::pid::toolkit::type::reporting::logging;

namespace gpts = ::gos::pid::toolkit::setting;
namespace gptsr = ::gos::pid::toolkit::setting::reporting;

namespace gos {
namespace pid {
namespace toolkit {
namespace reporting {

typedef std::lock_guard<std::mutex> Guard;

std::mutex _lock;
std::string _name;

void initialize(const char* name) {
  _name = name;
  Guard guard(_lock);
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
  if (gptsr::logging::level != gpttrl::level::none) {

    std::stringstream filenamestream;
    filenamestream << _name << "-" << gptsr::logging::file::pattern;
    std::string filename = filenamestream.str();

    bf::path filepath(gptsr::logging::file::path);
    filepath.append(filename);

    std::string format = gptsr::logging::format;

    b::filesystem::path::imbue(std::locale("C"));

    b::shared_ptr<bl::core> core = bl::core::get();

    bl::register_simple_formatter_factory<
      bl::trivial::severity_level, char>("Severity");

#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG_BACKEND
    b::shared_ptr<bl::sinks::text_file_backend> backend;
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG_ROTATE_AT_MIDNIGHT
    auto& timerotation = bl::sinks::file::rotation_at_time_point(0, 0, 0);
    backend =
      b::make_shared<bl::sinks::text_file_backend >(
        blk::format = gptsr::logging::format,
        blk::file_name = filepath,
        blk::rotation_size = gptsr::logging::file::rotation::size,
        blk::time_based_rotation = timerotation,
        blk::auto_flush = true);
#else
    backend =
      b::make_shared<bl::sinks::text_file_backend>(
        blk::format = format,
        blk::file_name = filepath,
        blk::rotation_size = gptsr::logging::file::rotation::size,
        blk::auto_flush = true);
#endif
    //backend->auto_flush(true);
    typedef bl::sinks::synchronous_sink<bl::sinks::text_file_backend> sink_t;
    b::shared_ptr<sink_t> sink(new sink_t(backend));
    core->add_sink(sink);
#else
    bl::add_file_log(
      blk::file_name = filepath,
      blk::rotation_size = gptsr::logging::file::rotation::size,
      blk::format = format,
      blk::auto_flush = true);
#endif

    switch (gptsr::logging::level) {
    case gpttrl::level::debug:
      core->set_filter(bl::trivial::severity >= bl::trivial::debug);
      break;
    case gpttrl::level::info:
      core->set_filter(bl::trivial::severity >= bl::trivial::info);
      break;
    case gpttrl::level::warning:
      core->set_filter(bl::trivial::severity >= bl::trivial::warning);
      break;
    case gpttrl::level::critical:
      core->set_filter(bl::trivial::severity >= bl::trivial::error);
      break;
    }

    bl::add_common_attributes();
  } else {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    if (gpts::isverbose()) {
      std::cout << "Logging is disabled with logging level none" << std::endl;
    }
#endif
  }
#endif
}
void shutdown() {
  Guard guard(_lock);
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
  b::shared_ptr<bl::core> core = bl::core::get();
  core->remove_all_sinks();
#endif
}

static bool _report = true;

void set(const bool& report) {
  _report = report;
}

void welcome() {
  Stream welstr;
  welstr << "Starting " << _name << " " << gpt::version::generate(gpt::version::WithAll);
  information::report(welstr);
}

namespace verbose {
void report(Stream& stream) {
  report(stream.str());
}
void report(const std::string& message) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    if (gpts::isverbose()) {
      Guard guard(_lock);
      std::cout << message << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(debug) << message;
    }
#endif
  }
}
}

namespace information {
bool report(Stream& stream) {
  return report(stream.str());
}

bool report(const std::string& message) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    if (gpts::isnormal()) {
      Guard guard(_lock);
      std::cout << message << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(info) << message;
    }
#endif
  }
  return true;
}
}

namespace warning {
bool report(Stream& stream) {
  return report(stream.str());
}
bool report(Stream& stream, const int& code) {
  return report(stream.str(), code);
}
bool report(Stream& stream, const std::exception& ex) {
  return report(stream.str(), ex);
}
bool report(const std::string& message) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    {
      Guard guard(_lock);
      std::cerr << message << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(warning) << message;
    }
#endif
  }
  return false;
}
bool report(const std::string& message, const int& code) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    {
      Guard guard(_lock);
      std::cerr << message << " code is " << code << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(warning) << message << " [code: " << code << "]";
    }
#endif
  }
  return false;
}
bool report(const std::string& message, const std::exception& ex) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    {
      Guard guard(_lock);
      std::cerr << message << " exception: '" << ex.what() << "'" << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(warning) << message
        << " [exception: " << ex.what() << "]";
    }
#endif
  }
  return false;
}
}

namespace error {
bool report(Stream& stream) {
  return report(stream.str());
}
bool report(Stream& stream, const int& code) {
  return report(stream.str(), code);
}
bool report(Stream& stream, const std::exception& ex) {
  return report(stream.str(), ex);
}
bool report(const std::string& message) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    {
      Guard guard(_lock);
      std::cerr << message << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(error) << message;
    }
#endif
  }
  return false;
}
bool report(const std::string& message, const int& code) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    {
      Guard guard(_lock);
      std::cerr << message << " code is " << code << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(error) << message << " [code: " << code << "]";
    }
#endif
  }
  return false;
}
bool report(const std::string& message, const std::exception& ex) {
  if (_report) {
#ifdef GOS_PID_TOOLKIT_REPORT_CONSOLE
    {
      Guard guard(_lock);
      std::cerr << message << " exception: '" << ex.what() << "'" << std::endl;
    }
#endif
#ifdef GOS_PID_TOOLKIT_REPORT_BOOST_LOG
    if (gptsr::logging::level != gpttrl::level::none) {
      Guard guard(_lock);
      BOOST_LOG_TRIVIAL(error) << message
        << " [exception: " << ex.what() << "]";
    }
#endif
  }
  return false;
}
}

namespace repeate {
namespace limiting {

typedef std::map<std::string, gptt::Time> LastMap;
typedef LastMap::value_type LastMapValueType;
typedef LastMap::iterator LastMapIterator;

static bool show(
  LastMap& map,
  const gptt::Duration& between,
  const std::string& message);
static bool show(LastMap& map, const std::string& message);

namespace verbose {
LastMap last;
void report(Stream& stream) {
  report(stream.str());
}
void report(const std::string& message) {
  if (show(last, message)) {
    gpt::reporting::verbose::report(message);
  }
}
}

namespace information {
LastMap last;
void report(Stream& stream) {
  report(stream.str());
}
void report(const std::string& message) {
  if (show(last, message)) {
    gpt::reporting::information::report(message);
  }
}
}

namespace warning {
LastMap last;
bool report(Stream& stream) {
  return report(stream.str());
}
bool report(Stream& stream, const int& code) {
  return report(stream.str(), code);
}
bool report(Stream& stream, const std::exception& ex) {
  return report(stream.str(), ex);
}
bool report(const std::string& key, Stream& stream) {
  if (show(last, key)) {
    return report(stream.str());
  } else {
    return false;
  }
}
bool report(const std::string& key, Stream& stream, const int& code) {
  if (show(last, key)) {
    return report(stream.str(), code);
  } else {
    return false;
  }
}
bool report(const std::string& key, Stream& stream, const std::exception& ex) {
  if (show(last, key)) {
    return report(stream.str(), ex);
  } else {
    return false;
  }
}
bool report(const std::string& message) {
  if (show(last, message)) {
    return gpt::reporting::warning::report(message);
  } else {
    return false;
  }
}
bool report(const std::string& message, const int& code) {
  if (show(last, message)) {
    return gpt::reporting::warning::report(message, code);
  } else {
    return false;
  }
}
bool report(const std::string& message, const std::exception& ex) {
  if (show(last, message)) {
    return gpt::reporting::warning::report(message, ex);
  } else {
    return false;
  }
}
}

namespace error {
LastMap last;
bool report(Stream& stream) {
  return report(stream.str());
}
bool report(Stream& stream, const int& code) {
  return report(stream.str(), code);
}
bool report(Stream& stream, const std::exception& ex) {
  return report(stream.str(), ex);
}
bool report(const std::string& message) {
  if (show(last, message)) {
    return gpt::reporting::error::report(message);
  } else {
    return false;
  }
}
bool report(const std::string& message, const int& code) {
  if (show(last, message)) {
    return gpt::reporting::error::report(message, code);
  } else {
    return false;
  }
}
bool report(const std::string& message, const std::exception& ex) {
  if (show(last, message)) {
    return gpt::reporting::error::report(message, ex);
  } else {
    return false;
  }
}
}
bool show(
  LastMap& map,
  const gptt::Duration& between,
  const std::string& message) {
  if (_report) {
    gptt::Time tick = gptt::Clock::now();
    LastMapIterator fit = map.find(message);
    if (fit != map.end()) {
      gptt::Time& last = fit->second;
      if ((tick - last) >= between) {
        last = tick;
        return true;
      } else {
        return false;
      }
    } else {
      map.insert(LastMapValueType(message, tick));
      return true;
    }
  } else {
    return false;
  }
}

bool show(LastMap& map, const std::string& message) {
  return show(map, gptsr::repeate::Between(), message);
}
}
}

}
}
}
}
