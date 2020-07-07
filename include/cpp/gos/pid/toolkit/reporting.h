#ifndef GOS_PID_TOOLKIT_REPORTING_H_
#define GOS_PID_TOOLKIT_REPORTING_H_

#include <string>
#include <sstream>
#include <exception>

namespace gos {
namespace pid {
namespace toolkit {
namespace reporting {

typedef std::stringstream Stream;

void initialize(const char* name);
void shutdown();

void set(const bool& report);

void welcome();

namespace verbose {
void report(Stream& stream);
void report(const std::string& message);
}

namespace information {
bool report(Stream& stream);
bool report(const std::string& message);
}

namespace warning {
bool report(Stream& stream);
bool report(Stream& stream, const int& code);
bool report(Stream& stream, const std::exception& ex);
bool report(const std::string& message);
bool report(const std::string& message, const int& code);
bool report(const std::string& message, const std::exception& ex);
}

namespace error {
bool report(Stream& stream);
bool report(Stream& stream, const int& code);
bool report(Stream& stream, const std::exception& ex);
bool report(const std::string& message);
bool report(const std::string& message, const int& code);
bool report(const std::string& message, const std::exception& ex);
}

namespace repeate {
namespace limiting {
namespace verbose {
void report(Stream& stream);
void report(const std::string& message);
}

namespace information {
void report(Stream& stream);
void report(const std::string& message);
}

namespace warning {
bool report(Stream& stream);
bool report(Stream& stream, const int& code);
bool report(Stream& stream, const std::exception& ex);
bool report(const std::string& key, Stream& stream);
bool report(const std::string& key, Stream& stream, const int& code);
bool report(const std::string& key, Stream& stream, const std::exception& ex);
bool report(const std::string& message);
bool report(const std::string& message, const int& code);
bool report(const std::string& message, const std::exception& ex);
}

namespace error {
bool report(Stream& stream);
bool report(Stream& stream, const int& code);
bool report(Stream& stream, const std::exception& ex);
bool report(const std::string& message);
bool report(const std::string& message, const int& code);
bool report(const std::string& message, const std::exception& ex);
}
}
}

}
}
}
}

#endif
