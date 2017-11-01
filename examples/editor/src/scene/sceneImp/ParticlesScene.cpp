#include <QColor>
#include "scene/callbacks/Callbacks.h"
#include "ParticlesScene.h"
#include <scene/callbacks/StandardKeyboardEventHandler.h>
#include <scene/callbacks/StandardMouseEventHandler.h>

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

ParticlesScene::ParticlesScene(int argc, char** argv, QMap<QString, QVariant> varValues)
  : AScene(argc, argv, varValues) {
  init();
}

void ParticlesScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  /* Cursor texture */
  textureC = mEngine->storeTexture("textures/cursor/standard_blue.png");

  /* Cursor */
  mEngine->getCurrentScene()->setCursor(std::move(make_unique<Cursor>(mEngine.get(), textureC)));
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                                       glm::quat(),
                                                                       glm::radians(90.0),
                                                                       1.0,
                                                                       0.1,
                                                                       1000.0));

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

  mEventsHandler.push_back(std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  mEventsHandler.push_back(std::make_unique<scene::callbacks::StandardMouseEventHandler>(mEngine));

  /* Attach emiters to entities */
  auto water = make_unique<EmiterPointCPU>(mEngine.get(),
                                           0.3,
                                           60000.0,
                                           glm::vec4(0.1, 0.1, 1.0, 1.0),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.9, 0.9, 0.9),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           10.0,
                                           10.0,
                                           mEngine->storeTexture("textures/particle.png"),
                                           GL_SRC_ALPHA,
                                           GL_ONE,
                                           GL_FALSE);
  water->moveBy(glm::vec3(0.0, -1.0, -1.0));

  auto sand = make_unique<EmiterPointCPU>(mEngine.get(),
                                          0.3,
                                          60000.0,
                                          glm::vec4(1.0, 1.0, 0.0, 1.0),
                                          glm::vec3(0.0, 2.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.9, 0.9, 0.9),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          10.0,
                                          10.0,
                                          mEngine->storeTexture("textures/particle.png"),
                                          GL_SRC_ALPHA,
                                          GL_ONE,
                                          GL_FALSE);

  auto snow = make_unique<EmiterPointGPU>(mEngine.get(),
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
                                          mEngine->storeTexture("textures/particle.png"),
                                          GL_SRC_ALPHA,
                                          GL_ONE,
                                          GL_FALSE);

  /* For time updates */

  //snow->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(snow.get(), FILLWAVE_ENDLESS));
  //water->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(water.get(), FILLWAVE_ENDLESS));
  //sand->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(sand.get(), FILLWAVE_ENDLESS));

  mWaterPtr = water.get();
  mSandPtr = sand.get();
  mEngine->getCurrentScene()->attach(std::move(sand));
  mEngine->getCurrentScene()->attach(std::move(water));
  //mEngine->getCurrentScene()->attach(std::move(snow));

  pText hint0 = mEngine->storeText("Particles", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
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

void ParticlesScene::perform() {
  QVariant a = mSceneParameters["mAcceleration"].value<int>();
  QVariant s = mSceneParameters["mSpeed"];
  QVariant rp = mSceneParameters["mRP"];
  QVariant rv = mSceneParameters["mRV"];
  auto wc = mSceneParameters["mWaterColor"].value<QColor>();
  auto sc = mSceneParameters["mSandColor"].value<QColor>();

  mEngine->detach(mSandPtr);
  auto sand = make_unique<EmiterPointCPU>(mEngine.get(),
                                          0.3,
                                          60000.0,
                                          glm::vec4(sc.redF(), sc.greenF(), sc.blueF(), sc.alphaF()),
                                          glm::vec3(0.0, 2.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.9, 0.9, 0.9),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          10.0,
                                          10.0,
                                          mEngine->storeTexture("textures/particle.png"),
                                          GL_SRC_ALPHA,
                                          GL_ONE,
                                          GL_FALSE);
  mSandPtr = sand.get();
  //mSandPtr->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(sand.get(), FILLWAVE_ENDLESS));
  mEngine->getCurrentScene()->attach(std::move(sand));
}

}
