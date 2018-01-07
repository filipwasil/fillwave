#include <memory>
#include <common/ISceneController.h>
#include "MenuWidgetFabric.h"
#include "factory/SliderWidgetFactory.h"
#include "factory/DialWidgetFactory.h"
#include "factory/LineEditWidgetFactory.h"
#include "factory/ColorPushButtonWidgetFactory.h"

namespace loader {
MenuWidgetFabric::MenuWidgetFabric(std::shared_ptr<common::ISceneController> scene)
    : mScene(scene) {
  mFabricMap["QSlider"] = new factory::SliderWidgetFactory();
  mFabricMap["QDial"] = new factory::DialWidgetFactory();
  mFabricMap["QLineEdit"] = new factory::LineEditWidgetFactory();
  mFabricMap["ColorQPushButton"] = new factory::ColorPushButtonWidgetFactory();
}

MenuWidgetFabric::~MenuWidgetFabric() {
  qDeleteAll(mFabricMap);
  mFabricMap.clear();
}

QWidget *MenuWidgetFabric::createWidget(QString typeName, QVector<std::pair<QString, QString>> &parametersVector) {
  if (!mFabricMap.contains(typeName)) {
    return nullptr;
  }
  auto factory = mFabricMap[typeName];
  return factory->create(parametersVector, mScene);
}
}