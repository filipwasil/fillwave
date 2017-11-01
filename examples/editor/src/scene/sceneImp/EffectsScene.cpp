#include "scene/callbacks/Callbacks.h"
#include "EffectsScene.h"
#include <scene/callbacks/StandardMouseEventHandler.h>
#include <scene/callbacks/StandardKeyboardEventHandler.h>

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

EffectsScene::EffectsScene(int argc, char** argv, QMap<QString, QVariant> varValues)
  : AScene(argc, argv, varValues) {
  mSceneParameters["mText"] = QVariant("HelloWorld");
  init();
}

void EffectsScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

  /* Lights */
  mEngine->storeLightSpot(glm::vec3(1.0, 1.0, 6.0), glm::quat(), glm::vec4(1.0, 0.0, 0.0, 0.0));

  /* Engine callbacks */
  prepareStandardCallbacks();

  puModel model = make_unique<Model>(mEngine.get(),
                                     ProgramLoader(mEngine.get()).getProgram(EProgram::basic),
                                     "meshes/sphere.obj",
                                     "64_128_255.checkboard");
  pIEffect fog = make_shared<Fog>();
  pIEffect boost = make_shared<BoostColor>(10.0);
  model->addEffect(make_shared<Fog>());
  model->addEffect(make_shared<BoostColor>(10.0));

  model->moveBy(glm::vec3(0.0, 0.0, -15.0));

  mEngine->getCurrentScene()->attach(std::move(model));

  /* Description */
  pText hint0 = mEngine->storeText("Fillwave example effects", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
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

void EffectsScene::perform() {

}
}
