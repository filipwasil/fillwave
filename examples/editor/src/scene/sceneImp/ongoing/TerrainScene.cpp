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
#include <TerrainConstructors/MountainConstructor.h>

/* Physics */
//#include <bullet>

using namespace flw;
using namespace flw::flf;
using namespace std;

int main(int argc, char* argv[]) {
	ContextGLFW mContext(argc, argv);
	mEngine->insertResizeScreen(mContext.getScreenWidth(),
	      mContext.getScreenHeight());
	init();
	perform();
	showDescription();
	mContext.render();
	exit(EXIT_SUCCESS);
}

void init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(
	   make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
	                                  glm::quat(),
	                                  glm::radians(90.0),
	                                  1.0,
	                                  0.1,
	                                  1000.0));

	/* Lights */
	auto light = mEngine->storeLightSpot(glm::vec3 (1.0, 20.0,
	             6.0),
	             glm::quat (),
	             glm::vec4 (1.0, 1.0, 1.0, 0.0));
	light->rotateTo(glm::vec3(1.0, 0.0, 0.0), glm::radians(-90.0));

	/* Engine callbacks */
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
	mEngine->configureFPSCounter("fonts/Titania",
	      glm::vec2(0.7, 0.9), 100.0);

	puMeshTerrain terrain = make_unique<MeshTerrain>(mEngine,
	                        ProgramLoader(mEngine).getDefault(),
	                        new MountainConstructor(),
	                        Material(),
	                        "textures/test.png",
	                        "textures/testNormal.png",
	                        "",
	                        20,
	                        16);
	terrain->scaleTo(1.0);
	terrain->addEffect(make_shared<Fog>());
	mEngine->getCurrentScene()->attach(std::move(terrain));
}

void showDescription() {
	/* Description */
	pText hint0 =
	   mEngine->storeText("Fillwave example terrain",
	         "fonts/Titania",
	         glm::vec2(-0.95, 0.80), 100.0);
	pText hint5 =
	   mEngine->storeText("Use mouse to move the camera",
	         "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
	pText hint3 = mEngine->storeText("Use 'S' for camera back",
	              "fonts/Titania",
	              glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 =
	   mEngine->storeText("Use 'W' for camera forward",
	         "fonts/Titania",
	         glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 =
	   mEngine->storeText("Use 'T' to resume/stop time",
	         "fonts/Titania",
	         glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 =
	   mEngine->storeText("Use 'D' for toggle debugger On/Off",
	         "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}
