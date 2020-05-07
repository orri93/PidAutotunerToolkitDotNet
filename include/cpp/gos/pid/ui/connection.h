#ifndef GOS_PID_TUNING_UI_ITEM_CONNECTION_H_
#define GOS_PID_TUNING_UI_ITEM_CONNECTION_H_

#include <QtGlobal>
#include <QtQml/QQmlEngine>

#define GOS_QML_ITEM_NAME_CONNECTION "PidConnection"
#define GOS_QML_ITEM_URI_CONNECTION GOS_QML_ITEM_NAME_CONNECTION

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace item {

class Connection : public QObject {
  Q_OBJECT

public:
  Connection(QObject* parent = nullptr);

  enum Status {
    PTC_UNDEFINED,
    PTC_CONNECTING,
    PTC_CONNECTED,
    PTC_DISCONNECTING,
    PTC_DISCONNECTED,
    PTC_UNKNOWN
  };
  Q_ENUMS(Status)
};

} // namespace item
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
