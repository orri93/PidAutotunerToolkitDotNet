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

template<typename E, typename R> class Enumerate {
public:
  Enumerate(
    const E* enumerate,
    const QString* text,
    const E& undefined,
    const R& valuerole,
    const R& textrole) :
    count_(0),
    undefined_(undefined),
    valuerole_(valuerole),
    textrole_(textrole) {
    while (text != nullptr && text->length() > 0) {
      enumtextmap_.insert(EnumerateTextMap::value_type(*enumerate, *text));
      textenummap_.insert(TextEnumerateMap::value_type(*text, *enumerate));
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
    EnumerateTextMap::iterator it = enumtextmap_.find(enumerate);
    return (it != enumtextmap_.end()) ? it->second : "Unknown";
  }
  E parse(const QString& text) {
    TextEnumerateMap::iterator it = textenummap_.find(text);
    return (it != textenummap_.end()) ? it->second : undefined_;
  }
  int index(const E& enumerate) {
    EnumerateIndexMap::iterator it = enumindexmap_.find(enumerate);
    return (it != enumindexmap_.end()) ? it->second : -1;
  }
  E enumerate(const int& index) {
    IndexEnumerateMap::iterator it = indexenummap_.find(index);
    return (it != indexenummap_.end()) ? it->second : undefined_;
  }

  QVariant data(const QModelIndex& index, int role) {
    E e = enumerate(index.row());
    if (e != undefined_) {
      if (role == valuerole_) {
        return QVariant::fromValue(e);
      } else if (role == textrole_) {
        return toString(e);
      }
    }
    return QVariant();
  }

private:
  typedef ::std::map<E, QString> EnumerateTextMap;
  typedef ::std::map<QString, E> TextEnumerateMap;
  typedef ::std::map<E, int> EnumerateIndexMap;
  typedef ::std::map<int, E> IndexEnumerateMap;

  int count_;
  EnumerateTextMap enumtextmap_;
  TextEnumerateMap textenummap_;
  EnumerateIndexMap enumindexmap_;
  IndexEnumerateMap indexenummap_;

  E undefined_;
  R valuerole_;
  R textrole_;
};


} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
