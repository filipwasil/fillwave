//============================================================================
// Name        : Client.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example full
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
#include <TerrainConstructors/MountainConstructor.h>
#include <fillwave/management/base/TManagerSmart.h>

/* Physics */
//#include <bullet>

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

Engine* gEngine;

pCameraPerspective gCamera;
pScenePerspective gScene;

pProgram gProgram;
map<string, pModel> gModels;

FLOGINIT("Test app", FERROR | FFATAL)

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
   gCamera = pCameraPerspective ( new CameraPerspective(glm::vec3(0.0,5.0,0.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0));

   /* Shaders */
   ProgramLoader loader(gEngine);
   gProgram = loader.getDefault();

   /* Models */


   /* Lights */
   pLight  light = gEngine->storeLightSpot(glm::vec3 (1.0,20.0,6.0),
                           glm::quat (),
                           glm::vec4 (1.0,1.0,1.0,0.0));
   light->rotateTo(glm::vec3(1.0,0.0,0.0), glm::radians(-90.0));

   /* Engine callbacks */
   gEngine->registerCallback(new TimeStopCallback(gEngine));
   gEngine->registerCallback(new MoveCameraCallback(gEngine,eEventType::eKey, 0.1));
   gEngine->registerCallback(new MoveCameraCallback(gEngine,eEventType::eCursorPosition, 0.1, ContextGLFW::mWindow));
}

void perform() {
   gEngine->configureFPSCounter("fonts/Titania",  glm::vec2(0.7,0.9), 100.0);
   gEngine->setCurrentScene(gScene);

   pIEffect fog(new Fog());

   gScene->setCamera(gCamera);

   Material material;

   pMeshTerrain terrain = std::make_shared<MeshTerrain>(gEngine,
                                    gProgram,
                                    new MountainConstructor(),
                                    material,
                                    "textures/test.png",
                                    "textures/testNormal.png",
                                    "",
                                    20,
                                    16);
   terrain->scaleTo(2.0);
   terrain->addEffect(fog);
   gScene->attach(terrain);
}

void showDescription() {
   /* Description */
   pText hint0 = gEngine->storeText("Fillwave example terrain", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
   pText hint5 = gEngine->storeText("Use mouse to move the camera", "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
   pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
   pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
   pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
   pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}
