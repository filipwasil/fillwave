#include <QColorDialog>
#include "MenuWidgetTranslatorButtonColor.h"

namespace common {
namespace translators {
MenuWidgetTranslatorButtonColor::MenuWidgetTranslatorButtonColor(const QWidget *menuWidget,
    QHash<QString, float> defaultValues)
    : MenuWidgetTranslatorStandardValues(menuWidget) {
  mLastColor.setRedF(defaultValues["Red"]);
  mLastColor.setGreenF(defaultValues["Green"]);
  mLastColor.setBlue(defaultValues["Blue"]);
  mLastColor.setAlphaF(defaultValues["Alpha"]);
}

void MenuWidgetTranslatorButtonColor::update() {
  if (!mMenuWidget) {
    return;
  }
  auto valueColor = getColor();
  if (!valueColor) {
    return;
  }
  auto value = getCurrentValues();
  emit updateScene(value);
}

bool MenuWidgetTranslatorButtonColor::getColor() {
  QColorDialog colorDialog;
  int status = colorDialog.exec();
  if (status == QDialog::DialogCode::Rejected) {
    return false;
  }
  mLastColor = colorDialog.currentColor();
  return true;
}

std::pair<QString, QVariant> MenuWidgetTranslatorButtonColor::getCurrentValues() {
  QVariant name = mMenuWidget->property("objectName");
  if (!name.isValid()) {
    std::pair<QString, QVariant> empty;
    return empty;
  }
  std::pair<QString, QVariant> elementValue = std::make_pair(name.toString(), QVariant(mLastColor));
  return elementValue;
}

}
}