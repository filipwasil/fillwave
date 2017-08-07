#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {
class TextScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  TextScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~TextScene();

  void init() override;

  void perform() override;

private:
  flw::pText mText;
};

}



