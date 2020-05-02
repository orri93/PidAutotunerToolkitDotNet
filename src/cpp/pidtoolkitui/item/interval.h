#ifndef GOS_PID_TUNING_UI_ITEM_INTERVAL_H_
#define GOS_PID_TUNING_UI_ITEM_INTERVAL_H_

#include <QDebug>
#include <QObject>
#include <QString>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace item {

class Interval : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString text READ text)
  Q_PROPERTY(int value READ value)

public:
  Interval(QObject* parent = nullptr);
  Interval(const QString& text, const int& value, QObject* parent = nullptr);
  Interval(const Interval& item);

  Interval& operator=(const Interval& item);

  const QString& text() const;
  const int& value() const;

  void setText(const QString& text);
  void setValue(const int& value);

private:
  QString text_;
  int value_;
};

} // namespace item
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

bool operator==(
  const ::gos::pid::toolkit::ui::item::Interval& lhs,
  const ::gos::pid::toolkit::ui::item::Interval& rhs);
bool operator!=(
  const ::gos::pid::toolkit::ui::item::Interval& lhs,
  const ::gos::pid::toolkit::ui::item::Interval& rhs);
QDebug operator<< (QDebug debug,
  ::gos::pid::toolkit::ui::item::Interval& endpoint);


#endif
