//============================================================================
// Name        : example_text.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example text
//============================================================================

#include <example.h>

/* Graphics */
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

#include "Cluster.h"
#include "Cradle.h"

#include <App.h>

#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
  App mContext(argc, argv);
  App::mGraphics->onResizeScreen(mContext.getScreenWidth(), mContext.getScreenHeight());
  perform();
  Cradle cradle(App::mGraphics);
  mContext.render();
  exit(EXIT_SUCCESS);
}

void perform() {
  /* Scene and camera */
  App::mGraphics->setCurrentScene(std::make_unique<flw::flf::Scene>());
  App::mGraphics->getCurrentScene()->setCamera(std::make_unique<flw::flf::CameraPerspective>());
}