#include <QColor>
#include "ShadowScene.h"
#include "scene/callbacks/Callbacks.h"
#include <scene/callbacks/StandardKeyboardEventHandler.h>
#include <scene/callbacks/StandardMouseEventHandler.h>

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

ShadowScene::ShadowScene(int argc, char **argv, QMap<QString, QVariant> varValues)
		: AScene(argc, argv, varValues) {
	init();
}

void ShadowScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
	                                                                     glm::quat(),
	                                                                     glm::radians(90.0),
	                                                                     1.0,
	                                                                     0.1,
	                                                                     1000.0));
	/* Entities */
	puEntity lightSource_1 = buildEntity();
	puEntity lightSource_2 = buildEntity();
	puEntity lightSource_3 = buildEntity();

	/* Lights */
	auto firstColor = mSceneParameters["mFirstShadow"].value<QColor>();
	mFirstLigth = mEngine->storeLightSpot(glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec4
			(firstColor.redF(), firstColor.greenF(), firstColor.blueF(), firstColor.alphaF()), lightSource_1.get());
  auto secondColor = mSceneParameters["mSecondShadow"].value<QColor>();
	mSecomdLigth = mEngine->storeLightSpot(glm::vec3(0.0, 1.0, 0.0), glm::quat(), glm::vec4
      (secondColor.redF(), secondColor.greenF(), secondColor.blueF(), secondColor.alphaF()), lightSource_2.get());
  auto thirdColor = mSceneParameters["mThirdShadow"].value<QColor>();
	mThirdLigth = mEngine->storeLightSpot(glm::vec3(1.0, 1.0, 1.0), glm::quat(), glm::vec4
       (thirdColor.redF(), thirdColor.greenF(), thirdColor.blueF(), thirdColor.alphaF()), lightSource_3.get());

	/* Programs */
	flc::Program *program = ProgramLoader(mEngine.get()).getProgram(EProgram::basic);

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
	mEngine->attachCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(), EEventType::eKey, 0.1));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(),
	                                                          EEventType::eCursorPosition,
	                                                          0.01));
  mEventsHandler.push_back(
      std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
  mEventsHandler.push_back(
      std::make_unique<scene::callbacks::StandardMouseEventHandler>(mEngine));

	/* Programs */
	puModel wall = make_unique<Model>(mEngine.get(), program, "meshes/floor.obj");
	puModel shadowCastingBall1 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	puModel shadowCastingBall2 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	puModel shadowCastingBall3 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	puModel shadowCastingBall4 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");
	puModel shadowCastingBall5 = make_unique<Model>(mEngine.get(), program, "meshes/sphere.obj", "64_128_255.checkboard");

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

	pText hint0 = mEngine->storeText("Fillwave example shadowing", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
	pText hint5 = mEngine->storeText("To move the camera push rigth mouse button and move", "fonts/Titania", glm::vec2(
      -0.95, -0.40), 70.0);
	pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
	                                 "fonts/Titania",
	                                 glm::vec2(-0.95, -0.80),
	                                 70.0);
}

void ShadowScene::perform() {
	auto firstColor = mSceneParameters["mFirstShadow"].value<QColor>();
	mFirstLigth->setIntensity(glm::vec4(firstColor.redF(), firstColor.greenF(), firstColor.blueF(), firstColor.alphaF()));
  auto secondColor = mSceneParameters["mSecondShadow"].value<QColor>();
  mSecomdLigth->setIntensity(glm::vec4
	    (secondColor.redF(), secondColor.greenF(), secondColor.blueF(), secondColor.alphaF()));
	auto thirdColor = mSceneParameters["mThirdShadow"].value<QColor>();
	mThirdLigth->setIntensity(glm::vec4
	    (thirdColor.redF(), thirdColor.greenF(), thirdColor.blueF(), thirdColor.alphaF()));
}
}