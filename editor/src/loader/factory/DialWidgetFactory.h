#pragma once

#include "IMenuWidgetFactory.h"

namespace loader {
namespace factory {

class DialWidgetFactory : public IMenuWidgetFactory {
public:
  QWidget *create(QVector<std::pair<QString, QString>> &parametersVector,
      std::shared_ptr<common::ISceneController> scene);
};
}
}

