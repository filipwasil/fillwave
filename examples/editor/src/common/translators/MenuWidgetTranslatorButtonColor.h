#pragma once

#include <QColor>
#include "MenuWidgetTranslatorStandardValues.h"

namespace common {
namespace translators {

class MenuWidgetTranslatorButtonColor : public MenuWidgetTranslatorStandardValues {
public:
  MenuWidgetTranslatorButtonColor(const QWidget *menuWidget, QString color);
  std::pair<QString, QVariant> getCurrentValues() override;

public slots:

  void update();

protected:
  bool getColor();
  QColor mLastColor;
};

}
}

