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

namespace scene {
class AScene : public QObject {
 public:
  AScene(int argc, char* const* argv) {
    if (argv != nullptr) {
      mEngine = std::make_shared<flw::EnginePC>(argc, argv);
    }
  }

  virtual ~AScene() = default;

  virtual void init() = 0;

  virtual void perform() = 0;

  std::shared_ptr<flw::Engine> getEngine() {
    return mEngine;
  };

 protected:
  std::shared_ptr<flw::Engine> mEngine;
  std::vector<std::unique_ptr<scene::callbacks::IEventHandler>> mEventsHandler;
};
}
