#pragma once

#include <flw/Fillwave.h>
#include <flw/flf/models/EmiterPointCPU.h>
#include "scene/AScene.h"

namespace scene {

class EmptyScene : public AScene {
 Q_OBJECT
 public:
  EmptyScene(int argc, char** argv);

  ~EmptyScene() override;

  void init() override;

  void perform() override;

 private:
  std::shared_ptr<flw::flf::Text> mText;
};

}



