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

using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

int main(int argc, char* argv[]) {
  App mContext(argc, argv);
  App::mGraphics->insertResizeScreen(mContext.getScreenWidth(),
                                                   mContext.getScreenHeight());
  perform();
  Cradle cradle(App::mGraphics);
  mContext.render();
  exit(EXIT_SUCCESS);
}

void perform() {
  /* Scene and camera */
  App::mGraphics->setCurrentScene(make_unique<Scene>());
  App::mGraphics->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

//  puHUD hud = make_unique<HUD>();
//
//  hud->attach(make_unique<Cluster>(
//      App::mGraphics, nullptr, "shaders/gauge/gauge.frag", vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f)));
//
//  App::mGraphics->getCurrentScene()->setHUD(std::move(hud));
}