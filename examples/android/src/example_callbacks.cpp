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
using namespace fillwave::actions;

void perform(fillwave::Engine *engine) {
  /* Scene */
  pScenePerspective gScene = buildScenePerspective();

  /* Camera */
  space::CameraPerspective gCamera(glm::vec3(0.0, 0.0, 6.0), glm::quat(), glm::radians(90.0), 1.0, 0.1, 1000.0);

  engine->configureDebugger(eDebuggerState::eLightsSpot);

  const GLuint SPHERES = 5;
  pModel gSpheres[SPHERES];
  LoopCallback *loop[SPHERES];

  /* Program */
  loader::ProgramLoader loader;
  core::Program *progDefault = loader.getDefault(engine);


  /* Lights */
  engine->storeLightSpot(glm::vec3(0.0, 0.0, 5.0), glm::quat(), glm::vec4(0.0, 1.0, 0.0, 0.0));

  /* Set scene */
  engine->setCurrentScene(gScene);

  /* Attach camera to scene */
  gScene->setCamera(gCamera);

  /* Models */

  pModel wall = buildModel(engine, progDefault, "floor.obj", "test.png", "test.png", "test.png");

  gScene->attach(wall);


  models::BuilderModelExternalMaps builder(engine, "sphere.obj", progDefault, "test.png");

  for (GLint i = 0; i < SPHERES; i++) {
    /* build */
    gSpheres[i] = builder.build();//make_unique<Model>(engine, progDefault, "meshes/sphere.obj", "textures/test.png");

    /* move */
    gSpheres[i]->scaleTo(0.1);
    gSpheres[i]->moveByX(-4 + 2 * i);

    /* create callbacks loop */
    TimedScaleCallback *scale_up = new TimedScaleCallback(gSpheres[i], 0.1 * 2.0, 2.0f + i * 0.5);
    TimedScaleCallback *scale_down = new TimedScaleCallback(gSpheres[i], 0.1 * 1.0, 2.0f + i * 0.5);
    TimedRotateCallback *rotateLeft = new TimedRotateCallback(gSpheres[i], glm::vec3(0.0, 1.0, 0.0));
    TimedRotateCallback *rotateRight = new TimedRotateCallback(gSpheres[i], glm::vec3(0.0, 1.0, 0.0));
    TimedMoveCallback *moveUp = new TimedMoveCallback(gSpheres[i], glm::vec3(0.0, 1.0, 0.0), 2.0f + i * 0.5);
    TimedMoveCallback *moveDown = new TimedMoveCallback(gSpheres[i],
                                                        glm::vec3(0.0, -1.0, 0.0),
                                                        2.0f + i * 0.5); //eEasing::None is default

    SequenceCallback *sequence = new SequenceCallback();
    sequence->push_back(scale_up);
    sequence->push_back(scale_down);
    sequence->push_back(rotateLeft);
    sequence->push_back(rotateRight);
    sequence->push_back(moveUp);
    sequence->push_back(moveDown);

    if (i == SPHERES / 2) {
      TimedMoveCallback *moveBack = new TimedMoveCallback(gSpheres[i], glm::vec3(1.0, -1.0, 0.0), 2.0f + i * 0.5);
      TimedMoveCallback *moveFront = new TimedMoveCallback(gSpheres[i], glm::vec3(-1.0, 1.0, 0.0), 2.0f + i * 0.5);
      sequence->push_back(moveBack);
      sequence->push_back(moveFront);
    }

    loop[i] = new LoopCallback(sequence, FILLWAVE_ENDLESS);

    gSpheres[i]->attachHierarchyCallback(loop[i]);

    gScene->attach(gSpheres[i]);
  }

  wall->rotateByX(glm::radians(90.0));
  wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
  wall->scaleTo(3.0);
}
