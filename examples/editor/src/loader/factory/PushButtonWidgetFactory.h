#pragma once
#include <memory>
#include <QMap>
#include <functional>
#include "IMenuWidgetFactory.h"
#include "common/translators/IMenuWidgetTranslator.h"

namespace loader {
namespace factory {
class PushButtonWidgetFactory : public IMenuWidgetFactory{
public:
  PushButtonWidgetFactory();

  QWidget *create(QVector<std::pair<QString, QString>> &parametersVector,
      std::shared_ptr<common::ISceneController> scene);
private:
  QMap<QString, std::function<common::translators::IMenuWidgetTranslator*(QWidget* widget, QString value)>>
      mTranslatorTypes;
};
}
}


