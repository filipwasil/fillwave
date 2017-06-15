#pragma once

#include <memory>
#include <fillwave/Fillwave.h>
#include <QtCore/QEvent>
#include "IEventHandler.h"
#include "common/SceneEventFactory.h"

namespace scene {
namespace callbacks {
class StandardKeyboardEventHandler : public IEventHandler {
public:
  StandardKeyboardEventHandler(const std::shared_ptr<flw::Engine> &engine);

  void handle(QEvent *event) override;

private:
  std::shared_ptr<flw::Engine> mEngine;
  common::SceneEventFactory mEventFactory;
};
}
}

