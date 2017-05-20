#include "MenuWidgetTranslatorStandardValues.h"

namespace common {
namespace translators {
MenuWidgetTranslatorStandardValues::MenuWidgetTranslatorStandardValues(const QWidget *menuWidget)
    : mMenuWidget(menuWidget) {

}

void MenuWidgetTranslatorStandardValues::update() {
  if (!mMenuWidget) {
    return;
  }
  auto value = getCurrentValues();
  if (value.first.isEmpty() || !value.second.isValid()) {
    return;
  }
  emit updateScene(value);
}

std::pair<QString, QVariant> MenuWidgetTranslatorStandardValues::getCurrentValues() {
  QVariant name = mMenuWidget->property("objectName");
  QVariant value = QVariant(mMenuWidget->property("value"));
  if (!name.isValid() || !value.isValid()) {
    std::pair<QString, QVariant> empty;
    return empty;
  }
  std::pair<QString, QVariant> menuElementState = std::make_pair(name.toString(), value);
  return menuElementState;
}
}
}