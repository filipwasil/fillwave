#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class CallbacksScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  CallbacksScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~CallbacksScene() {
    // nothing
  }

  void init() override;

  void perform() override;

private:
  flw::ps<flw::flf::Text> mText;
};

}
