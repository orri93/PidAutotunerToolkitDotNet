#include <gos/pid/toolkit/stream.h>
#include <gos/pid/toolkit/parsing.h>
#include <gos/pid/toolkit/text.h>

namespace gpt = ::gos::pid::toolkit;
namespace gptt = ::gos::pid::toolkit::type;
namespace gpttr = ::gos::pid::toolkit::type::reporting;
namespace gpttrl = ::gos::pid::toolkit::type::reporting::logging;

namespace gptp = ::gos::pid::toolkit::parsing;

//namespace gos {
//namespace pid {
//namespace toolkit {
//namespace type {

//namespace reporting {
//namespace logging {

namespace std {
std::istream& operator>> (std::istream& is, gpttrl::level& level) {
  std::string text;
  is >> text;
  level = gptp::logging::level(text);
  return is;
}

std::ostream& operator<< (std::ostream& os, const gpttrl::level& level) {
  std::string text = gpt::text::to::text(level);
  os << text;
  return os;
}
}

//}
//}

//}
//}
//}
//}
