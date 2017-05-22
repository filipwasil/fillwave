#include "SceneController.h"

namespace common {
SceneController::SceneController() {
}

SceneController::SceneController(std::shared_ptr<scene::AScene> scen)
    : mScene(scen) {
}

void SceneController::updateScenField(std::pair<QString, QVariant> menuElement) {
  QString elementName = menuElement.first;
  QVariant elementValue = menuElement.second;
  if (!elementValue.isValid()) {
    return;
  }
  QMap<QString, QVariant> parameter;
  parameter[elementName] = elementValue;
  if (!mScene) {
    return;
  }
  mScene->setProperty("sceneParameter", parameter);
}

void SceneController::addTranslator(translators::IMenuWidgetTranslator *translator) {
  mTranslators.push_back(translator);
  QObject::connect(translator, &translators::IMenuWidgetTranslator::updateScene, this, &SceneController::updateScenField);
  auto currentValue = translator->getCurrentValues();
  if (currentValue.first.isEmpty() || !currentValue.second.isValid()) {
    return;
  }
  updateScenField(currentValue);
}

void SceneController::deleteTranslators() {
  if (mTranslators.isEmpty()) {
    return;
  }
  qDeleteAll(mTranslators);
  mTranslators.clear();
}

void SceneController::registerNewScene(std::shared_ptr<scene::AScene> scen) {
  mScene = scen;
}

void SceneController::reInitSceneValues() {
  for (const auto translator : mTranslators) {
    updateScenField(translator->getCurrentValues());
  }
}

QMap<QString, QVariant> SceneController::getCurrentMenuValues() {
  QMap<QString, QVariant> values;
  for (const auto pairValue : mTranslators) {
    auto val = pairValue->getCurrentValues();
    values.insert(val.first, val.second);
  }
  return values;
}
}