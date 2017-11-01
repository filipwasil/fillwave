#include "SkyboxScene.h"
#include "scene/callbacks/StandardKeyboardEventHandler.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

SkyboxScene::SkyboxScene(int argc, char** argv, QMap<QString, QVariant> varValues)
  : AScene(argc, argv, varValues) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

void SkyboxScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
                                                                       glm::quat(),
                                                                       glm::radians(90.0),
                                                                       1.0,
                                                                       0.1,
                                                                       1000.0));
  mTimeCallback = std::make_unique<TimeStopCallback>(mEngine.get());
  mCameraCallback = std::make_unique<MoveCameraCallback>(mEngine.get(), 0.1);
  mSecondCameraCallback = std::make_unique<FollowCustomCursorCallback>(mEngine.get());
  /* Engine callbacks */
  prepareStandardCallbacks();
  mEventsHandler.push_back(std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  mEventsHandler.push_back(std::make_unique<scene::callbacks::StandardMouseEventHandler>(mEngine));

  mEngine->getCurrentScene()->setSkybox(make_unique<Skybox>(mEngine.get(),
                                                            mEngine->storeTexture3D(
                                                              "textures/skybox/emerald/emerald_right.jpg",
                                                              "textures/skybox/emerald/emerald_left.jpg",
                                                              "textures/skybox/emerald/emerald_top.jpg",
                                                              "",
                                                              "textures/skybox/emerald/emerald_front.jpg",
                                                              "textures/skybox/emerald/emerald_back.jpg")));
  pText hint0 = mEngine->storeText("Fillwave example skybox", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
  pText hint5 = mEngine->storeText("To move the camera push rigth mouse button and move",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.40),
                                   70.0);
  pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.80),
                                   70.0);
}

void SkyboxScene::perform() {

}

}