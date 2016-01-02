//============================================================================
// Name        : example_animation.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example animation
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
using namespace fillwave::framework;
using namespace std;

Engine* gEngine;

pCameraPerspective gCamera;
pScenePerspective gScene;

map<string, pProgram> gPrograms;

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
   /* Scenes */
   gScene = buildScenePerspective();

   /* Cameras */
   gCamera = pCameraPerspective (new CameraPerspective(glm::vec3(0.0,0.0,4.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0));
   /* Programs */
   ProgramLoader loader;
   gPrograms.insert(pair<string,pProgram>("default", loader.getDefault(gEngine)));
   gPrograms.insert(pair<string,pProgram>("defaultAnimation", loader.getDefaultBones(gEngine)));

   /* Engine callbacks */
   gEngine->registerCallback(new TimeStopCallback(gEngine));
   gEngine->registerCallback(new MoveCameraCallback(gEngine, eEventType::eKey, 0.1));
   gEngine->registerCallback(new MoveCameraCallback(gEngine, eEventType::eCursorPosition, 0.05, ContextGLFW::mWindow));
}

void perform() {
   gEngine->setCurrentScene(gScene);

   gScene->setCamera(gCamera);

   pModel beast = pModel (new Model(gEngine, gPrograms["defaultAnimation"], "animations/beast/beast.dae"));
   gScene->attach(beast);

   gEngine->registerCallback(new AnimationKeyboardCallback(beast, eEventType::eKey));
   gEngine->setFocus(eEventType::eKey, beast);

   beast->scaleTo(0.5);
}

void showDescription() {
   pText hint0 = gEngine->storeText("Fillwave example animation", "fonts/Titania", -0.95, 0.80, 100.0);
   pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", -0.95, -0.70, 70.0);
   pText hint2 = gEngine->storeText("Use '0' for start Animating", "fonts/Titania", -0.95, -0.60, 70.0);
   pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania", -0.95, -0.50, 70.0);
   pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania", -0.95, -0.40, 70.0);
   pText hint5 = gEngine->storeText("Use mouse to move the camera", "fonts/Titania", -0.95, -0.30, 70.0);
   pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania", -0.95, -0.80, 70.0);
}
