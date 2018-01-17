#pragma once

#include <utility>
#include <memory>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QVector>
#include <QObject>
#include <fillwave/Fillwave.h>
#include "scene/callbacks/IEventHandler.h"
#include "objects/SceneModel.h"

namespace scene {
class AScene : public QObject {
//TODO: Demonatrz property system
 public:
  AScene(int argc, char* const* argv, QMap<QString, QVariant> parametersMap)
    : mSceneParameters(parametersMap) {
    if (argv != nullptr) {
      mEngine = std::make_shared<flw::Engine>(argc, argv);
    }
  }

  virtual ~AScene() = default;

  virtual void init() = 0;

  virtual void perform() = 0;

  QMap<QString, QVariant> getParameters() {
    return mSceneParameters;
  };

  virtual void setParameters(QMap<QString, QVariant> parameters) {
    if (!mSceneParameters.contains(parameters.firstKey())) {
      return;
    }
    mSceneParameters[parameters.firstKey()] = parameters.first();
    perform();
  };

  std::shared_ptr<flw::Engine> getEngine() {
    return mEngine;
  };

  bool eventFilter(QObject* watched, QEvent* event) override {
    if (!mEventsHandler.empty()) {
      for (auto& mEvent : mEventsHandler) {
        mEvent->handle(event);
      }
    }
    return QObject::eventFilter(watched, event);
  }

 protected:
  std::shared_ptr<flw::Engine> mEngine;
  QMap<QString, QVariant> mSceneParameters;
  std::vector<std::unique_ptr<scene::callbacks::IEventHandler>> mEventsHandler;
};
}
