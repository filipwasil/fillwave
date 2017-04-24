#include "SimpleScene.h"
#include "fillwave/models/Model.h"
#include "fillwave/loaders/ProgramLoader.h"
namespace scene {

using namespace flw;
using namespace flw::flf;

SimpleScene::SimpleScene(int argc, char **argv)
    : mArgc(argc), mArgv(argv) {
  init();
}

void SimpleScene::init() {
  mEngine = std::make_shared<flw::Engine>(mArgc, mArgv);

  mEngine->setCurrentScene(std::make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(
      std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
                                   glm::quat(),
                                   glm::radians(90.0),
                                   1.0,
                                   0.1,
                                   1000.0));

  mEngine->getCurrentScene()->attach(std::make_unique<Model>(mEngine.get(),
                                                            ProgramLoader(mEngine.get()).getDefault(),
                                                            "meshes/sphere.obj", "255_255_255.color"));
}

void SimpleScene::perform() {

}

void SimpleScene::setDefaultParameters(const QVector<std::pair<QString, QString>> &param) {

}

SimpleScene::~SimpleScene() {

}

}