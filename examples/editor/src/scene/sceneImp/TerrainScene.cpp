#include "scene/callbacks/Callbacks.h"
#include "TerrainScene.h"
#include "scene/terrain/PerlinConstructor.h"
#include <scene/callbacks/StandardKeyboardEventHandler.h>
#include <scene/callbacks/StandardMouseEventHandler.h>

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

TerrainScene::TerrainScene(int argc, char **argv, QMap<QString, QVariant> varValues)
    : AScene(argc, argv, varValues) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

void TerrainScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 4.0, 16.0),
                                                                       glm::quat(),
                                                                       glm::radians(90.0),
                                                                       1.0,
                                                                       0.1,
                                                                       1000.0));

  /* Lights */
  auto light = mEngine->storeLightSpot(glm::vec3(1.0, 20.0, 6.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0));
  light->rotateTo(glm::vec3(1.0, 0.0, 0.0), glm::radians(-90.0));

  /* Engine callbacks */
  mTimeCallback = std::make_unique<TimeStopCallback>(mEngine.get());
  mCameraCallback = std::make_unique<MoveCameraCallback>(mEngine.get(), 0.1);
  mSecondCameraCallback = std::make_unique<FollowCustomCursorCallback>(mEngine.get());
  std::function<void(const flf::Event&)> timeFuncHandler = std::bind(&TimeStopCallback::perform,
                                                                     &(*mTimeCallback),
                                                                     std::placeholders::_1);
  std::function<void(const flf::Event&)> cameraFuncHandler = std::bind(&MoveCameraCallback::perform,
                                                                       &(*mCameraCallback),
                                                                       std::placeholders::_1);
  std::function<void(const flf::Event&)> secondCameraFuncHandler = std::bind(&FollowCustomCursorCallback::perform,
                                                                             &(*mSecondCameraCallback),
                                                                             std::placeholders::_1);
  mEngine->attachHandler(std::move(timeFuncHandler), flw::flf::eEventType::key);
  mEngine->attachHandler(std::move(cameraFuncHandler), flw::flf::eEventType::key);
  mEngine->attachHandler(std::move(secondCameraFuncHandler), flw::flf::eEventType::cursorPosition);

  mEventsHandler.push_back(
      std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  mEventsHandler.push_back(
      std::make_unique<scene::callbacks::StandardMouseEventHandler>(mEngine));

  mEngine->configFPSCounter("fonts/Titania", glm::vec2(0.7, 0.9), 100.0);

  auto terrain = make_unique<MeshTerrain>(mEngine.get(),
                                                   ProgramLoader(mEngine.get()).getProgram(EProgram::basic),
                                                   new PerlinConstructor(),
                                                   Material(),
                                                   "textures/test.png",
                                                   "textures/testNormal.png",
                                                   "",
                                                   20,
                                                   16);
  terrain->scaleTo(1.0);
  terrain->addEffect(make_shared<Fog>());
  mEngine->getCurrentScene()->attach(std::move(terrain));

  /* Description */
  mEngine->storeText("Terrain example", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
  mEngine->storeText("To move the camera push rigth mouse button and move", "fonts/Titania",
                     glm::vec2(-0.95, -0.40), 70.0);
  mEngine->storeText("'S' camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  mEngine->storeText("'W' camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  mEngine->storeText("'T' resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  mEngine->storeText("'D' debugger On/Off", "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}

void TerrainScene::perform() {

}

}