#include "ScensFactory.h"

#include <scene/sceneImp/AnimationScene.h>
#include <scene/sceneImp/TextScene.h>
#include <scene/sceneImp/FullModelScene.h>
#include <scene/sceneImp/CallbacksScene.h>
#include <scene/sceneImp/CursorScene.h>
#include <scene/sceneImp/DynamicTextureScene.h>
#include <scene/sceneImp/EffectsScene.h>
#include <scene/sceneImp/HudScene.h>
#include <scene/sceneImp/OrtpgraphicProjectionScene.h>
#include <scene/sceneImp/ParticlesScene.h>
#include <scene/sceneImp/PickingScene.h>
#include <scene/sceneImp/PostProcessingScene.h>
#include <scene/sceneImp/ShadowScene.h>
#include <scene/sceneImp/SkyboxScene.h>

namespace scene {

ScensFactory::ScensFactory(int argc, char **argv)
    : mArgc(argc), mArgv(argv) {
  mScens["Hello World"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::TextScene>(argc_, argv_);
    return scen;
  };
  mScens["Animation"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::AnimationScene>(argc_, argv_);
    return scen;
  };
  mScens["Specular lights"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::FullModelScene>(argc_, argv_);
    return scen;
  };
  mScens["Callbacks"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::CallbacksScene>(argc_, argv_);
    return scen;
  };
  mScens["Cursor"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::CursorScene>(argc_, argv_);
    return scen;
  };
  mScens["Dynamic texture"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::DynamicTextureScene>(argc_, argv_);
    return scen;
  };
  mScens["Effects"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::EffectsScene>(argc_, argv_);
    return scen;
  };
  mScens["Hud"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::HudScene>(argc_, argv_);
    return scen;
  };
  mScens["Ortographic projection"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::OrtpgraphicProjectionScene>(argc_, argv_);
    return scen;
  };
  mScens["Particles"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::ParticlesScene>(argc_, argv_);
    return scen;
  };
  mScens["Post processing"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::PostProcessingScene>(argc_, argv_);
    return scen;
  };
  mScens["Shadows"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::ShadowScene>(argc_, argv_);
    return scen;
  };
  mScens["Skybox"] = [](int argc_, char **argv_) {
    std::shared_ptr<scene::AScene> scen = std::make_shared<scene::SkyboxScene>(argc_, argv_);
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