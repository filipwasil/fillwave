#include <QColorDialog>
#include "MenuWidgetTranslatorButtonColor.h"

namespace common {
namespace translators {
MenuWidgetTranslatorButtonColor::MenuWidgetTranslatorButtonColor(const QWidget *menuWidget, QString color)
    : MenuWidgetTranslatorStandardValues(menuWidget) {
  auto vecColor = color.splitRef("_");
  mLastColor.setRedF(vecColor[0].toFloat());
  mLastColor.setGreenF(vecColor[1].toFloat());
  mLastColor.setBlue(vecColor[2].toFloat());
  mLastColor.setAlphaF(vecColor[3].toFloat());
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