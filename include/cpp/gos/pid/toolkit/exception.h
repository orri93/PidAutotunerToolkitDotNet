#ifndef GOS_PID_TOOLKIT_EXCEPTION_H_
#define GOS_PID_TOOLKIT_EXCEPTION_H_

#include <string>
#include <exception>

namespace gos {
namespace pid {
namespace toolkit {

class exception : public std::exception {
public:
  exception(const char* what);
#if _MSC_VER >= 1910
  const char* what() const noexcept override;
#else
  const char* what() const;
#endif
private:
  std::string what_;
};

} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
