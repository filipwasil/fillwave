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
#include <ContextGLFW.h>
#include <TerrainConstructors/MountainConstructor.h>
#include <fillwave/Fillwave.h>

/* Physics */
//#include <bullet>

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

int main(int argc, char* argv[]) {
	ContextGLFW mContext(argc, argv);
	ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(),
	      mContext.getScreenHeight());
	init();
	perform();
	showDescription();
	mContext.render();
	exit(EXIT_SUCCESS);
}

void init() {
	/* Scene and camera */
	ContextGLFW::mGraphicsEngine->setCurrentScene(make_unique<Scene>());
	ContextGLFW::mGraphicsEngine->getCurrentScene()->setCamera(
	   make_unique<CameraPerspective>());

	/* Entities */
	puEntity entity = buildEntity();

	/* Texture */
	core::Texture3D* textureCubemap =
	   ContextGLFW::mGraphicsEngine->storeTexture3D("textures/skybox/devilpunch/devpun_right.jpg",
	         "textures/skybox/devilpunch/devpun_left.jpg",
	         "textures/skybox/devilpunch/devpun_top.jpg",
	         "",
	         "textures/skybox/devilpunch/devpun_front.jpg",
	         "textures/skybox/devilpunch/devpun_back.jpg");

	/* Lights */
	ContextGLFW::mGraphicsEngine->storeLightSpot(glm::vec3 (0.0, 10.0, 1.0),
	      glm::quat(),
	      glm::vec4 (1.0, 0.0, 0.0, 1.0),
	      entity.get());

	entity->moveBy(glm::vec3 (0.0, 2.0, 4.0));

	/* Engine callbacks */
	ContextGLFW::mGraphicsEngine->registerCallback(TimeStopCallback(
	         ContextGLFW::mGraphicsEngine));
	ContextGLFW::mGraphicsEngine->registerCallback(MoveCameraCallback(
	         ContextGLFW::mGraphicsEngine, eEventType::eKey,
	         0.1));
	ContextGLFW::mGraphicsEngine->registerCallback(MoveCameraCallback(
	         ContextGLFW::mGraphicsEngine, eEventType::eScroll,
	         0.1));
}

void perform() {
	ContextGLFW::mGraphicsEngine->getCurrentScene()->setSkybox(make_unique<Skybox>
	      (ContextGLFW::mGraphicsEngine,
	       ContextGLFW::mGraphicsEngine->storeTexture3D("textures/skybox/devilpunch/devpun_right.jpg",
	             "textures/skybox/devilpunch/devpun_left.jpg",
	             "textures/skybox/devilpunch/devpun_top.jpg",
	             "",
	             "textures/skybox/devilpunch/devpun_front.jpg",
	             "textures/skybox/devilpunch/devpun_back.jpg")));
	ContextGLFW::mGraphicsEngine->getCurrentScene()->attach(buildTerrainVoxel(
	         ContextGLFW::mGraphicsEngine,
	         ProgramLoader(ContextGLFW::mGraphicsEngine).getDefault(),
	         "textures/test.png",
	         new MountainConstructor(),
	         2));
}

void showDescription() {
	pText hint0 =
	   ContextGLFW::mGraphicsEngine->storeText("Fillwave example terrain voxel",
	         "fonts/Titania",  glm::vec2(-0.95, 0.80), 100.0);
	pText hint5 =
	   ContextGLFW::mGraphicsEngine->storeText("Use mouse to move the camera",
	         "fonts/Titania",  glm::vec2(-0.95, -0.40), 70.0);
	pText hint3 = ContextGLFW::mGraphicsEngine->storeText("Use 'S' for camera back",
	              "fonts/Titania",
	              glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 =
	   ContextGLFW::mGraphicsEngine->storeText("Use 'W' for camera forward",
	         "fonts/Titania",
	         glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 =
	   ContextGLFW::mGraphicsEngine->storeText("Use 'T' to resume/stop time",
	         "fonts/Titania",
	         glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 =
	   ContextGLFW::mGraphicsEngine->storeText("Use 'D' for toggle debugger On/Off",
	         "fonts/Titania",  glm::vec2(-0.95, -0.80), 70.0);

}
