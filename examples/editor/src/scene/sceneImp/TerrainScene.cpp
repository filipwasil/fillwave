#include "scene/callbacks/Callbacks.h"
#include "TerrainScene.h"
#include "scene/terrain/MountainConstructor.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

TerrainScene::TerrainScene(int argc, char **argv)
    : AScene(argc, argv) {
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
  /* Engine callbacks */
  mEngine->registerCallback(make_unique<TimeStopCallback>(mEngine.get()));
  mEngine->registerCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));
//	mEngine->registerCallback(make_unique<MoveCameraCallback>(
//	         mEngine, eEventType::eCursorPosition, 0.1,
//	         ContextGLFW::mWindow));

  mEngine->configureFPSCounter("fonts/Titania", glm::vec2(0.7, 0.9), 100.0);

  puMeshTerrain terrain = make_unique<MeshTerrain>(mEngine.get(),
                                                   ProgramLoader(mEngine.get()).getDefault(),
                                                   new MountainConstructor(),
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
  pText hint0 = mEngine->storeText("Fillwave example terrain", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
  pText hint5 = mEngine->storeText("Use mouse to move the camera", "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
  pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.80),
                                   70.0);
}

void TerrainScene::perform() {

}

}