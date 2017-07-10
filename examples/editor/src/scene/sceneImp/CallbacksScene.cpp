#include "CallbacksScene.h"
#include "scene/callbacks/Callbacks.h"
#include "fillwave/common/Macros.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

const GLuint SPHERES = 5;

namespace scene {

CallbacksScene::CallbacksScene(int argc, char **argv, QMap<QString, QVariant> varValues)
    : AScene(argc, argv, varValues) {
  init();
}

void CallbacksScene::init() {
  /* Scene and camera */
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());


  /* Lights */
  mEngine->storeLightSpot(glm::vec3(0.0, 0.0, 5.0), glm::quat(), glm::vec4(0.0, 1.0, 0.0, 0.0));

  /* Engine callbacks */
  mEngine->attachCallback(make_unique<TimeStopCallback>(mEngine.get()));
  mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));

  flc::Program *p = ProgramLoader(mEngine.get()).getDefault();

  /* Models */
  BuilderModelExternalMaps builder(mEngine.get(), "meshes/sphere.obj", p, "textures/test.png");

  for (GLint i = 0; i < SPHERES; i++) {
    /* build */

    auto sphere = builder.build();

    /* move */
    sphere->scaleTo(0.1);
    sphere->moveByX(-4 + 2 * i);
    sphere->moveByZ(-4);

    sphere->attachHierarchyCallback(make_unique<LoopCallback>(std::move(make_unique_container<SequenceCallback>(
        make_unique<TimedScaleCallback>(sphere.get(), 0.1 * 2.0, 2.0f + i * 0.5, CircularEaseIn),
        make_unique<TimedScaleCallback>(sphere.get(), 0.1 * 1.0, 2.0f + i * 0.5, ElasticEaseIn),
        make_unique<TimedRotateCallback>(sphere.get(),
                                         glm::vec3(0.0, 1.0, 0.0),
                                         glm::radians(90.0f),
                                         2.0f + i * 0.5,
                                         BounceEaseIn),
        make_unique<TimedRotateCallback>(sphere.get(),
                                         glm::vec3(0.0, 1.0, 0.0),
                                         glm::radians(90.0f),
                                         2.0f + i * 0.5,
                                         BounceEaseOut),
        make_unique<TimedMoveCallback>(sphere.get(), glm::vec3(0.0, -1.0, 0.0), 2.0f + i * 0.5),
        make_unique<TimedMoveCallback>(sphere.get(), glm::vec3(0.0, 1.0, 0.0), 2.0f + i * 0.5))), FILLWAVE_ENDLESS));

    mEngine->getCurrentScene()->attach(std::move(sphere));
  }

  puModel wall = make_unique<Model>(mEngine.get(), p, "meshes/floor.obj");
  wall->rotateByX(glm::radians(90.0));
  wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
  wall->scaleTo(3.0);
  mEngine->getCurrentScene()->attach(std::move(wall));
}

void CallbacksScene::perform() {

}

}
