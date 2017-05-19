#include <fillwave/space/Scene.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/actions/callbacks/TimedEmiterUpdateCallback.h>
#include <fillwave/Fillwave.h>
#include "TextScene.h"

using namespace flw;
using namespace flw::flf;

namespace scene {
TextScene::TextScene(int argc, char **argv)
    : AScene(argc, argv) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

TextScene::~TextScene() {

}

void TextScene::init() {
  mEngine->setCurrentScene(std::make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                                            glm::quat(),
                                                                            glm::radians(90.0),
                                                                            1.0,
                                                                            0.1,
                                                                            1000.0));
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

  mText = mEngine->storeText("Fillwave editor", "FreeSans", glm::vec2(-0.95f, 0.95f), 50.0f);
}

void TextScene::perform() {
  QVariant tmp = mSceneParameters["mText"];
  std::string string = tmp.toString().toStdString();
  mText->editString(string);
}

}