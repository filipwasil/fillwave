#pragma once

#include <QColor>
#include <QHash>
#include "MenuWidgetTranslatorStandardValues.h"

namespace common {
namespace translators {

class MenuWidgetTranslatorButtonColor : public MenuWidgetTranslatorStandardValues {
public:
  MenuWidgetTranslatorButtonColor(const QWidget *menuWidget, QHash<QString, float> defaultValues);
  std::pair<QString, QVariant> getCurrentValues() override;

public slots:

  void update();

protected:
  bool getColor();
  QColor mLastColor;
};

}
}

