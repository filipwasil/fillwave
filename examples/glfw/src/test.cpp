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
  ContextGLFW::mGraphics->getCurrentScene()->getCamera()->moveTo(glm::vec3(0.0, 0.0, 14.0));

  /* Lights */
  ContextGLFW::mGraphics->storeLightSpot(glm::vec3(0.0, 0.0, 5.0),
                                               glm::quat(),
                                               glm::vec4(0.0, 1.0, 0.0, 0.0));

  /* Engine callbacks */
//  ContextGLFW::mGraphics->attachHandler(make_unique<TimeStopCallback>
//                                                   (ContextGLFW::mGraphics));
//  ContextGLFW::mGraphics->registerCallback(make_unique
//                                                   <MoveCameraCallback>(ContextGLFW::mGraphics, eEventType::eKey, 0.1));
}

void perform() {
  flc::Program* p = ProgramLoader(ContextGLFW::mGraphics).getProgram(EProgram::basic);

  /* Models */
  BuilderModelExternalMaps builder(ContextGLFW::mGraphics,
                                   "meshes/sphere.obj",
                                   p, "textures/test.png");

  for (GLint i = 0; i < SPHERES; i++) {
    /* build */

    puModel sphere = builder.build();

    /* move */
    sphere->scaleTo(0.1);
    sphere->moveByX(-4 + 2 * i);

    const auto t = 1.0f + i * 0.5f;
    sphere->scaleBy(t, glm::vec3(0.05f), ElasticEaseIn);
    sphere->scaleBy(t, glm::vec3(-0.05f), ElasticEaseIn);
    sphere->rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseIn);
    sphere->rotateBy(2.0f + i * 0.5f, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseOut);
    sphere->moveBy(2.0f + i * 0.5f, glm::vec3(0.0, -1.0, 0.0), ElasticEaseIn);
    sphere->moveBy(2.0f + i * 0.5f, glm::vec3(0.0, 1.0, 0.0), ElasticEaseIn);
    sphere->loop(1000);

    ContextGLFW::mGraphics->getCurrentScene()->attach(std::move(sphere));
  }

  puModel wall = make_unique<Model>(ContextGLFW::mGraphics, p,
                                    "meshes/floor.obj");
  wall->rotateByX(glm::radians(90.0));
  wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
  wall->scaleTo(3.0);
  ContextGLFW::mGraphics->getCurrentScene()->attach(std::move(wall));
}

void quit() {
//
}

void showDescription() {
  pText hint0 =
    ContextGLFW::mGraphics->storeText("Fillwave example callbacks",
                                            "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
  pText hint3 = ContextGLFW::mGraphics->storeText("Use 'S' for camera back",
                                                        "fonts/Titania",
                                                        glm::vec2(-0.95, -0.50), 70.0);
  pText hint4 =
    ContextGLFW::mGraphics->storeText("Use 'W' for camera forward",
                                            "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  pText hint1 =
    ContextGLFW::mGraphics->storeText("Use 'T' to resume/stop time",
                                            "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  pText hint6 =
    ContextGLFW::mGraphics->storeText("Use 'D' for toggle debugger On/Off",
                                            "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}