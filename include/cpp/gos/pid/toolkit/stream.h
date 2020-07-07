#ifndef GOS_PID_TOOLKIT_STREAM_H_
#define GOS_PID_TOOLKIT_STREAM_H_

#include <istream>
#include <ostream>

#include <gos/pid/toolkit/types.h>

//namespace gos {
//namespace pid {
//namespace toolkit {
//namespace type {

//namespace reporting {
//namespace logging {

namespace std {
std::istream& operator>> (std::istream& is, ::gos::pid::toolkit::type::reporting::logging::level& level);
std::wistream& operator>> (std::wistream& is, ::gos::pid::toolkit::type::reporting::logging::level& level);
std::ostream& operator<< (std::ostream& os, const ::gos::pid::toolkit::type::reporting::logging::level& level);
std::wostream& operator<< (std::wostream& os, const ::gos::pid::toolkit::type::reporting::logging::level& level);
}

//}
//}

//}
//}
//}
//}

#endif
