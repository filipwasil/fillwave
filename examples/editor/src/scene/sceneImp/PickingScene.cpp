//============================================================================
// Name        : Client.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example full
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>

/* Graphics */
#include <CallbacksGLFW/ColorPickingCallback.h>
#include <CallbacksGLFW/FollowCustomCursorCallback.h>
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <fillwave/Fillwave.h>
#include "PickableModel.h"

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

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>
	      (mEngine));
	mEngine->registerCallback(make_unique<MoveCameraCallback>
	      (mEngine, eEventType::eKey,
	       0.1));
}

void perform() {
	mEngine->getCurrentScene().setCursor(make_unique<Cursor>
	      (mEngine,
	       mEngine->storeTexture("textures/cursor/standard_blue.png")));

	/* Make cursor visible for current scene */
	mEngine->registerCallback(
	   make_unique<FollowCustomCursorCallback>(mEngine));

	/* Picking info text which will be modified frequently */
	pText pickInfo = mEngine->storeText("Nothing picked",
	                 "fonts/Titania",
	                 glm::vec2(-0.95,
	                           0.80),
	                 60.0);

	auto program = ProgramLoader(mEngine).getDefault();

	/* build ball model */
	puModel ballModel1 = make_unique<PickableModel>("left ball", pickInfo,
	                     mEngine,
	                     program, "meshes/sphere.obj", "64_128_255.checkboard");
	ballModel1->scaleTo(0.1);
	ballModel1->moveBy(glm::vec3(-3.0, 0.0, 0.0));
	puModel ballModel2 = make_unique<PickableModel>("right ball", pickInfo,
	                     mEngine,
	                     program, "meshes/sphere.obj", "64_128_255.checkboard");
	ballModel2->scaleTo(0.1);
	ballModel2->moveBy(glm::vec3(3.0, 0.0, 0.0));
	puModel ballModel3 = make_unique<PickableModel>("center ball", pickInfo,
	                     mEngine,
	                     program, "meshes/sphere.obj", "64_128_255.checkboard");
	ballModel3->scaleTo(0.1);
	puModel ballModel4 = make_unique<PickableModel>("up ball", pickInfo,
	                     mEngine,
	                     program, "meshes/sphere.obj", "64_128_255.checkboard");
	ballModel4->scaleTo(0.1);
	ballModel4->moveBy(glm::vec3(0.0, 3.0, 0.0));
	puModel ballModel5 = make_unique<PickableModel>("down ball", pickInfo,
	                     mEngine,
	                     program, "meshes/sphere.obj", "64_128_255.checkboard");
	ballModel5->scaleTo(0.1);
	ballModel5->moveBy(glm::vec3(0.0, -3.0, 0.0));

	/* Register ball model as a pickable model in scene */
	mEngine->getCurrentScene().registerPickable(
	   ballModel1.get()); // xxx is register pickable safe ?
	mEngine->getCurrentScene().registerPickable(
	   ballModel2.get());
	mEngine->getCurrentScene().registerPickable(
	   ballModel3.get());
	mEngine->getCurrentScene().registerPickable(
	   ballModel4.get());
	mEngine->getCurrentScene().registerPickable(
	   ballModel5.get());

	/* Attach ball model to ball entity */
	mEngine->getCurrentScene().attach(std::move(ballModel1));
	mEngine->getCurrentScene().attach(std::move(ballModel2));
	mEngine->getCurrentScene().attach(std::move(ballModel3));
	mEngine->getCurrentScene().attach(std::move(ballModel4));
	mEngine->getCurrentScene().attach(std::move(ballModel5));

	/* Register picking callback */
	mEngine->registerCallback(
	   make_unique<ColorPickingCallback>(mEngine));
}

void showDescription() {
	/* Description */
	pText description =
	   mEngine->storeText("Fillwave example cursor picking",
	         "fonts/Titania",
	         glm::vec2(-0.95,
	                   0.95),
	         100.0);

	pText hint0 = mEngine->storeText("Pick a sphere",
	              "fonts/Titania",
	              glm::vec2(-0.95, -0.80), 70.0);
}
