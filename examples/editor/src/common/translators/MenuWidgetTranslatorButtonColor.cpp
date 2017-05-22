#include <QColorDialog>
#include "MenuWidgetTranslatorButtonColor.h"

namespace common {
namespace translators {
MenuWidgetTranslatorButtonColor::MenuWidgetTranslatorButtonColor(const QWidget *menuWidget, QString color)
    : MenuWidgetTranslatorStandardValues(menuWidget) {
  auto vecColor = color.splitRef("_");
  mLastRGBValue["Red"] = QVariant(vecColor[0].toFloat());
  mLastRGBValue["Green"] = QVariant(vecColor[1].toFloat());
  mLastRGBValue["Blue"] = QVariant(vecColor[2].toFloat());
  mLastRGBValue["Alpha"] = QVariant(vecColor[3].toFloat());
}

void MenuWidgetTranslatorButtonColor::update() {
  if (!mMenuWidget) {
    return;
  }
  auto valueColor = getColor();
  if (valueColor.isEmpty()) {
    return;
  }
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
  QVector<qreal> colors;
  auto color = colorDialog.currentColor();
  mLastRGBValue["Red"] = QVariant(color.redF());
  mLastRGBValue["Green"] = QVariant(color.greenF());
  mLastRGBValue["Blue"] = QVariant(color.blueF());
  mLastRGBValue["Alpha"] = QVariant(color.alphaF());
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