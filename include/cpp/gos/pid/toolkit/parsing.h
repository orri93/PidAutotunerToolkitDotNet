#ifndef GOS_PID_TOOLKIT_PARSING_H_
#define GOS_PID_TOOLKIT_PARSING_H_

#include <gos/pid/toolkit/types.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace parsing {
namespace logging {
::gos::pid::toolkit::type::reporting::logging::level level(const std::string& text);
::gos::pid::toolkit::type::reporting::logging::level level(const std::wstring& text);
}
}
}
}
}

#endif
