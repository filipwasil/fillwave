/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>

#include "../../android/inc/CallbacksEGL/TimedMoveCallbackCustom.h"

using namespace fillwave;

void perform(fillwave::Engine* engine) {
   /* Scene */
   pScenePerspective gScene = buildScenePerspective();

   /* Camera */
   space::CameraPerspective gCamera (glm::vec3(0.0,0.0,6.0),
                                     glm::quat(),
                                     glm::radians(90.0),
                                     1.0,
                                     0.1,
                                     1000.0);

   engine->configureDebugger(eDebuggerState::lightsSpot);

   const GLuint SPHERES = 5;
   pModel gSpheres[SPHERES];
   actions::LoopCallback* loop[SPHERES];

   /* Program */
   loader::ProgramLoader loader;
   pProgram progDefault = loader.getDefault(engine);


   /* Lights */
   engine->storeLightSpot(glm::vec3 (0.0,0.0,5.0),
                          glm::quat (),
                          glm::vec4 (0.0,1.0,0.0,0.0));

   /* Set scene */
   engine->setCurrentScene(gScene);

   /* Attach camera to scene */
   gScene->setCamera(gCamera);

   /* Models */

   pModel wall = buildModel(engine, progDefault, "floor.obj", "test.png", "test.png", "test.png");

   gScene->attach(wall);


   models::BuilderModelExternalMaps builder(engine, "sphere.obj", progDefault, "test.png");

   for (GLint i=0;i<SPHERES;i++) {
      /* build */
      gSpheres[i]= builder.build();//buildModel(engine, progDefault, "meshes/sphere.obj", "textures/test.png");

      /* move */
      gSpheres[i]->scaleTo(0.1);
      gSpheres[i]->moveByX(-4+2*i);

      /* create callbacks loop */
      actions::TimedScaleCallback* scale_up = new actions::TimedScaleCallback(gSpheres[i], 0.1*2.0,2.0f + i*0.5, eEasing::CircIn);
      actions::TimedScaleCallback* scale_down = new actions::TimedScaleCallback(gSpheres[i], 0.1*1.0,2.0f + i*0.5, eEasing::Elastic);
      actions::TimedRotateCallback* rotateLeft = new actions::TimedRotateCallback(gSpheres[i], glm::vec3(0.0,1.0,0.0), glm::radians(90.0f), 2.0f + i*0.5, eEasing::BounceIn);
      actions::TimedRotateCallback* rotateRight = new actions::TimedRotateCallback(gSpheres[i], glm::vec3(0.0,1.0,0.0), glm::radians(90.0f),2.0f + i*0.5, eEasing::CubicIn);
      actions::TimedMoveCallback* moveUp = new actions::TimedMoveCallback(gSpheres[i], glm::vec3(0.0,1.0,0.0),2.0f + i*0.5, eEasing::CubicInOut);
      actions::TimedMoveCallback* moveDown = new actions::TimedMoveCallback(gSpheres[i], glm::vec3(0.0,-1.0,0.0),2.0f + i*0.5); //eEasing::None is default

      actions::SequenceCallback* sequence = new actions::SequenceCallback();
      sequence->push_back(scale_up);
      sequence->push_back(scale_down);
      sequence->push_back(rotateLeft);
      sequence->push_back(rotateRight);
      sequence->push_back(moveUp);
      sequence->push_back(moveDown);

      if (i==SPHERES/2) {
         actions::TimedMoveCallbackCustom* moveBack = new actions::TimedMoveCallbackCustom(gSpheres[i], glm::vec3(1.0,-1.0,0.0),2.0f + i*0.5);
         actions::TimedMoveCallbackCustom* moveFront = new actions::TimedMoveCallbackCustom(gSpheres[i], glm::vec3(-1.0,1.0,0.0),2.0f + i*0.5);
         sequence->push_back(moveBack);
         sequence->push_back(moveFront);
      }

      loop[i] = new actions::LoopCallback(sequence, FILLWAVE_ENDLESS);

      gSpheres[i]->attachHierarchyCallback(loop[i]);

      gScene->attach(gSpheres[i]);
   }

   wall->rotateByX(glm::radians(90.0));
   wall->moveInDirection(glm::vec3(0.0,-10.0,0.0));
   wall->scaleTo(3.0);
}
