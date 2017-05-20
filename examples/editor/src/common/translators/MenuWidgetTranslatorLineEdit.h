#pragma once

#include "MenuWidgetTranslatorStandardValues.h"

namespace common {
namespace translators {
class MenuWidgetTranslatorLineEdit : public MenuWidgetTranslatorStandardValues {
public:
  MenuWidgetTranslatorLineEdit(const QWidget *widget);

  std::pair<QString, QVariant> getCurrentValues() override;
};
}
}