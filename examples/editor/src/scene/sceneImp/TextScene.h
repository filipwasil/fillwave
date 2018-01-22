#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/models/EmiterPointCPU.h>
#include "fillwave/common/Aliases.h"
#include "scene/AScene.h"

namespace scene {
class TextScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  TextScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  ~TextScene() override;

  void init() override;

  void perform() override;

private:
  flw::ps<flw::flf::Text> mText;
};

}



