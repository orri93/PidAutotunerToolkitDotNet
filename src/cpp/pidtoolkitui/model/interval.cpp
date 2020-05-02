#include <memory>
#include <map>

#ifdef GOS_COMPLEX_MODEL
#include <QList>
#else
#include <QStringList>
#endif

#include <model/interval.h>
#include <item/interval.h>

namespace gptu = ::gos::pid::toolkit::ui;
namespace gptui = ::gos::pid::toolkit::ui::item;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace interval {

#ifdef GOS_COMPLEX_MODEL
typedef QList<QObject*> ObjectList;
typedef std::unique_ptr<ObjectList> ObjectListPointer;
typedef std::unique_ptr<QVariant> VariantPointer;
#endif

typedef std::map<int, int> IntervalMap;
typedef IntervalMap::value_type IntervalValue;
typedef IntervalMap::iterator IntervalIterator;

static const int Intervals[] = { 1000, 750, 500, 250, 200, 150, 100, 50, 0 };

static IntervalMap _indexmap;
static IntervalMap _valuemap;
#ifdef GOS_COMPLEX_MODEL
static ObjectListPointer _list;
static VariantPointer _model;
#else
static QStringList _list;
#endif
static int _count;

int index(const int& value) {
  IntervalIterator it = _valuemap.find(value);
  if (it != _valuemap.end()) {
    return it->second;
  }
  return -1;
}

int value(const int& index) {
  IntervalIterator it = _indexmap.find(index);
  if (it != _indexmap.end()) {
    return it->second;
  }
  return -1;
}

#ifdef GOS_COMPLEX_MODEL
QVariant& create() {
  int i = 0;
  _list = std::make_unique<ObjectList>();
  const int* interval = Intervals;
  while (*interval != 0) {
    QObject* item = new gptui::Interval(
      QString("%1 ms").arg(*interval),
      *interval);
    _list->append(item);
    _indexmap.insert(IntervalValue(i, *interval));
    _valuemap.insert(IntervalValue(*interval, i));
    interval++;
    i++;
  }
  _model = std::make_unique<QVariant>(QVariant::fromValue(*_list));
  return *_model;
}
#else
QVariant create() {
  int i = 0;
  const int* interval = Intervals;
  while (*interval != 0) {
    _list.append(QString("%1 ms").arg(*interval));
    _indexmap.insert(IntervalValue(i, *interval));
    _valuemap.insert(IntervalValue(*interval, i));
    interval++;
    i++;
  }
  return QVariant::fromValue(_list);
}
#endif

} // namespace interval
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos
