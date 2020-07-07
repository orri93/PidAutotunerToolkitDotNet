#include <sstream>
#include <set>

#include <gos/pid/toolkit/reporting.h>
#include <gos/pid/toolkit/service/subscriptions.h>
#include <gos/pid/toolkit/service/topics.h>

namespace gptr = ::gos::pid::toolkit::reporting;

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace subscriptions {

namespace definitions {
static Subscriptions _subscriptions;
void create(const char* prefix) {
  std::stringstream generalcommand;
  std::stringstream configcommands;
  std::stringstream tuningcommands;

  if (prefix) {
    generalcommand << prefix << "/";
    configcommands << prefix << "/";
    tuningcommands << prefix << "/";
  }

  generalcommand << GPT_MT_COMMAND << "/" << GPT_MT_GENERAL << "/#";
  configcommands << GPT_MT_COMMAND << "/" << GPT_MT_CONFIGURATION << "/#";
  tuningcommands << GPT_MT_COMMAND << "/" << GPT_MT_TUNING << "/#";

  _subscriptions.clear();
  _subscriptions.push_back(generalcommand.str());
  _subscriptions.push_back(configcommands.str());
  _subscriptions.push_back(tuningcommands.str());

  gptr::information::report("Service subscriptions created");
}

Subscriptions& get() {
  return _subscriptions;
}
}

namespace active {
typedef std::set<std::string> Active;
typedef Active::iterator ActiveIterator;
Active _subscriptions;
void add(const char* subscription) {
  if (subscription) {
    ActiveIterator it = _subscriptions.find(subscription);
    if (it == _subscriptions.end()) {
      _subscriptions.insert(subscription);
      gptr::Stream stream;
      stream << "Service subscriptions " << subscription << " active";
      gptr::information::report(stream);
    }
  }
}
void remove(const char* subscription) {
  if (subscription) {
    ActiveIterator it = _subscriptions.find(subscription);
    if (it != _subscriptions.end()) {
      _subscriptions.erase(it);
      gptr::Stream stream;
      stream << "Service subscriptions " << subscription << " disabled";
      gptr::information::report(stream);
    }
  }
}
void get(Subscriptions& subscriptions) {
  subscriptions.clear();
  subscriptions.assign(_subscriptions.begin(), _subscriptions.end());
}
}



}
}
}
}
}