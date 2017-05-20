#pragma once

#include <QWidget>
#include "IMenuWidgetTranslator.h"

namespace common {
namespace translators {
class MenuWidgetTranslatorStandardValues : public IMenuWidgetTranslator {
Q_OBJECT
public:
  MenuWidgetTranslatorStandardValues(const QWidget *menuWidget);

  std::pair<QString, QVariant> getCurrentValues() override;

public slots:

  void update();

protected:
  const QWidget *mMenuWidget;
};
}
}