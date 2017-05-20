#include "MenuWidgetTranslatorLineEdit.h"

namespace common {
namespace translators {
MenuWidgetTranslatorLineEdit::MenuWidgetTranslatorLineEdit(const QWidget *widget)
    : MenuWidgetTranslatorStandardValues(widget) {
}

std::pair<QString, QVariant> MenuWidgetTranslatorLineEdit::getCurrentValues() {
  QVariant name = mMenuWidget->property("objectName");
  QVariant value = QVariant(mMenuWidget->property("text"));
  if (!name.isValid() || !value.isValid()) {
    std::pair<QString, QVariant> empty;
    return empty;
  }
  std::pair<QString, QVariant> menuElementState = std::make_pair(name.toString(), value);
  return menuElementState;
}
}
}