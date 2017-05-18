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
#include <CallbacksGLFW/FollowCustomCursorCallback.h>
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

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
	      (mEngine, eEventType::eKey, 0.1));
}

void perform() {
	/* Cursor texture */
	flc::Texture2D* textureC =
	   mEngine->storeTexture("textures/cursor/standard_blue.png")
	   ;

	/* Cursor */
	mEngine->getCurrentScene().setCursor(make_unique<Cursor>
	      (mEngine, textureC));

	/* Make cursor visible for current scene */
	mEngine->registerCallback(
	   make_unique<FollowCustomCursorCallback>(mEngine));
}

void showDescription() {
	/* Description */
	pText description =
	   mEngine->storeText("Fillwave example cursor",
	         "fonts/Titania",
	         glm::vec2(-0.95,
	                   0.95),
	         100.0);
}
