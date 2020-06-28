/* To get rid of C4005 warning when modbus-tcp.h defines some error macros */

#include <gos/pid/toolkit/default.h>

namespace gpt = ::gos::pid::toolkit;

namespace gos {
namespace pid {
namespace toolkit {
namespace defval {

gpt::type::level Verbosity = gpt::type::level::normal;

namespace communication {
namespace serial {
const char* Port = DEFAULT_SERIAL_PORT;
const int Baud = DEFAULT_BAUD;
} // namespace serial
} // namespace communication

namespace slave {
const int Id = 1;
} // namespace slave

namespace timing {
namespace interval {
namespace milliseconds {
const int Loop = 0;
} // namespace milliseconds
} // namespace interval
} // namespace timing


} // namespace default
} // namespace toolkit
} // namespace pit
} // namespace gos
