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

#include <string>
#include <sstream>

using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

std::vector<pText> texts;
pText shift;

void createDynamicTexts() {
  shift =
      ContextGLFW::mGraphicsEngine->storeText("5",
                                              "fonts/bridgenorth",
                                              vec2(-0.04, 0.2), 300.0,
                                              vec4(0.8, 0.8, 0.8, 1.0),
                                              ETextEffect::eBold);
}

void createGauge(
    int angleStep
    , int angleStart
    , int angleStop
    , int valueStart
    , int valueStop
    , vec2 positionsCenter
    , float radius) {
  angleStep %= 360;
  angleStart %= 360;
  angleStop %= 360;
  if (angleStep <= 0 && angleStart - angleStop < angleStep) {
    // bad input data
    return;
  }

  const int angleSteps = (angleStop - angleStart)/angleStep;
  const int valueStep = (valueStop - valueStart)/angleSteps;

  int angle = angleStart;
  int value = valueStart;
  while (angle <= angleStop) {
    std::ostringstream oss;
    oss << value;
    std::string val = oss.str();
    float a = static_cast<float>(angle);
    const glm::vec2 screenSize = ContextGLFW::mGraphicsEngine->getScreenSize();
    float f = screenSize.x/screenSize.y;
    float x = positionsCenter.x + ( radius * cos(radians(-a - 90.f)) ) / f;
    float y = positionsCenter.y + ( radius * sin(radians(-a - 90.f)) );
    texts.push_back(ContextGLFW::mGraphicsEngine->storeText(val.c_str(), "fonts/bridgenorth", vec2(x, y), 100.0));
    angle += angleStep;
    value += valueStep;
  }
}

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

  auto gauges = make_unique < ProgressBar
  >(ContextGLFW::mGraphicsEngine,
    ContextGLFW::mGraphicsEngine->storeTexture("128_128_64.color"),
    "shaders/gauge/gauge.frag",
    vec2(-1.0f, -1.0f),
    vec2(2.0f, 2.0f));

  gauges->setProgress(0.99);
  createGauge(20, 30, 330, 0, 300, vec2(-0.65, 0.0f), 0.45f);
  createGauge(27, 45, 315, 0, 10, vec2(0.65, 0.0f), 0.45f);

  hud->attach(std::move(gauges));

  createDynamicTexts();

  ContextGLFW::mGraphicsEngine->getCurrentScene()->setHUD(std::move(hud));
}