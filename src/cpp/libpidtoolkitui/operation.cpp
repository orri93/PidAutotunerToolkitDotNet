#include <QStringList>

#include <gos/pid/ui/operation.h>

namespace gptut = ::gos::pid::toolkit::ui::types;

namespace gos {
namespace pid {
namespace toolkit {
namespace ui {
namespace model {
namespace operation {

static const QString Operations[] = { "Add", "Subtraction", "" };

static QStringList _list;

namespace to {
QString string(const gptut::operation& operation) {
  switch (operation) {
  case gptut::operation::add:
    return "Add";
  case gptut::operation::subtract:
    return "Subtract";
  default:
    return "Unknown";
  }
}
}

gptut::operation parse(const QString& text) {
  if (text.compare("add", Qt::CaseInsensitive) == 0) {
    return gptut::operation::add;
  } else if (text.compare("subtract", Qt::CaseInsensitive) == 0) {
    return gptut::operation::subtract;
  } else {
    return gptut::operation::undefined;
  }
}

int index(const gptut::operation& operation) {
  switch (operation) {
  case gptut::operation::add:
    return 0;
  case gptut::operation::subtract:
    return 1;
  default:
    return -1;
  }
}

gptut::operation operation(const int& index) {
  switch (index) {
  case 0:
    return gptut::operation::add;
  case 1:
    return gptut::operation::subtract;
  default:
    return gptut::operation::undefined;
  }
}

QVariant create() {
  const QString* operation = Operations;
  while (*operation != "") {
    _list.append(*operation);
    operation++;
  }
  return QVariant::fromValue(_list);
}

} // namespace operation
} // namespace model
} // namespace ui
} // namespace toolkit
} // namespace pid
} // namespace gos

