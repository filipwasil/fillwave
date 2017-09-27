//============================================================================
// Name        : example_terrain_voxel.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example terrain voxel
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>

/* Graphics */
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/AnimationKeyboardCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <App.h>
#include <TerrainConstructors/MountainConstructor.h>
#include <fillwave/Fillwave.h>

/* Physics */
//#include <bullet>

using namespace flw;
using namespace flw::flf;
using namespace std;

int main(int argc, char* argv[]) {
	App mContext(argc, argv);
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
	   make_unique<CameraPerspective>());

	/* Entities */
	puEntity entity = buildEntity();

	/* Texture */
	flc::Texture3D* textureCubemap =
	   mEngine->storeTexture3D("textures/skybox/devilpunch/devpun_right.jpg",
	         "textures/skybox/devilpunch/devpun_left.jpg",
	         "textures/skybox/devilpunch/devpun_top.jpg",
	         "",
	         "textures/skybox/devilpunch/devpun_front.jpg",
	         "textures/skybox/devilpunch/devpun_back.jpg");

	/* Lights */
	mEngine->storeLightSpot(glm::vec3 (0.0, 10.0, 1.0),
	      glm::quat(),
	      glm::vec4 (1.0, 0.0, 0.0, 1.0),
	      entity.get());

	entity->moveBy(glm::vec3 (0.0, 2.0, 4.0));

	/* Engine callbacks */
	mEngine->attachCallback(make_unique<TimeStopCallback>(
	         mEngine));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(
	         mEngine, EEventType::eKey,
	         0.1));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(
	         mEngine, EEventType::eScroll,
	         0.1));
}

void perform() {
	mEngine->getCurrentScene()->setSkybox(make_unique<Skybox>
	      (mEngine,
	       mEngine->storeTexture3D("textures/skybox/devilpunch/devpun_right.jpg",
	             "textures/skybox/devilpunch/devpun_left.jpg",
	             "textures/skybox/devilpunch/devpun_top.jpg",
	             "",
	             "textures/skybox/devilpunch/devpun_front.jpg",
	             "textures/skybox/devilpunch/devpun_back.jpg")));
	mEngine->getCurrentScene()->attach(buildTerrainVoxel(
	         mEngine,
	         ProgramLoader(mEngine).getDefault(),
	         "textures/test.png",
	         new MountainConstructor(),
	         5));
}

void showDescription() {
	pText hint0 =
	   mEngine->storeText("Fillwave example terrain voxel",
	         "fonts/Titania",  glm::vec2(-0.95, 0.80), 100.0);
	pText hint5 =
	   mEngine->storeText("Use mouse to move the camera",
	         "fonts/Titania",  glm::vec2(-0.95, -0.40), 70.0);
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
	         "fonts/Titania",  glm::vec2(-0.95, -0.80), 70.0);

}
