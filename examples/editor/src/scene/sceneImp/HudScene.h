#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class HudScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  HudScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  ~HudScene() override = default;

  void init() override;

  void perform() override;

private:
  flw::flf::ps<flw::flf::Text> mText;
  int mArgc;
  char **mArgv;
};

}
