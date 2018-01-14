#include "PickingScene.h"
#include "scene/objects/PickableModel.h"
#include "scene/callbacks/StandardKeyboardEventHandler.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

PickingScene::PickingScene(int argc, char **argv, QMap<QString, QVariant> varValues)
    : AScene(argc, argv, varValues) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

void PickingScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());
/* Engine callbacks */
  mTimeCallback = std::make_unique<TimeStopCallback>(mEngine.get());
  mCameraCallback = std::make_unique<MoveCameraCallback>(mEngine.get(), 0.1);
  mCustomCursorCallback = std::make_unique<FollowCustomCursorCallback>(mEngine.get());
  mColorCallback = std::make_unique<ColorPickingCallback>(mEngine.get());

  std::function<void(const flf::Event &)> timeFuncHandler = std::bind(&TimeStopCallback::perform,
                                                                      &(*mTimeCallback),
                                                                      std::placeholders::_1);
  std::function<void(const flf::Event &)> cameraFuncHandler = std::bind(&MoveCameraCallback::perform,
                                                                        &(*mCameraCallback),
                                                                        std::placeholders::_1);
  mEngine->attachHandler(std::move(timeFuncHandler), flw::flf::eEventType::key);
  mEngine->attachHandler(std::move(cameraFuncHandler), flw::flf::eEventType::key);
  mEventsHandler.push_back(std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  mEngine->getCurrentScene()->setCursor(make_unique<Cursor>(mEngine.get(),
                                                            mEngine->storeTexture("textures/cursor/standard_blue.png")));

  /* Make cursor visible for current scene */
  std::function<void(const flf::Event &)> customCursorFuncHandler = std::bind(&FollowCustomCursorCallback::perform,
                                                                              &(*mCustomCursorCallback),
                                                                              std::placeholders::_1);
  mEngine->attachHandler(std::move(customCursorFuncHandler), flw::flf::eEventType::custom);

  /* Picking info text which will be modified frequently */
  flw::flf::ps<flw::flf::Text> pickInfo = mEngine->storeText("Nothing picked", "fonts/Titania", glm::vec2(-0.95, 0.80), 60.0);

  auto program = ProgramLoader(mEngine.get()).getProgram(EProgram::basic);

  /* build ball model */
  puModel ballModel1 = make_unique<PickableModel>("left ball",
                                                  pickInfo,
                                                  mEngine.get(),
                                                  program,
                                                  "meshes/sphere.obj",
                                                  "64_128_255.checkboard");
  ballModel1->scaleTo(0.1);
  ballModel1->moveBy(glm::vec3(-3.0, 0.0, 0.0));
  puModel ballModel2 = make_unique<PickableModel>("right ball",
                                                  pickInfo,
                                                  mEngine.get(),
                                                  program,
                                                  "meshes/sphere.obj",
                                                  "64_128_255.checkboard");
  ballModel2->scaleTo(0.1);
  ballModel2->moveBy(glm::vec3(3.0, 0.0, 0.0));
  puModel ballModel3 = make_unique<PickableModel>("center ball",
                                                  pickInfo,
                                                  mEngine.get(),
                                                  program,
                                                  "meshes/sphere.obj",
                                                  "64_128_255.checkboard");
  ballModel3->scaleTo(0.1);
  puModel ballModel4 = make_unique<PickableModel>("up ball",
                                                  pickInfo,
                                                  mEngine.get(),
                                                  program,
                                                  "meshes/sphere.obj",
                                                  "64_128_255.checkboard");
  ballModel4->scaleTo(0.1);
  ballModel4->moveBy(glm::vec3(0.0, 3.0, 0.0));
  puModel ballModel5 = make_unique<PickableModel>("down ball",
                                                  pickInfo,
                                                  mEngine.get(),
                                                  program,
                                                  "meshes/sphere.obj",
                                                  "64_128_255.checkboard");
  ballModel5->scaleTo(0.1);
  ballModel5->moveBy(glm::vec3(0.0, -3.0, 0.0));

  /* Register ball model as a pickable model in scene */
  mEngine->getCurrentScene()->registerPickable(ballModel1.get()); // xxx is register pickable safe ?
  mEngine->getCurrentScene()->registerPickable(ballModel2.get());
  mEngine->getCurrentScene()->registerPickable(ballModel3.get());
  mEngine->getCurrentScene()->registerPickable(ballModel4.get());
  mEngine->getCurrentScene()->registerPickable(ballModel5.get());

  /* Attach ball model to ball entity */
  mEngine->getCurrentScene()->attach(std::move(ballModel1));
  mEngine->getCurrentScene()->attach(std::move(ballModel2));
  mEngine->getCurrentScene()->attach(std::move(ballModel3));
  mEngine->getCurrentScene()->attach(std::move(ballModel4));
  mEngine->getCurrentScene()->attach(std::move(ballModel5));

  /* Register picking callback */
  std::function<void(const flf::Event &)> colorFuncHandler = std::bind(&ColorPickingCallback::perform,
                                                                       &(*mColorCallback),
                                                                       std::placeholders::_1);
  mEngine->attachHandler(std::move(colorFuncHandler), flw::flf::eEventType::custom);

  /* Description */
  flw::flf::ps<flw::flf::Text> description = mEngine->storeText("Fillwave example cursor picking",
                                         "fonts/Titania",
                                         glm::vec2(-0.95, 0.95),
                                         100.0);

  flw::flf::ps<flw::flf::Text> hint0 = mEngine->storeText("Pick a sphere", "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}

void PickingScene::perform() {

}

}