//============================================================================
// Name        : example_terrain_voxel.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example terrain voxel
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>

/* Graphics */
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <TerrainConstructors/MountainConstructor.h>
#include <fillwave/Fillwave.h>

/* Physics */
//#include <bullet>

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

Engine* gEngine;

pScenePerspective gScene;
pCameraPerspective gCamera;

pEntity gEntityLight;
pTerrain gTerrain;
pSkybox gSkybox;

map<string, pProgram> gPrograms;

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
   gCamera = pCameraPerspective ( new CameraPerspective(glm::vec3(0.0,1.0,7.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0));

   /* Entities */
   gEntityLight = buildEntity();

   /* Programs */
   ProgramLoader loader;
   pProgram program = loader.getDefault(gEngine);

   /* Models */
   gTerrain = buildTerrainVoxel(gEngine,
                                program,
                                "textures/test.png",
                                new MountainConstructor(),
                                3);

   /* Texture */
   pTexture3D textureCubemap = gEngine->storeTexture3D("textures/skybox/devilpunch/devpun_right.jpg",
                                                      "textures/skybox/devilpunch/devpun_left.jpg",
                                                      "textures/skybox/devilpunch/devpun_top.jpg",
                                                      "",
                                                      "textures/skybox/devilpunch/devpun_front.jpg",
                                                      "textures/skybox/devilpunch/devpun_back.jpg");

   /* Lights */
   gEngine->storeLightSpot(glm::vec3 (0.0,10.0,1.0),
                           glm::quat(),
                           glm::vec4 (1.0,0.0,0.0,1.0),
                           gEntityLight);

   gEntityLight->moveBy(glm::vec3 (0.0,2.0,4.0));

   /* Models */
   gSkybox = buildSkybox(gEngine,
                         textureCubemap);

   /* Engine callbacks */
   gEngine->registerCallback(new TimeStopCallback(gEngine));
   gEngine->registerCallback(new MoveCameraCallback(gEngine,eEventType::eKey, 0.1));
   gEngine->registerCallback(new MoveCameraCallback(gEngine,eEventType::eScroll,0.1));
}

void perform() {
   gEngine->setCurrentScene(gScene);
   gScene->setSkybox(gSkybox);
   gScene->attach(gTerrain);
   gScene->setCamera(gCamera);
}

void showDescription() {
   pText hint0 = gEngine->storeText("Fillwave example terrain voxel", "fonts/Titania", -0.95, 0.80, 100.0);
   pText hint5 = gEngine->storeText("Use mouse to move the camera", "fonts/Titania", -0.95, -0.40, 70.0);
   pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania", -0.95, -0.50, 70.0);
   pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania", -0.95, -0.60, 70.0);
   pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", -0.95, -0.70, 70.0);
   pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania", -0.95, -0.80, 70.0);

}
