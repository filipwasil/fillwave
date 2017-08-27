#include "ScensFactory.h"


namespace scene {

template <class T>
std::function<std::shared_ptr<scene::AScene>(int, char**, QMap<QString, QVariant>)> factoryEntry() {
  return [](int argc_, char** argv_, QMap<QString, QVariant> mapa) {
    return std::make_shared<T>(argc_, argv_, mapa);
  };
}

ScensFactory::ScensFactory(int argc, char** argv)
  : mArgc(argc)
  , mArgv(argv) {
  /*mScens["Hello World"] = factoryEntry<scene::TextScene>();
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
  mScens["Terrain"] = factoryEntry<scene::TerrainScene>();*/
}

std::shared_ptr<scene::AScene> ScensFactory::createScen(QString name, QMap<QString, QVariant> valueMap) {
  /*if (!mScens.contains(name)) {
    return nullptr;
  }
  auto scen = mScens[name];
  return scen(mArgc, mArgv, valueMap);*/
}
}