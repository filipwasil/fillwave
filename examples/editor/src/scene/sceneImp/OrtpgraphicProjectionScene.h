#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class OrtpgraphicProjectionScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  OrtpgraphicProjectionScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~OrtpgraphicProjectionScene(){}

  void init() override;

  void perform() override;

private:
  flw::flf::ps<flw::flf::Text> mText;
  int mArgc;
  char **mArgv;
};

}
