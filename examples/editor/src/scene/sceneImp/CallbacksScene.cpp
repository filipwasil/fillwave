//============================================================================
// Name        : example_callbacks.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example callbacks
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>
/* Graphics */
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

/* Physics */
//#include <bullet>
using namespace flw;
using namespace flw::flf;
using namespace std;

const GLuint SPHERES = 5;

void CallbacksScene::init() {
	pText hint0 =
			mEngine->storeText("Fillwave example callbacks",
			                                        "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
	pText hint3 = mEngine->storeText("Use 'S' for camera back",
	                                                      "fonts/Titania",
	                                                      glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 =
			mEngine->storeText("Use 'W' for camera forward",
			                                        "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 =
			mEngine->storeText("Use 'T' to resume/stop time",
			                                        "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 =
			mEngine->storeText("Use 'D' for toggle debugger On/Off",
			                                        "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);

	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene().setCamera(
	   make_unique<CameraPerspective>());


	/* Lights */
	mEngine->storeLightSpot(glm::vec3(0.0, 0.0, 5.0),
	      glm::quat(),
	      glm::vec4(0.0, 1.0, 0.0, 0.0));

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>
	      (mEngine));
	mEngine->registerCallback(make_unique
	      <MoveCameraCallback>(mEngine, eEventType::eKey, 0.1));
}

void CallbacksScene::perform() {
	flc::Program* p = ProgramLoader(mEngine).getDefault();

	/* Models */
	BuilderModelExternalMaps builder(mEngine,
	                                 "meshes/sphere.obj",
	                                 p, "textures/test.png");

	for (GLint i = 0; i < SPHERES; i++) {
		/* build */

		puModel sphere = builder.build();

		/* move */
		sphere->scaleTo(0.1);
		sphere->moveByX(-4 + 2 * i);

		sphere->attachHierarchyCallback(make_unique<LoopCallback>(
				std::move(make_unique_container<SequenceCallback>
								  (make_unique<TimedScaleCallback>(
										  sphere.get(), 0.1 * 2.0,
										  2.0f + i * 0.5, CircularEaseIn),
								   make_unique<TimedScaleCallback>(
										   sphere.get(), 0.1 * 1.0,
										   2.0f + i * 0.5, ElasticEaseIn),
								   make_unique<TimedRotateCallback>(
										   sphere.get(),
										   glm::vec3(0.0, 1.0, 0.0),
										   glm::radians(90.0f), 2.0f + i * 0.5,
										   BounceEaseIn),
								   make_unique<TimedRotateCallback>(
										   sphere.get(),
										   glm::vec3(0.0, 1.0, 0.0),
										   glm::radians(90.0f), 2.0f + i * 0.5,
										   BounceEaseOut),
								   make_unique<TimedMoveCallback>(
										   sphere.get(),
										   glm::vec3(0.0, -1.0, 0.0),
										   2.0f + i * 0.5))),
				FILLWAVE_ENDLESS));

		mEngine->getCurrentScene().attach(std::move(sphere));
	}

	puModel wall = make_unique<Model>(mEngine, p,
	                                  "meshes/floor.obj");
	wall->rotateByX(glm::radians(90.0));
	wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
	wall->scaleTo(3.0);
	mEngine->getCurrentScene().attach(std::move(wall));
}

void CallbacksScene::quit() {
//
}

void showDescription() {

}
