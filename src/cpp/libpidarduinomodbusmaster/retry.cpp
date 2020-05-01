#include <thread>

#include <gos/pid/arduino/modbus/retry.h>
#include <gos/pid/arduino/modbus/master.h>

#define GPA_RETRY_SLEEP(d) std::this_thread::sleep_for(d)

#define GPA_RETRY0(m) \
  gpamt::result result = gpamt::result::undefiend; \
  for (int rt = 0; rt < details::_retry; ++rt) { \
    result = gpam::master::m(); \
    if (result == gpam::types::result::success) { \
      break; \
   } else { \
      GPA_RETRY_SLEEP(details::_delay); \
    } \
  } \
  return result

#define GPA_RETRY1(m,p) \
  gpamt::result result = gpamt::result::undefiend; \
  for (int rt = 0; rt < details::_retry; ++rt) { \
    result = gpam::master::m(p); \
    if (result == gpam::types::result::success) { \
      break; \
   } else { \
      GPA_RETRY_SLEEP(details::_delay); \
    } \
  } \
  return result

#define GPA_RETRY2(m,p1,p2) \
  gpamt::result result = gpamt::result::undefiend; \
  for (int rt = 0; rt < details::_retry; ++rt) { \
    result = gpam::master::m(p1,p2); \
    if (result == gpam::types::result::success) { \
      break; \
   } else { \
      GPA_RETRY_SLEEP(details::_delay); \
    } \
  } \
  return result

#define GPA_RETRY3(m,p1,p2,p3) \
  gpamt::result result = gpamt::result::undefiend; \
  for (int rt = 0; rt < details::_retry; ++rt) { \
    result = gpam::master::m(p1,p2); \
    if (result == gpam::types::result::success) { \
      break; \
   } else { \
      GPA_RETRY_SLEEP(details::_delay); \
    } \
  } \
  return result


namespace gp = ::gos::pid;
namespace gpt = ::gos::pid::toolkit;

namespace gpa = ::gos::pid::arduino;
namespace gpat = ::gos::pid::arduino::types;

namespace gpam = ::gos::pid::arduino::modbus;
namespace gpamt = ::gos::pid::arduino::modbus::types;

namespace gos {
namespace pid {
namespace arduino {
namespace modbus {
namespace master {
namespace retry {

namespace details {
static int _retry = 3;
static gpt::type::Duration _delay = std::chrono::milliseconds(250);
}

namespace delay {
void set(const gpt::type::Duration& delay) {
  details::_delay = delay;
}
gpt::type::Duration get() {
  return details::_delay;
}
}

void set(const int& retry) {
  details::_retry = retry;
}
int get() {
  return details::_retry;
}

gpamt::result connect() { GPA_RETRY0(connect); }

namespace read {
gpamt::result input(gpamt::registry::Input& input) {
  GPA_RETRY1(read::input, input);
}
gpamt::result holding(gpamt::registry::Holding& holding) {
  GPA_RETRY1(read::holding, holding);
}
} // namespace read
namespace write {
gpamt::result holding(const gpamt::registry::Holding& holding) {
  GPA_RETRY1(write::holding, holding);
}
gpamt::result interval(const gpat::Unsigned& interval) {
  GPA_RETRY1(write::interval, interval);
}
gpamt::result manual(const gpat::Unsigned& manual) {
  GPA_RETRY1(write::manual, manual);
}
gpamt::result setpoint(const gpat::Real& setpoint)
{
  GPA_RETRY1(write::setpoint, setpoint);
}
gpamt::result kp(const gpat::Real& kp) {
  GPA_RETRY1(write::kp, kp);
}
gpamt::result ki(const gpat::Real& ki) {
  GPA_RETRY1(write::ki, ki);
}
gpamt::result kd(const gpat::Real& kd) {
  GPA_RETRY1(write::kd, kd);
}
gpamt::result tuning(
  const gpat::Real& kp,
  const gpat::Real& ki) {
  GPA_RETRY2(write::tuning, kp, ki);
}
gpamt::result tuning(
  const gpat::Real& kp,
  const gpat::Real& ki,
  const gpat::Real& kd) {
  GPA_RETRY3(write::tuning, kp, ki, kd);
}
gpamt::result sensor(const gpat::Real& minimum, const gpat::Real& maximum) {
  GPA_RETRY2(write::sensor, minimum, maximum);
}
gpamt::result time(const gpat::Unsigned& tuning) {
  GPA_RETRY1(write::time, tuning);
}
gpamt::result force(const gpat::Unsigned& force) {
  GPA_RETRY1(write::force, force);
}
} // namespace write

} // namespace retry
} // namespace master
} // namespace modbus
} // namespace arduino
} // namespace pid
} // namespace gos

