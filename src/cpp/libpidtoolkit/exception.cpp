#include <sstream>

#include <gos/pid/toolkit/exception.h>

namespace gos {
namespace pid {
namespace toolkit {
exception::exception(const char* what) {
  std::stringstream s;
  s << "PID toolkit error: " << what;
  what_ = s.str();
}
#ifdef _MSC_VER
#if _MSC_VER >= 1910
const char* exception::what() const noexcept { return what_.c_str(); }
#else
const char* exception::what() const { return what_.c_str(); }
#endif
#else
const char* exception::what() const noexcept { return what_.c_str(); }
#endif
} // namespace toolkit
} // namespace pid 
} // namespace gos
