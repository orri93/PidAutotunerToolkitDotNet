#ifndef GOS_PID_TOOLKIT_SERVICE_WIN_TRIGGER_H_
#define GOS_PID_TOOLKIT_SERVICE_WIN_TRIGGER_H_

#include <windows.h>

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace windows {
namespace trigger {

namespace check {
bool supported();
}

namespace information {
bool get(SC_HANDLE hService, LPBOOL lpfIsTriggerStart);
}

bool set(SC_HANDLE hService);

}
}
}
}
}
}

#endif
