#include <regex>

#include <gos/pid/toolkit/serial.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace serial {

namespace compensate {
::std::string port(const char* device) {
  std::string port(device);
#ifdef _WIN32
  std::regex highport("COM\\d{2}");
  if (std::regex_match(port, highport)) {
    port = "\\\\.\\" + port;
  }
#endif
  return port;
}
} // namespace compensate

} // namespace serial
} // namespace toolkit
} // namespace pid 
} // namespace gos

