#pragma once

#include <QWidget>
#include <QMap>
#include <common/ISceneController.h>
#include <memory>
#include "factory/IMenuWidgetFactory.h"
#include "common/ISceneController.h"
#include "loader/IWidgetFabric.h"

namespace loader {
class MenuWidgetFabric : public IWidgetFabric {
public:
  MenuWidgetFabric(std::shared_ptr<common::ISceneController> scene);

  ~MenuWidgetFabric();

  QWidget *createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector);

private:
  QMap<QString, factory::IMenuWidgetFactory *> mFabricMap;
  std::shared_ptr<common::ISceneController> mScene;
};

}
