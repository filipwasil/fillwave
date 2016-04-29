//============================================================================
// Name        : example_animation.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example animation
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
#include <fillwave/Framework.h>

/* Physics */
//#include <bullet>

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

map<string, core::Program*> gPrograms;

int main(int argc, char* argv[]) {
	ContextGLFW mContext;
	ContextGLFW::mGraphicsEngine = new Engine(argc, argv);
	ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(),
	      mContext.getScreenHeight());
	init();
	perform();
	showDescription();
	mContext.render();
	delete ContextGLFW::mGraphicsEngine;
	exit(EXIT_SUCCESS);
}

void init() {
	/* Scenes */
	ContextGLFW::mGraphicsEngine->setCurrentScene(make_unique<IScene>());

	/* Engine callbacks */
	ContextGLFW::mGraphicsEngine->registerCallback(make_unique<TimeStopCallback>
	      (ContextGLFW::mGraphicsEngine));
	ContextGLFW::mGraphicsEngine->registerCallback(make_unique<MoveCameraCallback>
	      (ContextGLFW::mGraphicsEngine, eEventType::eKey, 0.1));
	ContextGLFW::mGraphicsEngine->registerCallback(make_unique<MoveCameraCallback>
	      (ContextGLFW::mGraphicsEngine, eEventType::eCursorPosition, 0.05,
	       ContextGLFW::mWindow));
}

void perform() {
	ContextGLFW::mGraphicsEngine->getCurrentScene()->setCamera(
	   make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 4.0),
	                                  glm::quat(),
	                                  glm::radians(90.0),
	                                  1.0,
	                                  0.1,
	                                  1000.0));

	puModel beast = make_unique<Model>(ContextGLFW::mGraphicsEngine,
	                                   ProgramLoader(ContextGLFW::mGraphicsEngine).getDefaultBones(),
	                                   "animations/beast/beast.dae");
	beast->attachHierarchyCallback(make_unique<AnimationKeyboardCallback>
	                               (beast.get(), eEventType::eKey));
	ContextGLFW::mGraphicsEngine->registerCallback(
	   make_unique<AnimationKeyboardCallback>(beast.get(), eEventType::eKey),
	   beast.get());
	beast->scaleTo(0.5);
	ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(std::move(beast));
}

void showDescription() {
	pText hint0 =
	   ContextGLFW::mGraphicsEngine->storeText("Fillwave example animation",
	         "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
	pText hint1 =
	   ContextGLFW::mGraphicsEngine->storeText("Use 'T' to resume/stop time",
	         "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	pText hint2 =
	   ContextGLFW::mGraphicsEngine->storeText("Use '0' for start Animating",
	         "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	pText hint3 = ContextGLFW::mGraphicsEngine->storeText("Use 'S' for camera back",
	              "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 =
	   ContextGLFW::mGraphicsEngine->storeText("Use 'W' for camera forward",
	         "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
	pText hint5 =
	   ContextGLFW::mGraphicsEngine->storeText("Use mouse to move the camera",
	         "fonts/Titania", glm::vec2(-0.95, -0.30), 70.0);
	pText hint6 =
	   ContextGLFW::mGraphicsEngine->storeText("Use 'D' for toggle debugger On/Off",
	         "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}