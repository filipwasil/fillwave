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

using namespace fillwave;
using namespace std;

Engine* gEngine;
pScenePerspective gScene;
pCameraPerspective gCamera;
pTexture gTexture;

#ifdef __linux__
   void junk() {
     int i;
     i=pthread_getconcurrency();
     (void)i;
   }
#elif _WIN32
    // windows code goes here
#endif

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
   gCamera = pCameraPerspective ( new space::CameraPerspective(glm::vec3(0.0,0.0,6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0));
   /* Textures */
   gTexture = gEngine->storeTexture("textures/particle.png");

   /* Engine callbacks */
   gEngine->registerKeyCallback(new actions::TimeStopCallback());
   gEngine->registerKeyCallback(new actions::MoveCameraCallback(eEventType::key, 0.1));
   gEngine->registerCursorPositionCallback(new actions::MoveCameraCallback(eEventType::cursorPosition, 0.1, ContextGLFW::mWindow));
}

void perform() {
   /* Set current scene */
   gEngine->setCurrentScene(gScene);

   /* Attach camera to scene */
   gScene->setCamera(gCamera);

   /* Attach emiters to entities */

   pEmiterPoint water = pEmiterPoint (new::particles::EmiterPointCPU(gEngine,
         0.3,
         60000.0,
         glm::vec4(0.1,0.1,1.0,1.0),
         glm::vec3(0.0,0.0,0.0),
         glm::vec3(0.0,0.0,0.0),
         glm::vec3(0.9,0.9,0.9),
         glm::vec3(0.0,0.0,0.0),
         glm::vec3(0.0,0.0,0.0),
         10.0,
         10.0,
         gTexture,
         GL_SRC_ALPHA,
         GL_ONE,
         GL_FALSE));
   water->moveBy(glm::vec3(0.0,-1.0,-1.0));

   pEmiterPoint sand = pEmiterPoint (new::particles::EmiterPointCPU(gEngine,
         0.3,
         60000.0,
         glm::vec4(1.0,1.0,0.0,1.0),
         glm::vec3(0.0,2.0,0.0),
         glm::vec3(0.0,0.0,0.0),
         glm::vec3(0.9,0.9,0.9),
         glm::vec3(0.0,0.0,0.0),
         glm::vec3(0.0,0.0,0.0),
         10.0,
         10.0,
         gTexture,
         GL_SRC_ALPHA,
         GL_ONE,
         GL_FALSE));

   pEmiterPoint snow = pEmiterPoint(new::particles::EmiterPointGPU(gEngine,
                 0.3,
                 600.0,
                 glm::vec4(1.0,1.0,1.0,1.0),
                 glm::vec3(0.0,1.0,0.0),
                 glm::vec3(0.0,0.0,0.0),
                 glm::vec3(0.9,0.9,0.9),
                 glm::vec3(0.0,0.0,0.0),
                 glm::vec3(0.6,0.6,0.6),
                 1.0,
                 1.0,
                 gTexture,
                 GL_SRC_ALPHA,
                 GL_ONE,
                 GL_FALSE));

   gScene->attach(sand);
   gScene->attach(water);
   gScene->attach(snow);

   /* For time updates */
   snow->attachHierarchyCallback(new actions::TimedEmiterUpdateCallback(snow, FILLWAVE_ENDLESS));
   water->attachHierarchyCallback(new actions::TimedEmiterUpdateCallback(water, FILLWAVE_ENDLESS));
   sand->attachHierarchyCallback(new actions::TimedEmiterUpdateCallback(sand, FILLWAVE_ENDLESS));
}

void showDescription() {
   pText hint0 = gEngine->storeText("Fillwave example particles", "fonts/Titania", -0.95, 0.80, 100.0);
   pText hint5 = gEngine->storeText("Use mouse to move the camera", "fonts/Titania", -0.95, -0.40, 70.0);
   pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania", -0.95, -0.50, 70.0);
   pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania", -0.95, -0.60, 70.0);
   pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", -0.95, -0.70, 70.0);
   pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania", -0.95, -0.80, 70.0);
}
