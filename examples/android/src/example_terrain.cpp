/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <flw/Fillwave.h>
#include <flw/extras/Log.h>
#include <flw/flf/models/shapes/Sphere.h>
#include "../../android/inc/TerrainConstructors/PerlinConstructor.h"

using namespace flw;

void perform(flw::Engine *engine) {
  /* Scene */
  pScenePerspective scene = buildScenePerspective();

  /* Camera */
  pCameraPerspective camera = pCameraPerspective(new space::CameraPerspective(glm::vec3(0.0, 2.0, 8.0),
                                                                              glm::quat(),
                                                                              glm::radians(90.0),
                                                                              1.0,
                                                                              0.1,
                                                                              1000.0));

  scene->setCamera(camera);
  engine->setCurrentScene(scene);

  /* Program */
  loader::ProgramLoader loader;
  flc::Program *program = loader.getDefault(engine);
  flc::Program *aprogram = loader.getDefaultBones(engine);

  pShader vertex = engine->storeShaderVertex("default.vert");

  /* Skybox */
  flw::flf::ps<flw::flf::Text>ure3D textureCubemap = engine->storeTexture3D("emerald_right.jpg",
                                                     "emerald_left.jpg",
                                                     "emerald_top.jpg",
                                                     "",
                                                     "emerald_front.jpg",
                                                     "emerald_back.jpg");

  pSkybox skybox = buildSkybox(engine, textureCubemap);

  skybox->scaleTo(100.0);
  scene->setSkybox(skybox);

  /* Text */
  flw::flf::ps<flw::flf::Text> text = engine->storeText("Fillwave terrain example", "bridgenorth", -0.95, 0.95, 100.0);

  /* Specular and normal mapping*/
  pEntity entity1 = buildEntity();

  pLightSpot l1 = engine->storeLightSpot(glm::vec3(0.0, 0.6, 0.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), entity1);

  entity1->rotateByX(glm::radians(-90.0));

  entity1->moveBy(glm::vec3(-1.0, 4.0, 0.0));

  pModel beast_animated = make_unique<Model>(engine, aprogram, "beast.dae");

  scene->attach(beast_animated);

//   actions::SequenceCallback* seq = new actions::SequenceCallback();
//   seq->push_back(new actions::TimedMoveCallback(entity1, glm::vec3(16.0,0.0,0.0), 10.0));
//   seq->push_back(new actions::TimedMoveCallback(entity1, glm::vec3(-16.0,0.0,0.0), 10.0));
//   actions::LoopCallback* loo = new actions::LoopCallback(seq, FILLWAVE_ENDLESS);
//   entity1->attachHierarchyCallback(loo);
//
//   entity1->scaleTo(0.02);
  scene->attach(entity1);

  models::Material material;

  pMeshTerrain terrain = pMeshTerrain(new terrain::MeshTerrain(engine,
                                                               program,
                                                               program,
                                                               new terrain::PerlinConstructor(),
                                                               material,
                                                               "test.png",
                                                               "test.png",
                                                               "test.png",
                                                               2));
//   pTerrain gTerrain = buildTerrain(engine,
//		                   program,
//                           "test.png",
//                           new terrain::PerlinConstructor(),
//                           2);

//   scene->attach(terrain);

//   scene->attach(pEntity(new models::Sphere(engine, 1.0, 10, 10)));
//   scene->setTerrain(gTerrain);
}
