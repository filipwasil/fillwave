/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>
#include <fillwave/models/shapes/Quad.h>
#include <fillwave/Framework.h>

using namespace fillwave;
using namespace fillwave::framework;

void perform(Engine *engine) {
  /* Scene and camera */
  engine->setCurrentScene (std::make_unique<Scene> ());
  engine->getCurrentScene ()->setCamera (std::make_unique<CameraPerspective> (glm::vec3 (0.0, 2.0, 18.0),
                                                                              glm::quat (),
                                                                              glm::radians (90.0),
                                                                              1.0,
                                                                              0.1,
                                                                              1000.0));
  /* Skybox */
  engine->getCurrentScene ()->setSkybox (std::make_unique<Skybox> (engine,
                                                                   engine->storeTexture3D ("emerald_right.jpg",
                                                                                           "emerald_left.jpg",
                                                                                           "emerald_top.jpg",
                                                                                           "",
                                                                                           "emerald_front.jpg",
                                                                                           "emerald_back.jpg")));

  /* Program */
  ProgramLoader loader (engine);
  core::Program *program = loader.getDefault ();
  core::Program *aprogram = loader.getDefaultBones ();

  pIEffect e = std::make_shared<TextureOnly> ();
  pIEffect f = std::make_shared<Fog> ();

  puModel cactus1 = std::make_unique<Model> (engine, aprogram, "beast.dae");
  puModel cactus2 = std::make_unique<Model> (engine, aprogram, "beast.dae");
  puModel cactus3 = std::make_unique<Model> (engine, aprogram, "beast.dae");

  cactus1->moveTo (glm::vec3 (0.0, -2.0, 0.0));
  cactus1->rotateBy (glm::vec3 (1.0, 0.0, 0.0), glm::radians (90.0));
  cactus1->setActiveAnimation (0);

  cactus1->addEffect (e);
  cactus1->addEffect (f);

  cactus2->moveTo (glm::vec3 (4.0, -2.0, 0.0));
  cactus2->rotateBy (glm::vec3 (1.0, 0.0, 0.0), glm::radians (90.0));
  cactus2->setActiveAnimation (0);

  cactus2->addEffect (e);
  cactus2->addEffect (f);

  cactus3->moveTo (glm::vec3 (-4.0, -2.0, 0.0));
  cactus3->rotateBy (glm::vec3 (1.0, 0.0, 0.0), glm::radians (90.0));
  cactus3->setActiveAnimation (0);
  cactus3->addEffect (e);
  cactus3->addEffect (f);

  /* Text */
  pText text = engine->storeText ("Fillwave example", "bridgenorth", glm::vec2 (-0.95, 0.95), 100.0);

  /* Specular and normal mapping*/
  puEntity entityLight = buildEntity ();

  LightDirectional *light = engine->storeLightDirectional (glm::vec3 (0.0, 0.6, 0.0),
                                                           glm::quat (),
                                                           glm::vec4 (1.0, 1.0, 1.0, 1.0),
                                                           entityLight.get ());

  entityLight->rotateByX (glm::radians (-90.0));
  entityLight->moveBy (glm::vec3 (-8.0, 8.0, 0.0));
  entityLight->attach (std::make_unique<Model> (engine, program, "sphere.obj", "255_255_255.color"));

  puModel wall = std::make_unique<Model> (engine, program, "floor.obj", "stonetiles.png",   /* diffuse map */
                                          "stonetiles_n.png", /* normals map */
                                          "stonetiles_s.png");/* specular map */
  wall->moveBy (glm::vec3 (0.0, -3.0, 0.0));

  entityLight->attachHierarchyCallback (std::make_unique<LoopCallback> (make_unique_container<SequenceCallback> (std::make_unique<TimedMoveCallback> (
      entityLight.get (),
      glm::vec3 (16.0, 0.0, 0.0),
      10.0), std::make_unique<TimedMoveCallback> (entityLight.get (), glm::vec3 (-16.0, 0.0, 0.0), 10.0)),
                                                                        FILLWAVE_ENDLESS));
  entityLight->scaleTo (0.02);

  engine->getCurrentScene ()->attach (std::move (entityLight));
  engine->getCurrentScene ()->attach (std::move (wall));
  engine->getCurrentScene ()->attach (std::move (cactus1));
  engine->getCurrentScene ()->attach (std::move (cactus2));
  engine->getCurrentScene ()->attach (std::move (cactus3));

  engine->configureFPSCounter ("bridgenorth", glm::vec2 (0.6, 0.9), 70.0);
}
