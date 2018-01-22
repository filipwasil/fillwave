#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"
#include "scene/callbacks/AnimationKeyboardCallback.h"

namespace scene {
class AnimationScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  AnimationScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~AnimationScene();

  void init() override;

  void perform() override;

private:
  flw::ps<flw::flf::Text> mText;
  int mArgc;
  char **mArgv;
  std::unique_ptr<flw::flf::AnimationKeyboardCallback> mAnimationCallback;
  std::function<void(const flw::flf::Event&)> animationFuncHandler;
};

}
