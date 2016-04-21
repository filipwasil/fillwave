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
using namespace fillwave::framework;
using namespace std;

Engine* gEngine;
pScenePerspective gScene;
pCameraPerspective gCamera;
core::Texture* gTexture;

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
   gCamera = pCameraPerspective ( new CameraPerspective(glm::vec3(0.0,0.0,6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0));
   /* Textures */
   gTexture = gEngine->storeTexture("textures/particle.png");

   /* Engine callbacks */
   gEngine->registerCallback(new TimeStopCallback(gEngine));
   gEngine->registerCallback(new MoveCameraCallback(gEngine,eEventType::eKey, 0.1));
   gEngine->registerCallback(new MoveCameraCallback(gEngine,eEventType::eCursorPosition, 0.1, ContextGLFW::mWindow));
}

void perform() {
   /* Set current scene */
   gEngine->setCurrentScene(gScene);

   /* Attach camera to scene */
   gScene->setCamera(gCamera);

   /* Attach emiters to entities */

   auto water = make_unique<EmiterPointCPU>(gEngine,
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
         GL_FALSE);
   water->moveBy(glm::vec3(0.0,-1.0,-1.0));

   auto sand = make_unique<EmiterPointCPU>(gEngine,
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
         GL_FALSE);

   auto snow = make_unique<EmiterPointGPU>(gEngine,
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
                 GL_FALSE);

   /* For time updates */
   snow->attachHierarchyCallback(new TimedEmiterUpdateCallback(snow.get(), FILLWAVE_ENDLESS));
   water->attachHierarchyCallback(new TimedEmiterUpdateCallback(water.get(), FILLWAVE_ENDLESS));
   sand->attachHierarchyCallback(new TimedEmiterUpdateCallback(sand.get(), FILLWAVE_ENDLESS));

   gScene->attach(std::move(sand));
   gScene->attach(std::move(water));
   gScene->attach(std::move(snow));
}

void showDescription() {
   pText hint0 = gEngine->storeText("Fillwave example particles", "fonts/Titania",  glm::vec2(-0.95, 0.80), 100.0);
   pText hint5 = gEngine->storeText("Use mouse to move the camera", "fonts/Titania",  glm::vec2(-0.95, -0.40), 70.0);
   pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania",  glm::vec2(-0.95, -0.50), 70.0);
   pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania",  glm::vec2(-0.95, -0.60), 70.0);
   pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania",  glm::vec2(-0.95, -0.70), 70.0);
   pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania",  glm::vec2(-0.95, -0.80), 70.0);
}
