#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/models/EmiterPointCPU.h>
#include "scene/AScene.h"

namespace scene {

class EmptyScene : public AScene {
 Q_OBJECT
  Q_PROPERTY(QMap sceneParameter
               READ
               getParameters
               WRITE
               setParameters)
 public:
  EmptyScene(int argc, char** argv, QMap<QString, QVariant> varValues);

  ~EmptyScene() override;

  void init() override;

  void perform() override;

 private:
  flw::flf::ps<flw::flf::Text> mText;
};

}



