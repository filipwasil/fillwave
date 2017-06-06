#pragma once
#include <memory>
#include <QMap>
#include <functional>
#include "IMenuWidgetFactory.h"
#include "common/translators/IMenuWidgetTranslator.h"

namespace loader {
namespace factory {
class ColorPushButtonWidgetFactory : public IMenuWidgetFactory{
public:
  QWidget *create(QVector<std::pair<QString, QString>> &parametersVector,
      std::shared_ptr<common::ISceneController> scene);
};
}
}


