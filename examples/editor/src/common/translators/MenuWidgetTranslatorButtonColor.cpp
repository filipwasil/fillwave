#include <QColorDialog>
#include "MenuWidgetTranslatorButtonColor.h"

namespace common {
namespace translators {
MenuWidgetTranslatorButtonColor::MenuWidgetTranslatorButtonColor(const QWidget *menuWidget, QString color)
    : MenuWidgetTranslatorStandardValues(menuWidget),
      mLastRGBValue(color) {
}

void MenuWidgetTranslatorButtonColor::update() {
  if (!mMenuWidget) {
    return;
  }
  auto valueColor = getColor();
  if (valueColor.isEmpty()) {
    return;
  }
  mLastRGBValue = valueColor;
  auto value = getCurrentValues();
  emit updateScene(value);
}

QString MenuWidgetTranslatorButtonColor::getColor() {
  QColorDialog colorDialog;
  int status = colorDialog.exec();
  if (status == QDialog::DialogCode::Rejected) {
    QString empty;
    return empty;
  }
  auto color = colorDialog.currentColor();
  auto red = color.red();
  auto green = color.green();
  auto blue = color.blue();
  QString rgb = QString::number(red) + "_";
  rgb.append(QString::number(green));
  rgb.append("_");
  rgb.append(QString::number(blue));
  return rgb;
}

std::pair<QString, QVariant> MenuWidgetTranslatorButtonColor::getCurrentValues() {
  QVariant name = mMenuWidget->property("objectName");
  if (!name.isValid()) {
    std::pair<QString, QVariant> empty;
    return empty;
  }
  std::pair<QString, QVariant> elementValue = std::make_pair(name.toString(), QVariant(mLastRGBValue));
  return elementValue;
}


}
}