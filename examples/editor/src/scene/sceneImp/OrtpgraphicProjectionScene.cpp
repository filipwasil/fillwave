#include "scene/callbacks/Callbacks.h"
#include "OrtpgraphicProjectionScene.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

OrtpgraphicProjectionScene::OrtpgraphicProjectionScene(int argc, char **argv)
		: AScene(argc, argv) {
	mSceneParameters["mText"] = QVariant("HelloWorld");
	init();
}

void OrtpgraphicProjectionScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraOrthographic>(glm::vec3(0.0, 0.0, 6.0),
	                                                                      glm::quat(),
	                                                                      -10.0f,
	                                                                      10.0f,
	                                                                      -10.0f,
	                                                                      10.0f,
	                                                                      0.1f,
	                                                                      1000.0f));
	/* Entities */
	auto lightSource_1 = buildEntity();
	auto lightSource_2 = buildEntity();
	auto lightSource_3 = buildEntity();

	/* Lights */
	mEngine->storeLightSpot(glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec4(0.0, 1.0, 0.0, 0.0), lightSource_1.get());

	mEngine->storeLightSpot(glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec4(0.0, 0.0, 1.0, 0.0), lightSource_2.get());

	mEngine->storeLightSpot(glm::vec3(1.0, 1.0, 1.0), glm::quat(), glm::vec4(1.0, 0.0, 0.0, 0.0), lightSource_3.get());

	/* Programs */
	flc::Program *program = ProgramLoader(mEngine.get()).getDefault();

	lightSource_1->attach(make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "0_255_0.color"));
	lightSource_2->attach(make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "0_0_255.color"));
	lightSource_3->attach(make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "255_0_0.color"));

	lightSource_1->attachHierarchyCallback(make_unique<TimedMoveCallback>(lightSource_1.get(),
	                                                                      glm::vec3(0.0, 0.0, 500.0),
	                                                                      2000.0));
	lightSource_1->scaleTo(0.02);
	lightSource_1->moveBy(glm::vec3(0.0, 0.0, 0.0));

	lightSource_2->attachHierarchyCallback(make_unique<TimedMoveCallback>(lightSource_2.get(),
	                                                                      glm::vec3(0.0, 0.0, 500.0),
	                                                                      2000.0));
	lightSource_2->scaleTo(0.02);
	lightSource_2->moveBy(glm::vec3(3.0, 0.0, 0.0));

	lightSource_3->attachHierarchyCallback(make_unique<TimedMoveCallback>(lightSource_3.get(),
	                                                                      glm::vec3(0.0, 0.0, 500.0),
	                                                                      2000.0));
	lightSource_3->scaleTo(0.02);
	lightSource_3->moveBy(glm::vec3(-3.0, 0.0, 0.0));

	mEngine->getCurrentScene()->attach(std::move(lightSource_1));
	mEngine->getCurrentScene()->attach(std::move(lightSource_2));
	mEngine->getCurrentScene()->attach(std::move(lightSource_3));

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));
//	mEngine->registerCallback(make_unique<MoveCameraCallback>(
//	         mEngine, eEventType::eCursorPosition, 0.1,
//	         ContextGLFW::mWindow));

	/* Programs */
	auto wall = make_unique<Model>(mEngine.get(), program, "meshes/floor.obj");
	auto shadowCastingBall1 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	auto shadowCastingBall2 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	auto shadowCastingBall3 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	auto shadowCastingBall4 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	auto shadowCastingBall5 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");


	/* Manipulate objects directly */
	wall->rotateByX(glm::radians(90.0));
	wall->moveInDirection(glm::vec3(0.0, -10.0, 0.0));
	wall->scaleTo(3.0);

	/* Manipulate objects, set Callbacks */
	shadowCastingBall1->scaleTo(0.1);
	shadowCastingBall1->moveBy(glm::vec3(-2.0, 0.0, 0.0));

	shadowCastingBall2->scaleTo(0.1);
	shadowCastingBall2->moveBy(glm::vec3(0.0, 0.0, 3.0));

	shadowCastingBall3->scaleTo(0.1);
	shadowCastingBall3->moveBy(glm::vec3(2.0, 0.0, 3.0));

	shadowCastingBall4->scaleTo(0.1);
	shadowCastingBall4->moveBy(glm::vec3(0.0, 2.0, 3.0));

	shadowCastingBall5->scaleTo(0.1);
	shadowCastingBall5->attachHierarchyCallback(make_unique<TimedMoveCallback>(shadowCastingBall5.get(),
	                                                                           glm::vec3(0.0, 0.0, 3.0),
	                                                                           2000.0));

	shadowCastingBall5->moveBy(glm::vec3(0.0, -2.0, 3.0));

	mEngine->getCurrentScene()->attach(std::move(wall));
	mEngine->getCurrentScene()->attach(std::move(shadowCastingBall1));
	mEngine->getCurrentScene()->attach(std::move(shadowCastingBall2));
	mEngine->getCurrentScene()->attach(std::move(shadowCastingBall3));
	mEngine->getCurrentScene()->attach(std::move(shadowCastingBall4));
	mEngine->getCurrentScene()->attach(std::move(shadowCastingBall5));

	auto hint0 = mEngine->storeText("Fillwave example shadowing", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
	auto hint5 = mEngine->storeText("Use mouse to move the camera", "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
	auto hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
	auto hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	auto hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	auto hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
	                                 "fonts/Titania",
	                                 glm::vec2(-0.95, -0.80),
	                                 70.0);
}

void OrtpgraphicProjectionScene::perform() {


}

}