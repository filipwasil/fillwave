#include <fillwave/space/Scene.h>
#include <fillwave/models/EmiterPointGPU.h>
#include "EmptyScene.h"

using namespace flw;
using namespace flw::flf;

namespace scene {
EmptyScene::EmptyScene(int argc, char** argv, QMap<QString, QVariant> varValues)
  : AScene(argc, argv, varValues) {
  init();
}

EmptyScene::~EmptyScene() = default;

void EmptyScene::init() {

  mEngine->setCurrentScene(std::make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(std::make_unique<CameraPerspective>(glm::vec3(0.0, 1.0, 6.0),
                                                                            glm::quat(),
                                                                            glm::radians(120.0),
                                                                            1.0,
                                                                            0.1,
                                                                            1000.0));
  auto snow = std::make_unique<EmiterPointCPU>(mEngine.get(),
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
  mEngine->getCurrentScene()->attach(std::move(snow));

  mEngine->getCurrentScene()->setSkybox(std::make_unique<Skybox>(mEngine.get(),
                                                            mEngine->storeTexture3D(
                                                              "textures/skybox/defaultLevelEditor/skyBoxBlue.png",
                                                              "textures/skybox/defaultLevelEditor/skyBoxBlue.png",
                                                              "textures/skybox/defaultLevelEditor/skyBoxBlue.png",
                                                              "textures/skybox/defaultLevelEditor/skyBoxGray.png",
                                                              "textures/skybox/defaultLevelEditor/skyBoxBlue.png",
                                                              "textures/skybox/defaultLevelEditor/skyBoxBlue.png")));

  auto startTextVariant = mSceneParameters["mText"];
  mText = mEngine->storeText(startTextVariant.toString().toStdString(), "FreeSans", glm::vec2(-0.95f, 0.95f), 50.0f);
}

void EmptyScene::perform() {
  QVariant tmp = mSceneParameters["mText"];
  std::string string = tmp.toString().toStdString();
  mText->editString(string);
}

}