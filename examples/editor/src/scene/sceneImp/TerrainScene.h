#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"

namespace scene {

class TerrainScene : public AScene {
Q_OBJECT
  Q_PROPERTY(QMap sceneParameter
                 READ
                 getParameters
                 WRITE
                 setParameters)
public:
  TerrainScene(int argc, char **argv);

  virtual ~TerrainScene() {
  }

  void init() override;

  void perform() override;

private:
  flw::pText mText;
};

}



