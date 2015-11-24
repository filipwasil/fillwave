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

using namespace fillwave;
using namespace std;

Engine* gEngine;

pScenePerspective gScene;
pSkybox gSkybox;
pCameraPerspective gCamera;
pEntity gEntityLight;
pProgram gProgram;

int main(int argc, char* argv[]) {
   ContextGLFW mContext;
   ContextGLFW::mGraphicsEngine = new Engine(argc, argv);
   gEngine = ContextGLFW::mGraphicsEngine;
   ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(),
                                                   mContext.getScreenHeight());
   init();
   perform();
   showDescription();
   mContext.render();
   delete gEngine;
   exit(EXIT_SUCCESS);
}

void init() {
   /* Scene */
   gScene = buildScenePerspective();

   /* Camera */
   gCamera = pCameraPerspective ( new space::CameraPerspective(glm::vec3(0.0,2.0,10.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0));

   /* Programs */
   loader::ProgramLoader loader;
   gProgram = loader.getDefault(gEngine);

   /* Texture */
   pTexture3D textureCubemap = gEngine->storeTexture3D("textures/skybox/hourglass/hourglass_right.jpg",
                                                      "textures/skybox/hourglass/hourglass_left.jpg",
                                                      "textures/skybox/hourglass/hourglass_top.jpg",
                                                      "",
                                                      "textures/skybox/hourglass/hourglass_front.jpg",
                                                      "textures/skybox/hourglass/hourglass_back.jpg");
   /* Skybox */
   gSkybox = buildSkybox(gEngine,
                         textureCubemap);

   /* Entities */
   gEntityLight = buildEntity();

   /* Lights */
   pLightSpot l = gEngine->storeLightSpot(glm::vec3 (0.0,1.0,0.0),
                                          glm::quat(),
                                          glm::vec4 (1.0,1.0,1.0,0.0),
                                          gEntityLight);
   gEntityLight->rotateByX(glm::radians(-90.0));

   /* Engine callbacks */
   gEngine->registerKeyCallback(new actions::TimeStopCallback());
   gEngine->registerKeyCallback(new actions::MoveCameraCallback(eEventType::eKey, 0.1));
   gEngine->registerCursorPositionCallback(new actions::MoveCameraCallback(eEventType::eCursorPosition, 0.1, ContextGLFW::mWindow));
}

void perform() {
   /* Set scene */
   gEngine->setCurrentScene(gScene);

   /* Attach entities and entity to the scene */
   gScene->attach(gEntityLight);
   gScene->setCamera(gCamera);
   gScene->setSkybox(gSkybox);

   gEntityLight->attach(buildModel(gEngine,
                                   gProgram,
                                   "meshes/sphere.obj",
                                   "255_255_255.color"));

   pModel wall = buildModel(gEngine,
                            gProgram,
                            "meshes/floor.obj",
                            "textures/wall/stonetiles.png", /* diffuse map */
                            "textures/wall/stonetiles_n.png", /* normals map */
                            "textures/wall/stonetiles_s.png");/* specular map */

   gScene->attach(wall);
   wall->moveInDirection(glm::vec3(0.0,-2.0,0.0));
   wall->scaleTo(1.0);

   gEntityLight->attachHierarchyCallback(new actions::TimedMoveCallback(gEntityLight, glm::vec3(4.0,0.0,0.0), 50.0));
   gEntityLight->scaleTo(0.02);
   gEntityLight->moveBy(glm::vec3(-2.0,4.0,0.0));
}

void showDescription() {
   pText hint0 = gEngine->storeText("Fillwave example normal mapping", "fonts/Titania", -0.95, 0.80, 100.0);
   pText hint5 = gEngine->storeText("Use mouse to move the camera", "fonts/Titania", -0.95, -0.40, 70.0);
   pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania", -0.95, -0.50, 70.0);
   pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania", -0.95, -0.60, 70.0);
   pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", -0.95, -0.70, 70.0);
   pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania", -0.95, -0.80, 70.0);
}
