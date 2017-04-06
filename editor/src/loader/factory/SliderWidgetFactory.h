#pragma once

#include <memory>
#include "IMenuWidgetFactory.h"

namespace loader {
namespace factory {
class SliderWidgetFactory : public IMenuWidgetFactory {
public:
  QWidget *create(QVector<std::pair<QString, QString>> &parametersVector,
      std::shared_ptr<common::ISceneController> scene);
};
}
}

