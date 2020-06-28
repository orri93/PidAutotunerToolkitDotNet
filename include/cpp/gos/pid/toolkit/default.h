#ifndef GOS_PID_TOOLKIT_DEFAULT_H_
#define GOS_PID_TOOLKIT_DEFAULT_H_

#include <string>

#include <gos/pid/toolkit/types.h>

#ifndef DEFAULT_SERIAL_PORT
#ifdef WIN32
#define DEFAULT_SERIAL_PORT "COM32"
#else
#define DEFAULT_SERIAL_PORT "/dev/ttyS0"
#endif
#endif
#ifndef DEFAULT_BAUD
#define DEFAULT_BAUD 9600
#endif

namespace gos {
namespace pid {
namespace toolkit {
namespace defval {

  namespace communication {
  namespace serial {
  extern const char* Port;
  extern const int Baud;
  } // namespace serial
  } // namespace communication

  namespace slave {
  extern const int Id;
  } // namespace slave

  namespace timing {
  namespace interval {
  namespace milliseconds {
  extern const int Loop;
  } // namespace milliseconds
  } // namespace interval
  } // namespace timing

} // namespace default
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
