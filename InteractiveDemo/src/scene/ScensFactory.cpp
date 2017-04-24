#include "ScensFactory.h"
#include "sceneImp/TextScene.h"
#include "sceneImp/SimpleScene.h"

namespace scene {
ScensFactory::ScensFactory(int argc, char **argv)
    : mArgc(argc), mArgv(argv) {
  mScens["Hello World"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::TextScene>(argc_, argv_);
    return scen;
  };
  mScens["Simple Scene"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::SimpleScene>(argc_, argv_);
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