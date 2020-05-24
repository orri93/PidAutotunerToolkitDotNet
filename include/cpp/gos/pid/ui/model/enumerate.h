#ifndef GOS_PID_TUNING_UI_MODEL_ENUMERATE_H_
#define GOS_PID_TUNING_UI_MODEL_ENUMERATE_H_

#include <map>

#include <QAbstractListModel>
#include <QString>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

template<typename E, typename R, typename T = QString> class Enumerate {
public:
  Enumerate(
    const E* enumerate,
    const T* t,
    const T last,
    const E& undefined,
    const R& enumrole,
    const R& valuerole) :
    count_(0),
    undefined_(undefined),
    enumrole_(valuerole),
    valuerole_(valuerole),
    last_(last) {
    while (t != nullptr && *t != last) {
      enumvaluemap_.insert(EnumerateValueMap::value_type(*enumerate, *t));
      valueenummap_.insert(ValueEnumerateMap::value_type(*t, *enumerate));
      enumindexmap_.insert(EnumerateIndexMap::value_type(*enumerate, count_));
      indexenummap_.insert(IndexEnumerateMap::value_type(count_, *enumerate));
      enumerate++;
      count_++;
      t++;
    }
  }

  Enumerate(
    const E* enumerate,
    const T* text,
    const E& undefined,
    const R& enumrole,
    const R& textrole) :
    count_(0),
    undefined_(undefined),
    enumrole_(enumrole),
    textrole_(textrole),
    last_("Unknown"){
    while (text != nullptr && text->length() > 0) {
      enumvaluemap_.insert(EnumerateValueMap::value_type(*enumerate, *text));
      valueenummap_.insert(ValueEnumerateMap::value_type(*text, *enumerate));
      enumindexmap_.insert(EnumerateIndexMap::value_type(*enumerate, count_));
      indexenummap_.insert(IndexEnumerateMap::value_type(count_, *enumerate));
      enumerate++;
      count_++;
      text++;
    }
  }

  const int count() const {
    return count_;
  }

  QString toString(const E& enumerate) {
    EnumerateValueMap::iterator it = enumvaluemap_.find(enumerate);
    return (it != enumvaluemap_.end()) ?
      QString("%1").arg(it->second) : "Unknown";
  }
  T toValue(const E& enumerate) {
    EnumerateValueMap::iterator it = enumvaluemap_.find(enumerate);
    return (it != enumvaluemap_.end()) ? it->second : last_;
  }
  E parse(const QString& text) {
    ValueEnumerateMap::iterator it = valueenummap_.find(text);
    return (it != valueenummap_.end()) ? it->second : undefined_;
  }
  E fromValue(const T& value) {
    ValueEnumerateMap::iterator it = valueenummap_.find(value);
    return (it != valueenummap_.end()) ? it->second : undefined_;
  }
  int index(const E& enumerate) {
    EnumerateIndexMap::iterator it = enumindexmap_.find(enumerate);
    return (it != enumindexmap_.end()) ? it->second : -1;
  }
  int indexFromString(const QString& text) {
    E e = parse(text);
    return index(e);
  }
  int indexFromValue(const T& value) {
    E e = fromValue(value);
    return index(e);
  }
  E enumerate(const int& index) {
    IndexEnumerateMap::iterator it = indexenummap_.find(index);
    return (it != indexenummap_.end()) ? it->second : undefined_;
  }
  T valueFromIndex(const int& index) {
    E e = enumerate(index);
    return toValue(e);
  }

  QVariant data(const QModelIndex& index, int role) {
    E e = enumerate(index.row());
    if (e != undefined_) {
      if (role == enumrole_) {
        return QVariant::fromValue(e);
      } else if (role == textrole_) {
        return toString(e);
      } else if (role == valuerole_) {
        return toValue(e);
      }
    }
    return QVariant();
  }

private:
  typedef ::std::map<E, T> EnumerateValueMap;
  typedef ::std::map<T, E> ValueEnumerateMap;
  typedef ::std::map<E, int> EnumerateIndexMap;
  typedef ::std::map<int, E> IndexEnumerateMap;

  int count_;
  EnumerateValueMap enumvaluemap_;
  ValueEnumerateMap valueenummap_;
  EnumerateIndexMap enumindexmap_;
  IndexEnumerateMap indexenummap_;

  E undefined_;
  R valuerole_;
  R enumrole_;
  R textrole_;
  T last_;
};


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
