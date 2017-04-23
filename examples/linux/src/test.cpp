//============================================================================
// Name        : Client.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example full
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>

/* Graphics */
#include <CallbacksGLFW/FollowCustomCursorCallback.h>
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

/* Physics */
//#include <bullet>

using namespace flw;
using namespace flw::flf;
using namespace std;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(),
                                                   mContext.getScreenHeight());
  init();
  perform();
  showDescription();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void init() {
  /* Scene and camera */
  ContextGLFW::mGraphicsEngine->setCurrentScene(make_unique<Scene>());
  ContextGLFW::mGraphicsEngine->getCurrentScene().setCamera(
      make_unique<CameraPerspective>());

  /* Engine callbacks */
  ContextGLFW::mGraphicsEngine->registerCallback(make_unique<TimeStopCallback>
                                                     (ContextGLFW::mGraphicsEngine));
  ContextGLFW::mGraphicsEngine->registerCallback(make_unique<MoveCameraCallback>
                                                     (ContextGLFW::mGraphicsEngine, eEventType::eKey, 0.1));
}

void perform() {
  /* Cursor texture */
  flc::Texture2D* textureC =
      ContextGLFW::mGraphicsEngine->storeTexture("textures/cursor/standard_blue.png")
  ;

  /* Cursor */
  ContextGLFW::mGraphicsEngine->getCurrentScene().setCursor(make_unique<Cursor>
                                                                (ContextGLFW::mGraphicsEngine, textureC));

  /* Make cursor visible for current scene */
  ContextGLFW::mGraphicsEngine->registerCallback(
      make_unique<FollowCustomCursorCallback>(ContextGLFW::mGraphicsEngine));
}

void showDescription() {
  /* Description */
  pText description =
      ContextGLFW::mGraphicsEngine->storeText("Fillwave example cursor",
                                              "fonts/Titania",
                                              glm::vec2(-0.95,
                                                        0.95),
                                              100.0);
}
