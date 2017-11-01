#include "CursorScene.h"
#include "scene/callbacks/StandardKeyboardEventHandler.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

CursorScene::CursorScene(int argc, char** argv, QMap<QString, QVariant> varValues)
  : AScene(argc, argv, varValues) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

void CursorScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

  /* Engine callbacks */
  mTimeCallback = std::make_unique<TimeStopCallback>(mEngine.get());
  mCameraCallback = std::make_unique<MoveCameraCallback>(mEngine.get(), 0.1);
  mCustomCursorCallback = std::make_unique<FollowCustomCursorCallback>(mEngine.get());
  std::function<void(const flf::Event&)> timeFuncHandler = std::bind(&TimeStopCallback::perform,
                                                                     &(*mTimeCallback),
                                                                     std::placeholders::_1);
  std::function<void(const flf::Event&)> cameraFuncHandler = std::bind(&MoveCameraCallback::perform,
                                                                       &(*mCameraCallback),
                                                                       std::placeholders::_1);
  mEngine->attachHandler(std::move(timeFuncHandler), flw::flf::eEventType::key);
  mEngine->attachHandler(std::move(cameraFuncHandler), flw::flf::eEventType::key);
  mEventsHandler.push_back(std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  /* Cursor texture */
  flc::Texture2D* textureC = mEngine->storeTexture("textures/cursor/standard_blue.png");

  /* Cursor */
  mEngine->getCurrentScene()->setCursor(make_unique<Cursor>(mEngine.get(), textureC));

  /* Make cursor visible for current scene */
  std::function<void(const flf::Event &)> customCursorFuncHandler = std::bind(&FollowCustomCursorCallback::perform,
                                                                              &(*mCustomCursorCallback),
                                                                              std::placeholders::_1);
  mEngine->attachHandler(std::move(customCursorFuncHandler), flw::flf::eEventType::custom);

  /* Description */
  pText description = mEngine->storeText("Fillwave example cursor", "fonts/Titania", glm::vec2(-0.95, 0.95), 100.0);
  pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.80),
                                   70.0);
}

void CursorScene::perform() {

}

}
