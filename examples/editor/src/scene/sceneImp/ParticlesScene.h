#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class ParticlesScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  ParticlesScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~ParticlesScene(){}

  void init() override;

  void perform() override;

private:
  flw::pText mText;
  int mArgc;
  char **mArgv;
};

}
