//============================================================================
// Name        : example_lights.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example lights
//============================================================================

#include <fillwave/Fillwave.h>
#include <example.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>

/* Physics */
//#include <bullet>

using namespace flw;
using namespace flw::flf;
using namespace std;

void init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene().setCamera(
	   make_unique<CameraPerspective>());

	/* Programs */
	loader::ProgramLoader loader;
	gPrograms.insert(pair<string, pProgram>("default", loader.getDefault(gEngine)));
	gPrograms.insert(pair<string, pProgram>("animation",
	                                        loader.getDefaultBones(gEngine)));

	/* Entities */
	gEntities.insert(pair<string, pEntity>("wall", buildEntity()));
	gEntities.insert(pair<string, pEntity>("lightSource", buildEntity()));

	/* Lights */
	gEngine->storeLightSpot(glm::vec3 (0.0, 1.0, 0.0),
	                        glm::quat(),
	                        glm::vec4 (1.0, 1.0, 1.0, 0.0),
	                        gEntities["lightSource"] );

	/* Engine callbacks */
	gEngine->registerCallback(new actions::TimeStopCallback());
	gEngine->registerCallback(new actions::MoveCameraCallback(eEventType::eKey,
	                          0.1));
	gEngine->registerCallback(new actions::MoveCameraCallback(
	                             eEventType::eCursorPosition, 0.1, ContextGLFW::mWindow));
}

void perform() {
	/* Attach entities to scene */
	gScene->attach(gEntities["wall"] );
	gScene->attach(gEntities["lightSource"] );

	/* Attach camera to scene */
	gScene->setCamera(gCamera);

	pModel sphere = buildModel(gEngine, gPrograms["default"], "meshes/sphere.obj",
	                           "255_255_255.color");
	pModel wall = buildModel(gEngine, gPrograms["default"], "meshes/floor.obj");
	pModel beast = pModel ( new models::Model(gEngine, gPrograms["animation"],
	                        "animations/beast/beast.dae"));

	gScene->attach(beast);
	gEntities["lightSource"]->attach(sphere);
	gEntities["wall"]->attach(wall);

	/* Manipulate objects directly */
	gEntities["wall"]->rotateByX(glm::radians(90.0));
	gEntities["wall"]->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
	gEntities["wall"]->scaleTo(3.0);

	gEntities["lightSource"]->attachHierarchyCallback(new
	      actions::TimedMoveCallback(gEntities["lightSource"], glm::vec3(0.0, 0.0, 500.0),
	                                 2000.0));
	gEntities["lightSource"]->scaleTo(0.02);
	gEntities["lightSource"]->moveBy(glm::vec3(0.0, 0.0, 10.0));
}

void showDescription() {
	pText hint0 = gEngine->storeText("Fillwave example lights", "fonts/Titania",
	                                 -0.95, 0.80, 100.0);
	pText hint5 = gEngine->storeText("Use mouse to move the camera",
	                                 "fonts/Titania", -0.95, -0.40, 70.0);
	pText hint3 = gEngine->storeText("Use 'S' for camera back", "fonts/Titania",
	                                 -0.95, -0.50, 70.0);
	pText hint4 = gEngine->storeText("Use 'W' for camera forward", "fonts/Titania",
	                                 -0.95, -0.60, 70.0);
	pText hint1 = gEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania",
	                                 -0.95, -0.70, 70.0);
	pText hint6 = gEngine->storeText("Use 'D' for toggle debugger On/Off",
	                                 "fonts/Titania", -0.95, -0.80, 70.0);
}
