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

using namespace flw;
using namespace flw::flf;
using namespace std;

int main(int argc, char *argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(), mContext.getScreenHeight());
  init();
  perform();
  showDescription();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void init() {
  /* Scene and camera */
  ContextGLFW::mGraphicsEngine->setCurrentScene(make_unique<Scene>());
  ContextGLFW::mGraphicsEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 2.0, 10.0),
                                                                                            glm::quat(),
                                                                                            glm::radians(90.0),
                                                                                            1.0,
                                                                                            0.1,
                                                                                            1000.0));

  /* Entities */
  puEntity light = buildEntity();

  /* Lights */
  ContextGLFW::mGraphicsEngine->storeLightSpot(glm::vec3(0.0, 1.0, 0.0),
                                               glm::quat(),
                                               glm::vec4(1.0, 1.0, 1.0, 0.0),
                                               light.get());

  light->rotateByX(glm::radians(-90.0));

  flc::Program *program = ProgramLoader(ContextGLFW::mGraphicsEngine).getDefault();

  light->attach(make_unique<Model>(ContextGLFW::mGraphicsEngine, program, "meshes/sphere.obj", "255_255_255.color"));
  light->attachHierarchyCallback(make_unique<TimedMoveCallback>(light.get(), glm::vec3(4.0, 0.0, 0.0), 50.0));
  light->scaleTo(0.02);
  light->moveBy(glm::vec3(-2.0, 4.0, 0.0));

  auto mirroredContent = ContextGLFW::mGraphicsEngine->storeTextureRenderable();

  puModel wall = make_unique<Model>(ContextGLFW::mGraphicsEngine,
                                    program,
                                    "meshes/floor.obj",
                                    mirroredContent,
                                    ContextGLFW::mGraphicsEngine->storeTexture("255_255_255.color"),
                                    ContextGLFW::mGraphicsEngine->storeTexture("255_255_255.color"));
  wall->moveInDirection(glm::vec3(0.0, -2.0, 0.0));
  wall->scaleTo(1.0);

  ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(wall));
  ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(light));

  /* Engine callbacks */
  ContextGLFW::mGraphicsEngine->attachCallback(make_unique<TimeStopCallback>(ContextGLFW::mGraphicsEngine));
  ContextGLFW::mGraphicsEngine->attachCallback(make_unique<MoveCameraCallback>(ContextGLFW::mGraphicsEngine,
                                                                                 eEventType::eKey,
                                                                                 0.1));
  ContextGLFW::mGraphicsEngine->attachCallback(make_unique<MoveCameraCallback>(ContextGLFW::mGraphicsEngine,
                                                                                 eEventType::eCursorPosition,
                                                                                 0.1,
                                                                                 ContextGLFW::mWindow));

  CameraPerspective c(glm::vec3(0.0, 2.0, 10.0),
                                 glm::quat(),
                                 glm::radians(90.0),
                                 1.0,
                                 0.1,
                                 1000.0);
  mirroredContent->bindForWriting();
  ContextGLFW::mGraphicsEngine->getCurrentScene()->draw(c);
  mirroredContent->bindForRendering();
}

void perform() {
  /* Attach entities and entity to the scene */

  ContextGLFW::mGraphicsEngine->getCurrentScene()->setSkybox(make_unique<Skybox>(ContextGLFW::mGraphicsEngine,
                                                                                 ContextGLFW::mGraphicsEngine->storeTexture3D(
                                                                                     "textures/skybox/hourglass/hourglass_right.jpg",
                                                                                     "textures/skybox/hourglass/hourglass_left.jpg",
                                                                                     "textures/skybox/hourglass/hourglass_top.jpg",
                                                                                     "",
                                                                                     "textures/skybox/hourglass/hourglass_front.jpg",
                                                                                     "textures/skybox/hourglass/hourglass_back.jpg")));
}

void showDescription() {
  ContextGLFW::mGraphicsEngine->storeText("Fillwave example normal mapping",
                                          "fonts/Titania",
                                          glm::vec2(-0.95, 0.80),
                                          100.0);
  ContextGLFW::mGraphicsEngine->storeText("Use mouse to move the camera",
                                          "fonts/Titania",
                                          glm::vec2(-0.95, -0.40),
                                          70.0);
  ContextGLFW::mGraphicsEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  ContextGLFW::mGraphicsEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  ContextGLFW::mGraphicsEngine->storeText("Use 'T' to resume/stop time",
                                          "fonts/Titania",
                                          glm::vec2(-0.95, -0.70),
                                          70.0);
  ContextGLFW::mGraphicsEngine->storeText("Use 'D' for toggle debugger On/Off",
                                          "fonts/Titania",
                                          glm::vec2(-0.95, -0.80),
                                          70.0);
}
