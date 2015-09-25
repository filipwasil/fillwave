/*
 * example_animations_with_light.cpp
 *
 *  Created on: 8 Apr 2015
 *      Author: filip
 */

#include <fillwave/Fillwave.h>
#include <fillwave/extras/Log.h>
#include <fillwave/models/shapes/Quad.h>

using namespace fillwave;

void perform(fillwave::Engine* engine) {
    /* Scene */
    pScenePerspective scene = buildScenePerspective();

    /* Camera */
    pCameraPerspective camera = pCameraPerspective ( new space::CameraPerspective (glm::vec3(0.0,2.0,18.0),
                               glm::quat(),
                               glm::radians(90.0),
                               1.0,
                               0.1,
                               1000.0));
    const GLuint SPHERES = 5;
    pModel gSpheres[SPHERES];
    actions::LoopCallback* loop[SPHERES];

    scene->setCamera(camera);
    engine->setCurrentScene(scene);

    /* Program */
    loader::ProgramLoader loader;
    pProgram program = loader.getDefault(engine);
//    pProgram program = loader.getDefaultDeferredGeometry(engine);
    pProgram aprogram = loader.getDefaultBones(engine);

    pEffect e = pEffect (new effects::TextureOnly());
    pEffect f = pEffect (new effects::Fog());

    pModel cactus1 = buildModel(engine, aprogram, "beast.dae");
    pModel cactus2 = buildModel(engine, aprogram, "beast.dae");
    pModel cactus3 = buildModel(engine, aprogram, "beast.dae");

    cactus1->moveTo(glm::vec3(0.0,-2.0,0.0));
    cactus1->rotateBy(glm::vec3(1.0,0.0,0.0), glm::radians(90.0));
    cactus1->setActiveAnimation(0);
    scene->attach(cactus1);
    cactus1->addEffect(e);
    cactus1->addEffect(f);

    cactus2->moveTo(glm::vec3(4.0,-2.0,0.0));
    cactus2->rotateBy(glm::vec3(1.0,0.0,0.0), glm::radians(90.0));
    cactus2->setActiveAnimation(0);
    scene->attach(cactus2);
    cactus2->addEffect(e);
    cactus2->addEffect(f);

    cactus3->moveTo(glm::vec3(-4.0,-2.0,0.0));
    cactus3->rotateBy(glm::vec3(1.0,0.0,0.0), glm::radians(90.0));
    cactus3->setActiveAnimation(0);
    scene->attach(cactus3);
    cactus3->addEffect(e);
    cactus3->addEffect(f);

    /* Skybox */
    pTexture3D textureCubemap = engine->storeTexture3D("emerald_right.jpg",
                                                       "emerald_left.jpg",
                                                       "emerald_top.jpg",
                                                       "",
                                                       "emerald_front.jpg",
                                                       "emerald_back.jpg");

    pSkybox skybox = buildSkybox(engine,
                                 textureCubemap);
    scene->setSkybox(skybox);

    /* Text */
    pText text = engine->storeText("Fillwave example", "bridgenorth", -0.95, 0.95, 100.0);

    /* Specular and normal mapping*/
    pEntity entity1 = buildEntity();

    pLightDirectional l1 = engine->storeLightDirectional(glm::vec3 (0.0,0.6,0.0),
                            glm::quat(),
                            glm::vec4 (1.0,1.0,1.0,1.0),
                            entity1);

    entity1->rotateByX(glm::radians(-90.0));

    entity1->moveBy(glm::vec3(-8.0,8.0,0.0));

    entity1->attach(buildModel(engine,
                               program,
                               "sphere.obj",
                               "255_255_255.color"));

    pModel wall = buildModel(engine,
                             program,
                             "floor.obj",
                             "stonetiles.png",   /* diffuse map */
                             "stonetiles_n.png", /* normals map */
                             "stonetiles_s.png");/* specular map */
   wall->moveBy(glm::vec3(0.0,-3.0,0.0));
   scene->attach(wall);

   actions::SequenceCallback* seq = new actions::SequenceCallback();
   seq->push_back(new actions::TimedMoveCallback(entity1, glm::vec3(16.0,0.0,0.0), 10.0));
   seq->push_back(new actions::TimedMoveCallback(entity1, glm::vec3(-16.0,0.0,0.0), 10.0));
   actions::LoopCallback* loo = new actions::LoopCallback(seq, FILLWAVE_ENDLESS);
   entity1->attachHierarchyCallback(loo);

   entity1->scaleTo(0.02);
   scene->attach(entity1);

   engine->configureFPSCounter("bridgenorth",0.6,0.9,70.0);
}
