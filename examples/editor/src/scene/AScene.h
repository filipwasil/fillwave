#pragma once

#include <utility>
#include <memory>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QObject>
#include <fillwave/Fillwave.h>

namespace scene {
class AScene : public QObject {

public:
  AScene(int argc, char *const *argv, QMap<QString, QVariant> parametersMap) : mSceneParameters(parametersMap) {
      mEngine = std::make_shared<flw::Engine>(argc, argv);
  }

  virtual ~AScene() {
  }

  virtual void init() = 0;

  virtual void perform() = 0;

  QMap<QString, QVariant> getParameters() {
    return mSceneParameters;
  };

  void setParameters(QMap<QString, QVariant> parameters) {
    if (!mSceneParameters.contains(parameters.firstKey())) {
      return;
    }
    mSceneParameters[parameters.firstKey()] = parameters.first();
    perform();
  };

  std::shared_ptr<flw::Engine> getEngine() {
    return mEngine;
  };

protected:
  std::shared_ptr<flw::Engine> mEngine;
  QMap<QString, QVariant> mSceneParameters;
};
}
