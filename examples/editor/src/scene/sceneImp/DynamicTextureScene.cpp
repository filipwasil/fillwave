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
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <fillwave/Fillwave.h>

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

	/* Entities */
	puEntity light = buildEntity();
	light->moveTo(glm::vec3(0.0, 0.0, 3.0));

	/* Texture */
	flc::Texture2D* textureN =
	   mEngine->storeTexture("255_255_255.color");
	flc::Texture2D* textureS = mEngine->storeTexture("");

	/* Lights */
	mEngine->storeLightSpot(glm::vec3 (1.0, 1.0, 3.0),
	      glm::quat (),
	      glm::vec4 (1.0, 1.0, 1.0, 0.0),
	      light.get());

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>(
	         mEngine));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(
	         mEngine, eEventType::eKey, 0.1));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(
	         mEngine, eEventType::eCursorPosition, 0.1,
	         ContextGLFW::mWindow));
}

void perform() {
	puModel model = make_unique<Model>(mEngine,
	                                   ProgramLoader(mEngine).getDefault(), "meshes/sphere.obj",
	                                   mEngine->storeTextureDynamic("shaders/water/water.frag"));
	model->moveBy(glm::vec3(0.0, 0.0, -15.0));
	mEngine->getCurrentScene().attach(std::move(model));
}

void showDescription() {
	/* Description */
	pText hint5 =
	   mEngine->storeText("Use mouse to move the camera",
	         "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
	pText hint3 = mEngine->storeText("Use 'S' for camera back",
	              "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 =
	   mEngine->storeText("Use 'W' for camera forward",
	         "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 =
	   mEngine->storeText("Use 'T' to resume/stop time",
	         "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 =
	   mEngine->storeText("Use 'D' for toggle debugger On/Off",
	         "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}
