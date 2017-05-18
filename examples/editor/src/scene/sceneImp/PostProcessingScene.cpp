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
#include <fillwave/Log.h>

/* Physics */
//#include <bullet>

using namespace flw;
using namespace flw::flf;
using namespace std;

FLOGINIT("Test app", FERROR | FFATAL)

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
	/* Entities */
	puEntity entity = buildEntity();

	/* Texture */
	mEngine->addPostProcess("shaders/process/process1.frag",
	      8.0);

	flc::Texture2D* textureDynamic =
	   mEngine->storeTextureDynamic("shaders/water/water.frag");

	/* Models */

	puModel model = make_unique<Model>(mEngine,
	                                   ProgramLoader(mEngine).getDefault(),
	                                   "meshes/sphere.obj",
	                                   textureDynamic);
	model->moveBy(glm::vec3(0.0, 0.0, -15.0));

	/* Lights */
	mEngine->storeLightSpot(glm::vec3 (1.0, 1.0, 3.0),
	      glm::quat(),
	      glm::vec4 (1.0, 1.0, 1.0, 0.0),
	      entity.get());

	entity->moveTo(glm::vec3(0.0, 0.0, 3.0));

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>(
	         mEngine));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(
	         mEngine, eEventType::eKey, 0.1));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(
	         mEngine, eEventType::eCursorPosition, 0.1,
	         ContextGLFW::mWindow));

	mEngine->getCurrentScene().attach(std::move(model));
}

void perform() {

}

void showDescription() {
	/* Description */
	pText description =
	   mEngine->storeText("Fillwave example post processing shader",
	         "fonts/Titania",
	         glm::vec2(-0.95, 0.95), 100.0);
}
