/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>

using namespace fillwave;

void perform(fillwave::Engine *engine) {

  /* Scene */
  pScene gScene = buildScene ();

  /* Camera */
  pCameraPerspective gCamera = pCameraPerspective (new space::CameraPerspective (glm::vec3 (0.0, 0.0, 6.0),
                                                                                 glm::quat (),
                                                                                 glm::radians (90.0),
                                                                                 1.0,
                                                                                 0.1,
                                                                                 1000.0));
  /* Textures */
  pTexture gTexture = engine->storeTexture ("particle.png");

  /* Set current scene */
  engine->setCurrentScene (gScene);

  /* Attach camera to scene */
  gScene->setCamera (gCamera);

  /* Attach emiters to entities */

  pEmiterPoint water = pEmiterPoint (new ::particles::EmiterPointPolynomial (engine,
                                                                             0.3,
                                                                             100000.0,
                                                                             glm::vec4 (0.1, 0.1, 1.0, 1.0),
                                                                             glm::vec3 (0.0, 20.0, 0.0),
                                                                             glm::vec3 (0.0, 0.0, 0.0),
                                                                             glm::vec3 (0.9, 0.9, 0.9),
                                                                             glm::vec3 (0.0, 0.0, 0.0),
                                                                             glm::vec3 (0.0, 0.0, 0.0),
                                                                             10.0,
                                                                             15.0,
                                                                             gTexture,
                                                                             GL_SRC_ALPHA,
                                                                             GL_ONE,
                                                                             GL_FALSE));
  water->moveBy (glm::vec3 (0.0, -1.0, -1.0));

  pEmiterPoint sand = pEmiterPoint (new ::particles::EmiterPointPolynomial (engine,
                                                                            0.3,
                                                                            100000.0,
                                                                            glm::vec4 (1.0, 1.0, 0.0, 1.0),
                                                                            glm::vec3 (0.0, 0.0, 0.0),
                                                                            glm::vec3 (0.0, 0.0, 0.0),
                                                                            glm::vec3 (10.9, 10.9, 10.9),
                                                                            glm::vec3 (0.0, 0.0, 0.0),
                                                                            glm::vec3 (0.0, 0.0, 0.0),
                                                                            10.0,
                                                                            15.0,
                                                                            gTexture,
                                                                            GL_SRC_ALPHA,
                                                                            GL_ONE,
                                                                            GL_FALSE));

  pEmiterPoint snow = pEmiterPoint (new ::particles::EmiterPointGPU (engine,
                                                                     0.3,
                                                                     600.0,
                                                                     glm::vec4 (1.0, 1.0, 1.0, 1.0),
                                                                     glm::vec3 (0.0, 1.0, 0.0),
                                                                     glm::vec3 (0.0, 0.0, 0.0),
                                                                     glm::vec3 (10.9, 10.9, 10.9),
                                                                     glm::vec3 (0.0, 0.0, 0.0),
                                                                     glm::vec3 (0.6, 0.6, 0.6),
                                                                     1.0,
                                                                     1.0,
                                                                     gTexture,
                                                                     GL_SRC_ALPHA,
                                                                     GL_ONE,
                                                                     GL_FALSE));

  gScene->attach (sand);
  gScene->attach (water);
  gScene->attach (snow);

  /* For time updates */
  snow->attachHierarchyCallback (new actions::TimedEmiterUpdateCallback (snow, FILLWAVE_ENDLESS));
  water->attachHierarchyCallback (new actions::TimedEmiterUpdateCallback (water, FILLWAVE_ENDLESS));
  sand->attachHierarchyCallback (new actions::TimedEmiterUpdateCallback (sand, FILLWAVE_ENDLESS));

}
