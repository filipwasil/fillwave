#pragma once

#include <fillwave/Fillwave.h>
#include <memory>
#include "scene/AScene.h"

namespace scene {
class FullModelScene : public AScene {
 Q_OBJECT
  Q_PROPERTY(QMap sceneParameter
               READ getParameters
               WRITE
               setParameters)
 public:
  FullModelScene(int argc, char** argv, QMap<QString, QVariant> varValues);

  virtual ~FullModelScene() {
  }

  void init() override;

  void perform() override;

 private:
  flw::flf::ps<flw::flf::Text> mText;
  int mArgc;
  char** mArgv;
};

}
