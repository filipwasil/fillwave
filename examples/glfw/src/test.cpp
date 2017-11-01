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

  auto p = ProgramLoader(ContextGLFW::mGraphics).getHUDCustomFragmentShader("shaders/gauge/gauge.frag");
  p->use();
  p->uniformPush("uResolution", glm::vec2(ContextGLFW::mScreenWidth, ContextGLFW::mScreenHeight));
  hud->attach(make_unique < Sprite > (
    ContextGLFW::mGraphics->storeTexture("textures/wall/stonetiles.png")
    , ProgramLoader(ContextGLFW::mGraphics).getHUDCustomFragmentShader("shaders/gauge/gauge.frag")
    , vec2(-0.75f, -0.75f)
    , vec2( 1.0f,  1.0f)));

//  hud->attach(make_unique < Sprite > (
//    ContextGLFW::mGraphics->storeTexture("textures/W.JPG")
//    , ProgramLoader(ContextGLFW::mGraphics).getHUDCustomFragmentShader("shaders/gauge/gauge.frag")
//    , vec2(-0.5f, -0.5f)
//    , vec2( 0.25f,  0.25f)));

  hud->attach(make_unique < Sprite > (
    ContextGLFW::mGraphics->storeTexture("textures/W.JPG")
    , ProgramLoader(ContextGLFW::mGraphics).getHUDCustomFragmentShader("shaders/gauge/gauge.frag")
    , vec2(-1.0f)
    , vec2(2.0f)));

  ContextGLFW::mGraphics->getCurrentScene()->setHUD(std::move(hud));
}

void quit() {
//
}

void setupParam(const char* name, glm::vec2 position) {
  ContextGLFW::mGraphics->storeText(name, "fonts/Titania", position, 70.0);
  position.y -= 0.06f;
  ContextGLFW::mGraphics->storeText((std::string(name) + std::string("val")).c_str(), "fonts/Titania", position, 80.0);
}

void showDescription() {
  auto e = ContextGLFW::mGraphics;
  setupParam("par1", glm::vec2(0.30, 0.28));
  setupParam("par2", glm::vec2(0.50, 0.28));
  setupParam("par3", glm::vec2(0.70, 0.28));
  setupParam("par4", glm::vec2(0.30, 0.08));
  setupParam("par5", glm::vec2(0.50, 0.08));
  setupParam("par6", glm::vec2(0.70, 0.08));
  setupParam("par7", glm::vec2(0.30, -0.12));
  setupParam("par8", glm::vec2(0.50, -0.12));
  setupParam("par9", glm::vec2(0.70, -0.12));
  setupParam("par11", glm::vec2(0.30, -0.32));
  setupParam("par12", glm::vec2(0.50, -0.32));
  setupParam("par13", glm::vec2(0.70, -0.32));
  setupParam("par14", glm::vec2(0.30, -0.52));
  setupParam("par15", glm::vec2(0.50, -0.52));
  setupParam("par16", glm::vec2(0.70, -0.52));
}

