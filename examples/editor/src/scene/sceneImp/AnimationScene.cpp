#include <fillwave/space/Scene.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/actions/callbacks/TimedEmiterUpdateCallback.h>
#include "scene/callbacks/AnimationKeyboardCallback.h"
#include "AnimationScene.h"

using namespace flw;
using namespace flw::flf;

namespace scene {
AnimationScene::AnimationScene(int argc, char **argv) : AScene (argc, argv) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

AnimationScene::~AnimationScene() {

}

void AnimationScene::init() {
  mEngine = std::make_shared<flw::Engine>(mArgc, mArgv);
  mEngine->setCurrentScene(std::make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                                            glm::quat(),
                                                                            glm::radians(90.0),
                                                                            1.0,
                                                                            0.1,
                                                                            1000.0));

  auto beast = std::make_unique<Model>(mEngine.get(), ProgramLoader(mEngine.get()).getDefaultBones(),
                                  "animations/beast/beast.dae");
  beast->scaleTo(3.0f);
  beast->rotateByX(90.0f);
  beast->setActiveAnimation(0);
  mEngine->getCurrentScene()->attach(std::move(beast));

  mEngine->registerCallback(
      std::make_unique<AnimationKeyboardCallback>(beast.get(), eEventType::eKey),
      beast.get());

  puIEmiterPoint snow = std::make_unique<EmiterPointCPU>(mEngine.get(),
                                                         0.3,
                                                         600.0,
                                                         glm::vec4(1.0, 1.0, 1.0, 1.0),
                                                         glm::vec3(0.0, 1.0, 0.0),
                                                         glm::vec3(0.0, 0.0, 0.0),
                                                         glm::vec3(0.9, 0.9, 0.9),
                                                         glm::vec3(0.0, 0.0, 0.0),
                                                         glm::vec3(0.6, 0.6, 0.6),
                                                         1.0,
                                                         1.0,
                                                         mEngine->storeTexture("assets/alphaMask.png"),
                                                         GL_SRC_ALPHA,
                                                         GL_ONE,
                                                         GL_FALSE);

  snow->attachHierarchyCallback(std::make_unique<TimedEmiterUpdateCallback>(snow.get(), FILLWAVE_ENDLESS));

  mEngine->getCurrentScene()->attach(std::move(snow));

  mText = mEngine->storeText("Animation Scene", "FreeSans", glm::vec2(-0.95f, 0.95f), 50.0f);
}

void AnimationScene::perform() {
  QVariant tmp = mSceneParameters["mText"];
  std::string string = tmp.toString().toStdString();
  mText->editString(string);
}
}