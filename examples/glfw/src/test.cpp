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

  /* Lights */
  ContextGLFW::mGraphics->storeLightSpot(glm::vec3(0.0, 0.0, 5.0),
                                               glm::quat(),
                                               glm::vec4(0.0, 1.0, 0.0, 0.0));

  /* Engine callbacks */
//  ContextGLFW::mGraphics->attachHandler(make_unique<TimeStopCallback> (ContextGLFW::mGraphics));
//  ContextGLFW::mGraphics->registerCallback(make_unique <MoveCameraCallback>(ContextGLFW::mGraphics,
// eEventType::eKey, 0.1));
}

void perform() {
  //auto p = ProgramLoader(ContextGLFW::mGraphics).getProgram(EProgram::basic, "shaders/tesselation");
  auto p = ProgramLoader(ContextGLFW::mGraphics).getProgram(EProgram::basic);
  auto e = ContextGLFW::mGraphics;

  /* Models */
  BuilderModelExternalMaps builder(ContextGLFW::mGraphics, "meshes/cubemap.obj", p, "textures/test.png");
  auto wall = make_unique<Model>(ContextGLFW::mGraphics, p, "meshes/floor.obj");

  for (GLint i = 0; i < SPHERES; i++) {
    const auto t = 1.0f + i * 0.5f;

    /* build */
    auto sphere = builder.build();

    /* move */
    sphere->scaleTo(0.005);
    sphere->moveByX(-4 + 2 * i);
    sphere->rotateByX(glm::radians(45.0f));
    sphere->scaleBy(t, glm::vec3(0.05f), ElasticEaseIn);
    sphere->scaleTo(t, glm::vec3(0.005f), ElasticEaseIn);
    sphere->rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseIn);
    sphere->rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseOut);
    sphere->moveBy(t, glm::vec3(-(0.5f * SPHERES) + i, -2.0, 0.0), ElasticEaseIn);
    sphere->moveBy(t, glm::vec3( (0.5f * SPHERES) - i, 2.0, 0.0), ElasticEaseIn);
    sphere->loop(1000);

    ContextGLFW::mGraphics->getCurrentScene()->attach(std::move(sphere));
  }

  wall->rotateByX(glm::radians(90.0));
  wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
  wall->scaleTo(3.0);
  ContextGLFW::mGraphics->getCurrentScene()->attach(std::move(wall));

  auto snow = make_unique<EmiterPointGPU>(ContextGLFW::mGraphics,
                                          0.3,
                                          200.0,
                                          glm::vec4(10.0, 10.0, 10.0, 1.0),
                                          glm::vec3(0.0, 10.0, 0.0),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(10.9, 10.9, 0.9),
                                          glm::vec3(0.0, 0.0, 0.0),
                                          glm::vec3(15.6, 0.6, 0.6),
                                          1.0,
                                          1.0,
                                          ContextGLFW::mGraphics->storeTexture("textures/particle.png"),
                                          GL_SRC_ALPHA,
                                          GL_ONE,
                                          GL_FALSE);
  snow->moveBy( { 0.0, 3.0, 0.0} );
  ContextGLFW::mGraphics->getCurrentScene()->attach(std::move(snow));
}

void quit() {
//
}

void showDescription() {
  auto e = ContextGLFW::mGraphics;
  auto h2 = e->storeText("Test app", "fonts/Titania", glm::vec2(-0.95, 0.80), 70.0);
}