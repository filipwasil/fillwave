#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class ShadowScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  ShadowScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  ~ShadowScene() override = default;

  void init() override;

  void perform() override;

private:
  flw::flf::ps<flw::flf::Text> mText;
  int mArgc;
  char **mArgv;
  flw::flf::LightSpot* mFirstLigth;
  flw::flf::LightSpot* mSecomdLigth;
  flw::flf::LightSpot* mThirdLigth;
};

}
