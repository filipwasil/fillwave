//============================================================================
// Name        : example_callbacks.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example callbacks
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>
/* Graphics */
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>

/* Physics */
//#include <bullet>
using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

const GLint SPHERES = 5;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::mGraphics->onResizeScreen(mContext.getScreenWidth(), mContext.getScreenHeight());
  init();
  perform();
  showDescription();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void init() {
  /* Scene and camera */
  ContextGLFW::mGraphics->setCurrentScene(make_unique<Scene>());
  ContextGLFW::mGraphics->getCurrentScene()->setCamera(make_unique<CameraPerspective>());
  ContextGLFW::mGraphics->getCurrentScene()->getCamera()->moveTo(glm::vec3(0.0, 0.0, 7.0));
}

void perform() {
  /* Scene and camera */
  ContextGLFW::mGraphics->setCurrentScene(make_unique<Scene>());
  ContextGLFW::mGraphics->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

  puHUD hud = make_unique<HUD>();

  auto background = ContextGLFW::mGraphics->storeTexture("textures/wall/stonetiles_s.png");
  auto gauge = ContextGLFW::mGraphics->storeTexture("textures/wall/stonetiles_s.png");
//  auto gauges

  auto gaugeHud
    = make_unique < Sprite > (
      gauge
      , ProgramLoader(ContextGLFW::mGraphics).getHUDCustomFragmentShader("shaders/gauge/gauge.frag")
      , vec2(-1.0f)
      , vec2(2.0f));

  auto backgroundHud
    = make_unique < Sprite > (
      gauge
      , ProgramLoader(ContextGLFW::mGraphics).getHUDCustomFragmentShader("shaders/gauge/gauge.frag")
      , vec2(-0.75f, -0.75f)
      , vec2( 1.0f,  1.0f));

  hud->attach(std::move(backgroundHud));
  hud->attach(std::move(gaugeHud));

  ContextGLFW::mGraphics->getCurrentScene()->setHUD(std::move(hud));
}

void quit() {
//
}

void showDescription() {
  auto e = ContextGLFW::mGraphics;
  auto h2 = e->storeText("Test app", "fonts/Titania", glm::vec2(-0.95, 0.80), 70.0);
}
