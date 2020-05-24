#ifndef GOS_PID_TUNING_UI_MODEL_VALUE_H_
#define GOS_PID_TUNING_UI_MODEL_VALUE_H_

#include <map>

#include <QAbstractListModel>
#include <QString>

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {

template<typename T, typename R> class Value {
public:
  Value(
    const T& undefined,
    const R& valuerole,
    const R& textrole):
    count_(0),
    undefined_(undefined),
    valuerole_(valuerole),
    textrole_(textrole) {
  }

  Value(
    const T* value,
    const QString* text,
    const T& undefined,
    const R& valuerole,
    const R& textrole) :
    count_(0),
    undefined_(undefined),
    valuerole_(valuerole),
    textrole_(textrole) {
    while (text != nullptr && text->length() > 0) {
      enumtextmap_.insert(ValueTextMap::value_type(*value, *text));
      textenummap_.insert(TextValueMap::value_type(*text, *value));
      enumindexmap_.insert(ValueIndexMap::value_type(*value, count_));
      indexenummap_.insert(IndexValueMap::value_type(count_, *value));
      value++;
      count_++;
      text++;
    }
  }

  Value(
    const T* value,
    const T& undefined,
    const R& valuerole,
    const R& textrole) :
    count_(0),
    undefined_(undefined),
    valuerole_(valuerole),
    textrole_(textrole) {
    while (value != nullptr && *value != undefined) {
      QString text = QString("%1").arg(*value);
      enumtextmap_.insert(ValueTextMap::value_type(*value, text));
      textenummap_.insert(TextValueMap::value_type(text, *value));
      enumindexmap_.insert(ValueIndexMap::value_type(*value, count_));
      indexenummap_.insert(IndexValueMap::value_type(count_, *value));
      value++;
      count_++;
    }
  }

  void clear() {
    enumtextmap_.clear();
    textenummap_.clear();
    enumindexmap_.clear();
    indexenummap_.clear();
  }

  void add(const T& value) {
    QString text = QString("%1").arg(value);
    enumtextmap_.insert(ValueTextMap::value_type(value, text));
    textenummap_.insert(TextValueMap::value_type(text, value));
    enumindexmap_.insert(ValueIndexMap::value_type(value, count_));
    indexenummap_.insert(IndexValueMap::value_type(count_, value));
    count_++;
  }

  const int count() const {
    return count_;
  }

  QString toString(const T& value) {
    ValueTextMap::iterator it = enumtextmap_.find(value);
    return (it != enumtextmap_.end()) ? it->second : "Unknown";
  }
  T parse(const QString& text) {
    TextValueMap::iterator it = textenummap_.find(text);
    return (it != textenummap_.end()) ? it->second : undefined_;
  }
  int index(const T& value) {
    ValueIndexMap::iterator it = enumindexmap_.find(value);
    return (it != enumindexmap_.end()) ? it->second : -1;
  }
  T value(const int& index) {
    IndexValueMap::iterator it = indexenummap_.find(index);
    return (it != indexenummap_.end()) ? it->second : undefined_;
  }

  QVariant data(const QModelIndex& index, int role) {
    T v = value(index.row());
    if (v != undefined_) {
      if (role == valuerole_) {
        return QVariant::fromValue(v);
      } else if (role == textrole_) {
        return toString(v);
      }
    }
    return QVariant();
  }

  QVariant dataString(const QModelIndex& index, int role) {
    T v = value(index.row());
    if (v != undefined_) {
      if (role == valuerole_ || role == textrole_) {
        return v;
      }
    }
    return QVariant();
  }


private:
  typedef ::std::map<T, QString> ValueTextMap;
  typedef ::std::map<QString, T> TextValueMap;
  typedef ::std::map<T, int> ValueIndexMap;
  typedef ::std::map<int, T> IndexValueMap;

  int count_;
  ValueTextMap enumtextmap_;
  TextValueMap textenummap_;
  ValueIndexMap enumindexmap_;
  IndexValueMap indexenummap_;

  T undefined_;
  R valuerole_;
  R textrole_;
};


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
