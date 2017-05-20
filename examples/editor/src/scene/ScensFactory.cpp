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

template <class T>
std::function<std::shared_ptr<scene::AScene>(int, char **)> factoryEntry()
{
  return [](int argc_, char **argv_) {
    return std::make_shared<T>(argc_, argv_);
  };
}

ScensFactory::ScensFactory(int argc, char **argv)
    : mArgc(argc), mArgv(argv) {
  mScens["Hello World"] = factoryEntry<scene::TextScene>();
  mScens["Animation"] = factoryEntry<scene::AnimationScene>();
  mScens["Specular lights"] = factoryEntry<scene::FullModelScene>();
  mScens["Callbacks"] = factoryEntry<scene::CallbacksScene>();
  mScens["Cursor"] = factoryEntry<scene::CursorScene>();
  mScens["Dynamic texture"] = factoryEntry<scene::DynamicTextureScene>();
  mScens["Picking"] = factoryEntry<scene::PickingScene>();
  mScens["Effects"] = factoryEntry<scene::EffectsScene>();
  mScens["Hud"] = factoryEntry<scene::HudScene>();
  mScens["Ortographic projection"] = factoryEntry<scene::OrtpgraphicProjectionScene>();
  mScens["Particles"] = factoryEntry<scene::ParticlesScene>();
  mScens["Post processing"] = factoryEntry<scene::PostProcessingScene>();
  mScens["Shadows"] = factoryEntry<scene::ShadowScene>();
  mScens["Skybox"] = factoryEntry<scene::SkyboxScene>();
}

std::shared_ptr<scene::AScene> ScensFactory::createScen(QString name) {
  if (!mScens.contains(name)) {
    return nullptr;
  }
  auto scen = mScens[name];
  return scen(mArgc, mArgv);
}
}