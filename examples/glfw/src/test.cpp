//============================================================================
// Name        : example_text.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example text
//============================================================================

#include <ContextGLFW.h>
#include <example.h>

/* Graphics */
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>
#include "Cluster.h"

#include <string>
#include <sstream>

using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(),
                                                   mContext.getScreenHeight());
  perform();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void perform() {
  /* Scene and camera */
  ContextGLFW::mGraphicsEngine->setCurrentScene(make_unique<Scene>());
  ContextGLFW::mGraphicsEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

  puHUD hud = make_unique<HUD>();

  auto gauges = make_unique < Cluster
  >(ContextGLFW::mGraphicsEngine, nullptr,
    "shaders/gauge/gauge.frag",
    vec2(-1.0f, -1.0f),
    vec2(2.0f, 2.0f));

  gauges->createGauge(20, 30, 330, 0, 300, vec2(-0.65, 0.0f), 0.43f);
  gauges->createGauge(27, 45, 315, 0, 10, vec2(0.60, 0.0f), 0.43f);
  gauges->setShift(8);
  gauges->setSpeed(30.0f);
  gauges->setRPM(45.0f);

  hud->attach(std::move(gauges));

  ContextGLFW::mGraphicsEngine->getCurrentScene()->setHUD(std::move(hud));
}