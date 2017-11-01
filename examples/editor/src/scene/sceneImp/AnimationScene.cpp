#include <fillwave/space/Scene.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/loaders/ProgramLoader.h>
#include "AnimationScene.h"

using namespace flw;
using namespace flw::flf;

namespace scene {
AnimationScene::AnimationScene(int argc, char** argv, QMap<QString, QVariant> varValues)
  : AScene(argc, argv, varValues) {
  init();
}

AnimationScene::~AnimationScene() {

}

void AnimationScene::init() {
  mEngine->setCurrentScene(std::make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                                            glm::quat(),
                                                                            glm::radians(90.0),
                                                                            1.0,
                                                                            0.1,
                                                                            1000.0));

  auto beast
    = std::make_unique<Model>(mEngine.get(),
                              ProgramLoader(mEngine.get()).getProgram(EProgram::basicAnimated),
                              "animations/beast/beast.dae");
  beast->scaleTo(3.0f);
  beast->rotateByX(90.0f);
  beast->setActiveAnimation(0);

  mEngine->getCurrentScene()->attach(std::move(beast));

  animationFuncHandler = std::bind(&AnimationKeyboardCallback::perform, &(*mAnimationCallback), std::placeholders::_1);
  mEngine->attachHandler(std::move(animationFuncHandler), flw::flf::eEventType::key);

  mText = mEngine->storeText("Animation Scene", "FreeSans", glm::vec2(-0.95f, 0.95f), 50.0f);
}

void AnimationScene::perform() {
  QVariant tmp = mSceneParameters["mText"];
  std::string string = tmp.toString().toStdString();
  mText->editString(string);
}
}