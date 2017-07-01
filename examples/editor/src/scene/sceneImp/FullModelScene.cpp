#include "FullModelScene.h"
#include "scene/callbacks/Callbacks.h"
#include <scene/callbacks/StandardKeyboardEventHandler.h>
#include <scene/callbacks/StandardMouseEventHandler.h>

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

FullModelScene::FullModelScene(int argc, char **argv, QMap<QString, QVariant> varValues)
		: AScene(argc, argv, varValues) {
	mSceneParameters["mText"] = QVariant("HelloWorld");
	init();
}

void FullModelScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 2.0, 10.0),
	                                                                     glm::quat(),
	                                                                     glm::radians(90.0),
	                                                                     1.0,
	                                                                     0.1,
	                                                                     1000.0));

	/* Entities */
	puEntity light = buildEntity();

	/* Lights */
	LightSpot *l = mEngine->storeLightSpot(glm::vec3(0.0, 1.0, 0.0),
	                                       glm::quat(),
	                                       glm::vec4(1.0, 1.0, 1.0, 0.0),
	                                       light.get());

	light->rotateByX(glm::radians(-90.0));

	flc::Program *program = ProgramLoader(mEngine.get()).getDefault();

	light->attach(make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "255_255_255.color"));
	light->attachHierarchyCallback(make_unique<TimedMoveCallback>(light.get(), glm::vec3(4.0, 0.0, 0.0), 50.0));
	light->scaleTo(0.02);
	light->moveBy(glm::vec3(-2.0, 4.0, 0.0));

	puModel wall = make_unique<Model>(mEngine.get(),
	                                  program,
	                                  "meshes/floor.obj",
	                                  "textures/wall/stonetiles.png",
	                                  "textures/wall/stonetiles_n.png",
	                                  "textures/wall/stonetiles_s.png");
	wall->moveInDirection(glm::vec3(0.0, -2.0, 0.0));
	wall->scaleTo(1.0);

	mEngine->getCurrentScene()->attach(std::move(wall));
	mEngine->getCurrentScene()->attach(std::move(light));

	/* Engine callbacks */
	mEngine->attachCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(
			mEngine.get(), eEventType::eCursorPosition, 0.01));

  mEventsHandler.push_back(
      std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  mEventsHandler.push_back(
      std::make_unique<scene::callbacks::StandardMouseEventHandler>(mEngine));
	/* Attach entities and entity to the scene */

	mEngine->getCurrentScene()->setSkybox(make_unique<Skybox>(mEngine.get(),
	                                                          mEngine->storeTexture3D(
			                                                          "textures/skybox/hourglass/hourglass_right.jpg",
			                                                          "textures/skybox/hourglass/hourglass_left.jpg",
			                                                          "textures/skybox/hourglass/hourglass_top.jpg",
			                                                          "",
			                                                          "textures/skybox/hourglass/hourglass_front.jpg",
			                                                          "textures/skybox/hourglass/hourglass_back.jpg")));

	pText hint0 = mEngine->storeText("Fillwave example normal mapping", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
	pText hint5 = mEngine->storeText("To move the camera push rigth mouse button and move", "fonts/Titania",
                                   glm::vec2(-0.95, -0.40), 70.0);
	pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
	                                 "fonts/Titania",
	                                 glm::vec2(-0.95, -0.80),
	                                 70.0);
}

void FullModelScene::perform() {

}

}
