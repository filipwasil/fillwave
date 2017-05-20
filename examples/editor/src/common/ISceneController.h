#pragma once

#include <QWidget>
#include <QVariant>
#include <utility>
#include <common/translators/MenuWidgetTranslatorStandardValues.h>
#include "scene/AScene.h"

namespace common {
class ISceneController : public QObject {
public:
  virtual ~ISceneController() {
  }

  virtual void addTranslator(translators::IMenuWidgetTranslator *translator) = 0;

  virtual void deleteTranslators() = 0;

  virtual void registerNewScene(std::shared_ptr<scene::AScene> scen) = 0;

public slots:

  virtual void updateScenField(std::pair<QString, QVariant> menuElement) = 0;
};
}

