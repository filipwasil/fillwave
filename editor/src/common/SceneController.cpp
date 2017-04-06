#include "SceneController.h"

namespace common {
SceneController::SceneController() {
}

SceneController::SceneController(std::shared_ptr<scene::AScene> scen)
    : mScene(scen) {
}

void SceneController::updateScenField(QWidget *menuElement) {
  QVariant elementName = menuElement->property("objectName");
  QVariant elementValue = getValue(menuElement);
  if (!elementName.isValid() || !elementValue.isValid()) {
    return;
  }
  QMap<QString, QVariant> parameter;
  parameter[elementName.toString()] = elementValue;
  if (!mScene) {
    return;
  }
  mScene->setProperty("sceneParameter", parameter);
}

QVariant SceneController::getValue(const QWidget *menuElement) const {
  const QMetaObject *metaobject = menuElement->metaObject();
  if (metaobject->indexOfProperty("value") != -1) {
    return menuElement->property("value");
  } else if (metaobject->indexOfProperty("text") != -1) {
    return menuElement->property("text");
  }
  return QVariant();
}

void SceneController::addTranslator(MenuWidgetTranslator *translator) {
  mTranslators.push_back(translator);
  QObject::connect(translator, &MenuWidgetTranslator::updateScene, this, &SceneController::updateScenField);
}

void SceneController::deleteTranslators() {
  qDeleteAll(mTranslators);
  mTranslators.clear();
}

void SceneController::registerNewScene(std::shared_ptr<scene::AScene> scen) {
  mScene = scen;
}

}