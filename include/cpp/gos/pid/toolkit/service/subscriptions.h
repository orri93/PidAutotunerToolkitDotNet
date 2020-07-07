#ifndef GOS_PID_TOOLKIT_SERVICE_SUBSCRIPTIONS_H_
#define GOS_PID_TOOLKIT_SERVICE_SUBSCRIPTIONS_H_

#include <vector>

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace subscriptions {
typedef std::vector<std::string> Subscriptions;

namespace definitions {
void create(const char* prefix);
Subscriptions& get();
}

namespace active {
void add(const char* subscription);
void remove(const char* subscription);
void get(Subscriptions& subscriptions);
}

}
}
}
}
}

#endif
