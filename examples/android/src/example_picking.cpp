/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>

#include "../../android/inc/CallbacksEGL/ColorPickingCallback.h"
#include "../../android/src/PickableModel.h"

using namespace fillwave;

void perform(fillwave::Engine* engine) {
    /* Scene */
    pScene scene = buildScene();

    /* Camera */
    pCameraPerspective camera = pCameraPerspective ( new space::CameraPerspective(glm::vec3(0.0,2.0,18.0),
                                                                glm::quat(),
                                                                glm::radians(90.0),
                                                                1.0,
                                                                0.1,
                                                                1000.0));

    scene->setCamera(camera);
    engine->setCurrentScene(scene);

    /* Program */
    loader::ProgramLoader loader;
    core::Program* program = loader.getDefault();
    core::Program* aprogram = loader.getDefaultBones();

    pModel beast_animated = buildModel(engine, aprogram, "beast.dae");
    pModel beast_animated1 = buildModel(engine, aprogram, "beast.dae");
    pText pick = engine->storeText("Nothing picked", "bridgenorth", -0.95, -0.45, 100.0);
    pModel beast_animated2 = pModel(new PickableModel("pickable beast", pick, engine, aprogram, "beast.dae"));

    beast_animated->moveTo(glm::vec3(0.0,-2.0,0.0));
    beast_animated->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);

    beast_animated1->moveTo(glm::vec3(2.0,-2.0,0.0));
    beast_animated1->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);

//                beast_animated2->scaleTo(0.1);
    beast_animated2->moveTo(glm::vec3(-2.0,-2.0,0.0));
    beast_animated2->setActiveAnimation(0);

    scene->attach(beast_animated);
    scene->attach(beast_animated1);
    scene->attach(beast_animated2);

    /* Skybox */
    pTexture3D textureCubemap = engine->storeTexture3D("emerald_right.jpg",
                                                                 "emerald_left.jpg",
                                                                 "emerald_top.jpg",
                                                                 "",
                                                                 "emerald_front.jpg",
                                                                 "emerald_back.jpg");

    pSkybox skybox = buildSkybox(engine,
                                 "sphere_skybox.obj",
                                 textureCubemap);

    skybox->scaleTo(100.0);
    scene->setSkybox(skybox);

    /* Text */
    pText text = engine->storeText("Fillwave Android example", "bridgenorth", -0.95, 0.95, 50.0);

    /* Specular and normal mapping*/
    pEntity entity1 = buildEntity();
    pEntity entity2 = buildEntity();

    pLightSpot l1 = engine->storeLightSpot(glm::vec3 (0.0,1.0,0.0),
                            glm::quat(),
                            glm::vec4 (1.0,1.0,1.0,0.0),
                            entity1);

    entity1->rotateByX(glm::radians(-90.0));

    entity1->moveBy(glm::vec3(0.0,2.0,0.0));

    entity1->attach(buildModel(engine,
                                   program,
                                   "sphere.obj",
                                   "255_255_255.color"));

    pModel wall = buildModel(engine,
                             program,
                             "floor.obj",
                             "stonetiles.png", /* diffuse map */
                             "stonetiles_n.png", /* normals map */
                             "stonetiles_s.png");/* specular map */

    scene->attach(wall);
    wall->moveInDirection(glm::vec3(0.0,-2.0,0.0));


    actions::SequenceCallback* seq = new actions::SequenceCallback();
    seq->push_back(new actions::TimedMoveCallback(entity1, glm::vec3(16.0,0.0,0.0), 10.0));
    seq->push_back(new actions::TimedMoveCallback(entity1, glm::vec3(-16.0,0.0,0.0), 10.0));
    actions::LoopCallback* loo = new actions::LoopCallback(seq, FILLWAVE_ENDLESS);
    entity1->attachHierarchyCallback(loo);

    entity1->scaleTo(0.02);
    entity1->moveBy(glm::vec3(-8.0,4.0,0.0));
    scene->attach(entity1);

    engine->configureDebugger(eDebuggerState::pickingMap);
    scene->registerPickable(beast_animated);
    scene->registerPickable(beast_animated1);
    scene->registerPickable(beast_animated2);
    engine->registerTouchScreenCallback(new actions::ColorPickingCallback());
}
