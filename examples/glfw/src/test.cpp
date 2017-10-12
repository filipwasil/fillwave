//============================================================================
// Name        : example_normals_and_specular_map.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave normals and specular map example
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>

/* Graphics */
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <fillwave/Fillwave.h>

/* Physics */
//#include <bullet>

int main(int argc, char* argv[]) {
  App mContext(argc, argv);
  App::mGraphics->onResizeScreen(mContext.getScreenWidth(), mContext.getScreenHeight());
  perform();
  showDescription();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void init() {
  /* Scene and camera */
  App::mGraphics->setCurrentScene(std::make_unique<flw::flf::Scene>());
  App::mGraphics->getCurrentScene()->setCamera(std::make_unique<flw::flf::CameraPerspective>());
}