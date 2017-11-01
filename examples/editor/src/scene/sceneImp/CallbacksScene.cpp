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
  auto e = mEngine.get();

  /* Scene and camera */
  e->setCurrentScene(make_unique<Scene>());
  e->getCurrentScene()->setCamera(make_unique<CameraPerspective>());
  e->getCurrentScene()->getCamera()->moveTo(glm::vec3(0.0, 0.0, 7.0));

  /* Lights */
  e->storeLightSpot(glm::vec3(0.0, 0.0, 5.0), glm::quat(), glm::vec4(0.0, 1.0, 0.0, 0.0));
  
  auto p = ProgramLoader(e).getProgram(EProgram::basic);

  BuilderModelExternalMaps builder(e, "meshes/cubemap.obj", p, "textures/test.png");
  auto wall = make_unique<Model>(e, p, "meshes/floor.obj");

  for (GLint i = 0; i < SPHERES; i++) {
    const auto t = 1.0f + i * 0.5f;

    /* build */
    auto sphere = builder.build();

    /* move */
    sphere->scaleTo(0.005);
    sphere->moveByX(-4 + 2 * i);
    sphere->rotateByX(glm::radians(45.0f));
    sphere->scaleBy(t, glm::vec3(0.05f), ElasticEaseIn);
    sphere->scaleTo(t, glm::vec3(0.005f), ElasticEaseIn);
    sphere->rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseIn);
    sphere->rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseOut);
    sphere->moveBy(t, glm::vec3(-(0.5f * SPHERES) + i, -2.0, 0.0), ElasticEaseIn);
    sphere->moveBy(t, glm::vec3( (0.5f * SPHERES) - i, 2.0, 0.0), ElasticEaseIn);
    sphere->loop(1000);

    e->getCurrentScene()->attach(std::move(sphere));
  }

  wall->rotateByX(glm::radians(90.0));
  wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
  wall->scaleTo(3.0);
  e->getCurrentScene()->attach(std::move(wall));
}

void CallbacksScene::perform() {

}

}
