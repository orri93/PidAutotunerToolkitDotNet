#ifndef GOS_PID_TOOLKIT_SERVICE_H_
#define GOS_PID_TOOLKIT_SERVICE_H_

namespace gos {
namespace pid {
namespace toolkit {
namespace service {

bool create();
void shutdown();

bool start();
bool stop();

bool cycle();

}
}
}
}

#endif
