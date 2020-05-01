#ifndef GOS_PID_TOOLKIT_SERIAL_H_
#define GOS_PID_TOOLKIT_SERIAL_H_

#include <string>

namespace gos {
namespace pid {
namespace toolkit {
namespace serial {

namespace compensate {
::std::string port(const char* device);
} // namespace compensate

} // namespace serial
} // namespace toolkit
} // namespace pid 
} // namespace gos

#endif
