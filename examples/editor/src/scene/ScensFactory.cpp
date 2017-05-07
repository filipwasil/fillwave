#include <scene/sceneImp/AnimationScene.h>
#include "ScensFactory.h"
#include "sceneImp/TextScene.h"

namespace scene {
ScensFactory::ScensFactory(int argc, char **argv)
    : mArgc(argc), mArgv(argv) {
  mScens["Hello World"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::TextScene>(argc_, argv_);
    return scen;
  };
  mScens["Animation Scene"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::AnimationScene>(argc_, argv_);
    return scen;
  };
}

std::shared_ptr<scene::AScene> ScensFactory::createScen(QString name) {
  if (!mScens.contains(name)) {
    return nullptr;
  }
  auto scen = mScens[name];
  return scen(mArgc, mArgv);
}
}