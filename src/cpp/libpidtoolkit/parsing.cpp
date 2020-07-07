#include <gos/pid/toolkit/parsing.h>
#include <gos/pid/toolkit/text.h>

namespace gpt = ::gos::pid::toolkit;

namespace gptt = ::gos::pid::toolkit::type;
namespace gpttr = ::gos::pid::toolkit::type::reporting;
namespace gpttrl = ::gos::pid::toolkit::type::reporting::logging;

namespace gos {
namespace pid {
namespace toolkit {

namespace parsing {

namespace logging {
gpttrl::level level(const std::string& text) {
  std::string lower = gpt::text::formating(text, gpt::text::format::lower);
  if (lower.compare("debug") == 0) {
    return gpttrl::level::debug;
  } else if (lower.compare("info") == 0) {
    return gpttrl::level::info;
  } else if (lower.compare("warning") == 0) {
    return gpttrl::level::warning;
  } else if (lower.compare("critical") == 0) {
    return gpttrl::level::critical;
  } else {
    return gpttrl::level::none;
  }
}
gpttrl::level level(const std::wstring& text) {
  std::wstring lower = gpt::text::wide::formating(text, gpt::text::format::lower);
  if (lower.compare(L"debug") == 0) {
    return gpttrl::level::debug;
  } else if (lower.compare(L"info") == 0) {
    return gpttrl::level::info;
  } else if (lower.compare(L"warning") == 0) {
    return gpttrl::level::warning;
  } else if (lower.compare(L"critical") == 0) {
    return gpttrl::level::critical;
  } else {
    return gpttrl::level::none;
  }
}
}

}

}
}
}
