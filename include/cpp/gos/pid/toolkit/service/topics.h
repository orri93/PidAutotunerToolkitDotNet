#ifndef GOS_PID_TOOLKIT_SERVICE_TOPICS_H_
#define GOS_PID_TOOLKIT_SERVICE_TOPICS_H_

/* Commands */
#define GPT_MT_COMMAND "command"
#define GPT_MT_GENERAL "general"
#define GPT_MT_TUNING "tuning"
#define GPT_MT_START "start"
#define GPT_MT_ABORT "abort"

/* Configuration */
#define GPT_MT_CONFIGURATION "configuration"
#define GPT_MT_BLACKBOX "blackbox"
#define GPT_MT_GET "get"
#define GPT_MT_SET "set"

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace topics {
void create();
}
}
}
}
}

#endif
