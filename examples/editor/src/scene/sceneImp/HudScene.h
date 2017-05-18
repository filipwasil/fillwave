#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class HudScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  HudScene(int argc, char **argv);

  virtual ~HudScene();

  void init() override;

  void perform() override;

private:
  flw::pText mText;
  int mArgc;
  char **mArgv;
};

}
