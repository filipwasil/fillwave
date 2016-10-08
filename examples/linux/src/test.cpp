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

/* Physics */
//#include <bullet>
using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

const GLint SPHERES = 5;

int main(int argc, char* argv[]) {
	ContextGLFW mContext(argc, argv);
	ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(), mContext.getScreenHeight());
	init();
	perform();
	showDescription();
	mContext.render();
	exit(EXIT_SUCCESS);
}

void init() {
	/* Scene and camera */
	ContextGLFW::mGraphicsEngine->setCurrentScene(make_unique<Scene>());
	ContextGLFW::mGraphicsEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

	/* Lights */
	ContextGLFW::mGraphicsEngine->storeLightSpot(glm::vec3(0.0, 0.0, 5.0), glm::quat(), glm::vec4(0.0, 1.0, 0.0, 0.0));

	/* Engine callbacks */
	ContextGLFW::mGraphicsEngine->registerCallback(make_unique<TimeStopCallback> (ContextGLFW::mGraphicsEngine));
	ContextGLFW::mGraphicsEngine->registerCallback(make_unique<MoveCameraCallback>(ContextGLFW::mGraphicsEngine, eEventType::eKey, 0.1));
}

void perform() {
	core::Program* p = ProgramLoader(ContextGLFW::mGraphicsEngine).getDefault();

	/* Models */
	BuilderModelExternalMaps builder(ContextGLFW::mGraphicsEngine,
	                                 "meshes/sphere.obj",
	                                 p, "textures/test.png");

	const glm::vec3 upY (0.0f, 1.0f, 0.0f);
	const glm::vec3 downY (0.0f, 1.0f, 0.0f);
	for (GLint i = 0; i < SPHERES; i++) {
		/* build */

		puModel sphere = builder.build();

		/* move */
		sphere->scaleTo(0.1);
		sphere->moveByX(-4 + 2 * i);

		sphere->attachHierarchyCallback(make_unique<LoopCallback>(std::move(make_unique_container<SequenceCallback>(
		                                   make_unique<TimedScaleCallback>(sphere.get(), 0.1f * 2.0f, 2.0f + i * 0.5f, CircularEaseIn),
		                                   make_unique<TimedScaleCallback>(sphere.get(), 0.1f * 1.0f, 2.0f + i * 0.5f, ElasticEaseIn),
		                                   make_unique<TimedRotateCallback>(sphere.get(), upY, glm::radians(90.0f), 2.0f + i * 0.5f, BounceEaseIn),
		                                   make_unique<TimedRotateCallback>(sphere.get(), upY, glm::radians(90.0f), 2.0f + i * 0.5f, BounceEaseOut),
		                                   make_unique<TimedMoveCallback>(sphere.get(), downY, 2.0f + i * 0.5f))), FILLWAVE_ENDLESS));

		ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(sphere));
	}

	puModel wall = make_unique<Model>(ContextGLFW::mGraphicsEngine, p, "meshes/floor.obj", "textures/test.png");
	wall->rotateByX(glm::radians(90.0));
	wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
	wall->scaleTo(3.0);
	ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(wall));
}

void quit() {
//
}

void showDescription() {
	pText hint0 = ContextGLFW::mGraphicsEngine->storeText("Fillwave example callbacks", "fonts/Titania", glm::vec2(-0.95,
	              0.80), 100.0);
	pText hint3 = ContextGLFW::mGraphicsEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95,
	              -0.50), 70.0);
	pText hint4 = ContextGLFW::mGraphicsEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95,
	              -0.60), 70.0);
	pText hint1 = ContextGLFW::mGraphicsEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95,
	              -0.70), 70.0);
	pText hint6 = ContextGLFW::mGraphicsEngine->storeText("Use 'D' for toggle debugger On/Off", "fonts/Titania",
	              glm::vec2(-0.95, -0.80), 70.0);
}