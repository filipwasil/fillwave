//============================================================================
// Name        : example_skybox.cpp
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
	   make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
	                                  glm::quat(),
	                                  glm::radians(90.0),
	                                  1.0,
	                                  0.1,
	                                  1000.0));

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
	mEngine->getCurrentScene().setSkybox(make_unique<Skybox>
	      (mEngine,
	       mEngine->storeTexture3D("textures/skybox/emerald/emerald_right.jpg",
	             "textures/skybox/emerald/emerald_left.jpg",
	             "textures/skybox/emerald/emerald_top.jpg",
	             "",
	             "textures/skybox/emerald/emerald_front.jpg",
	             "textures/skybox/emerald/emerald_back.jpg")));
}

void showDescription() {
	pText hint0 = mEngine->storeText("Fillwave example skybox",
	              "fonts/Titania",
	              glm::vec2(-0.95, 0.80), 100.0);
}

