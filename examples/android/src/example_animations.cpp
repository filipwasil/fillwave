/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

using namespace flw;
using namespace flw::framework;

void perform(Engine *engine) {
  /* Scene */
  pScene scene = buildScene();

  /* Camera */
  pCameraPerspective camera = pCameraPerspective(new CameraPerspective(glm::vec3(0.0, 2.0, 18.0),
                                                                       glm::quat(),
                                                                       glm::radians(90.0),
                                                                       1.0,
                                                                       0.1,
                                                                       1000.0));

  scene->setCamera(camera);
  engine->setCurrentScene(scene);

  /* Program */
  ProgramLoader loader(engine);
  flc::Program *program = loader.getDefault();
  flc::Program *aprogram = loader.getDefaultBones();

  puModel beast_animated = make_unique<Model>(engine, aprogram, "beast.dae");
  puModel beast_animated1 = make_unique<Model>(engine, aprogram, "beast.dae");
  puModel beast_animated2 = make_unique<Model>(engine, aprogram, "beast.dae");

  beast_animated->moveTo(glm::vec3(0.0, -2.0, 0.0));
  beast_animated->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);

  beast_animated1->moveTo(glm::vec3(2.0, -2.0, 0.0));
  beast_animated1->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);

//                beast_animated2->scaleTo(0.1);
  beast_animated2->moveTo(glm::vec3(-2.0, -2.0, 0.0));
  beast_animated2->setActiveAnimation(0);

  scene->attach(beast_animated);
  scene->attach(beast_animated1);
  scene->attach(beast_animated2);

  /* Skybox */
  flw::flf::ps<flw::flf::Text>ure3D textureCubemap = engine->storeTexture3D("emerald_right.jpg",
                                                     "emerald_left.jpg",
                                                     "emerald_top.jpg",
                                                     "",
                                                     "emerald_front.jpg",
                                                     "emerald_back.jpg");

  pSkybox skybox = buildSkybox(engine, "sphere_skybox.obj", textureCubemap);

  skybox->scaleTo(100.0);
  scene->setSkybox(skybox);

  /* Text */
  flw::flf::ps<flw::flf::Text> text = engine->storeText("Fillwave Android example", "bridgenorth", -0.95, 0.95, 100.0);

  /* Specular and normal mapping*/
  pEntity entity1 = buildEntity();

  pLightSpot l1 = engine->storeLightSpot(glm::vec3(1.0, 0.6, 0.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), entity1);


//    entity1->rotateBy(glm::vec3(1.0,0.0,0.0), glm::radians(90.0f));
  entity1->rotateByX(glm::radians(-90.0));
  //                l2->getShadowCamera()->rotateByX(glm::radians(-90.0));

//    entity1->moveBy(glm::vec3(0.0,16.0,0.0));
//    entity1->attach(make_unique<Model>(engine,
//                                   program,
//                                   "sphere.obj",
//                                   "255_255_255.color"));

  pModel wall = buildModel(engine, program, "floor.obj", "stonetiles.png",   /* diffuse map */
                           "stonetiles_n.png", /* normals map */
                           "stonetiles_s.png");/* specular map */

  scene->attach(wall);
  wall->moveInDirection(glm::vec3(0.0, -2.0, 0.0));

  SequenceCallback *seq = new SequenceCallback();
  seq->push_back(new TimedMoveCallback(entity1, glm::vec3(16.0, 0.0, 0.0), 10.0));
  seq->push_back(new TimedMoveCallback(entity1, glm::vec3(-16.0, 0.0, 0.0), 10.0));
  LoopCallback *loo = new LoopCallback(seq, FILLWAVE_ENDLESS);
  entity1->attachHierarchyCallback(loo);

  entity1->scaleTo(0.02);
  scene->attach(entity1);

  flw::flf::ps<flw::flf::Text>ure gTexture = engine->storeTexture("fire.png");
  pEmiterPointGPU e = pEmiterPointGPU(new EmiterPointGPU(engine,
                                                         0.3,
                                                         2000.0,
                                                         glm::vec4(1.0, 1.0, 1.0, 1.0),
                                                         glm::vec3(0.0, 0.0, 0.0),
                                                         glm::vec3(0.0, 0.5, 0.0),
                                                         glm::vec3(0.1, 0.0, 0.1),
                                                         glm::vec3(0.0, 0.0, 0.0),
                                                         glm::vec3(0.2, 0.0, 0.2),
                                                         1.0,
                                                         1.0,
                                                         gTexture,
                                                         GL_SRC_ALPHA,
                                                         GL_ONE,
                                                         GL_FALSE));

  e->attachHierarchyCallback(new TimedEmiterUpdateCallback(e, FILLWAVE_ENDLESS));
//	   scene->attach(e);
  entity1->attach(e);

//    engine->configureDebugger(EDebuggerState::lightsSpot);
}
