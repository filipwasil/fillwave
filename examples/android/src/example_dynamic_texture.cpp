/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>

using namespace flw;

void perform(flw::Engine *engine) {
  /* Scene */
  pScene gScene = buildScene();

  /* Camera */
  pCameraPerspective gCamera = pCameraPerspective(new space::CameraPerspective(glm::vec3(0.0, 0.0, 6.0),
                                                                               glm::quat(),
                                                                               glm::radians(90.0),
                                                                               1.0,
                                                                               0.1,
                                                                               1000.0));
  /* Entities */
  pEntity gEntityLight = buildEntity();

  /* Texture */
  pTexture textureDynamic = engine->storeTextureDynamic("water.frag");
  pTexture textureN = engine->storeTexture("255_255_255.color");
  pTexture textureS = engine->storeTexture("");

  /* Shaders */
  pShader fragment = engine->storeShaderFragment("default.frag");
  pShader vertex = engine->storeShaderVertex("default.vert");

  /* Programs */
  flc::Program *gProgram = buildProgram(vertex + fragment);

  /* Models */
  pModel sphere = buildModel(engine, gProgram, "sphere.obj", textureDynamic);

  /* Lights */
  engine->storeLightSpot(glm::vec3(1.0, 1.0, 3.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), gEntityLight);

  gEntityLight->moveTo(glm::vec3(0.0, 0.0, 3.0));

  engine->setCurrentScene(gScene);

  gScene->attach(sphere);

  gScene->setCamera(gCamera);

  sphere->moveBy(glm::vec3(0.0, 0.0, -15.0));

  /* Description */
  pText hint0 = engine->storeText("Fillwave example dynamic texture", "bridgenorth", -0.95, 0.95, 100.0);

  engine->debuggerOn(GL_TRUE);

  engine->setBackgroundColor(glm::vec3(1.0, 1.0, 1.0));
}
