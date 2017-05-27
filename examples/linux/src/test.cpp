//============================================================================
// Name        : example_particles.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example particles
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
  ContextGLFW::mGraphicsEngine->getCurrentScene()->setCamera(
      make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                     glm::quat(),
                                     glm::radians(90.0),
                                     1.0,
                                     0.1,
                                     1000.0));

  /* Engine callbacks */
  ContextGLFW::mGraphicsEngine->registerCallback(make_unique<TimeStopCallback>(
      ContextGLFW::mGraphicsEngine));
  ContextGLFW::mGraphicsEngine->registerCallback(make_unique<MoveCameraCallback>(
      ContextGLFW::mGraphicsEngine, eEventType::eKey, 0.1));
  ContextGLFW::mGraphicsEngine->registerCallback(make_unique<MoveCameraCallback>(
      ContextGLFW::mGraphicsEngine, eEventType::eCursorPosition, 0.1,
      ContextGLFW::mWindow));
}

void perform() {
  /* Attach emiters to entities */
  auto water = make_unique<EmiterPointCPU>(ContextGLFW::mGraphicsEngine,
                                           0.3,
                                           60000.0,
                                           glm::vec4(0.1, 0.1, 1.0, 1.0),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.9, 0.9, 0.9),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           glm::vec3(0.0, 0.0, 0.0),
                                           10.0,
                                           10.0,
                                           ContextGLFW::mGraphicsEngine->storeTexture("textures/particle.png"),
                                           GL_SRC_ALPHA,
                                           GL_ONE,
                                           GL_FALSE);
  water->moveBy(glm::vec3(0.0, -1.0, -1.0));

  auto sand = make_unique<EmiterPointCPU>(ContextGLFW::mGraphicsEngine,
                                          0.3,
                                          60000.0,
                                          glm::vec4(1.0, 1.0, 0.0, 1.0),
                                          glm::vec3(0.0, 2.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.9, 0.9, 0.9),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          10.0,
                                          10.0,
                                          ContextGLFW::mGraphicsEngine->storeTexture("textures/particle.png"),
                                          GL_SRC_ALPHA,
                                          GL_ONE,
                                          GL_FALSE);

  auto snow = make_unique<EmiterPointGPU>(ContextGLFW::mGraphicsEngine,
                                          0.3,
                                          600.0,
                                          glm::vec4(1.0, 1.0, 1.0, 1.0),
                                          glm::vec3(0.0, 1.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.9, 0.9, 0.9),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(0.6, 0.6, 0.6),
                                          1.0,
                                          1.0,
                                          ContextGLFW::mGraphicsEngine->storeTexture("textures/particle.png"),
                                          GL_SRC_ALPHA,
                                          GL_ONE,
                                          GL_FALSE);

  /* For time updates */
  snow->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(snow.get(), FILLWAVE_ENDLESS));
  water->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(water.get(), FILLWAVE_ENDLESS));
  sand->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(sand.get(), FILLWAVE_ENDLESS));
  ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(sand));
  ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(water));
  ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(snow));
}

void showDescription() {
  ContextGLFW::mGraphicsEngine->storeText("Particles", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
  ContextGLFW::mGraphicsEngine->storeText("Mouse to move the camera","fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
  ContextGLFW::mGraphicsEngine->storeText("'S' camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  ContextGLFW::mGraphicsEngine->storeText("'W' camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  ContextGLFW::mGraphicsEngine->storeText("'T' resume/stop time", "fonts/Titania",glm::vec2(-0.95, -0.70), 70.0);
  ContextGLFW::mGraphicsEngine->storeText("'D' toggle debugger On/Off", "fonts/Titania",  glm::vec2(-0.95, -0.80), 70.0);
}