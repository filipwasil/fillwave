#include "scene/callbacks/Callbacks.h"
#include "PickingScene.h"
#include "scene/objects/PickableModel.h"
#include "scene/callbacks/StandardKeyboardEventHandler.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

PickingScene::PickingScene(int argc, char **argv, QMap<QString, QVariant> varValues)
		: AScene(argc, argv, varValues) {
	mSceneParameters["mText"] = QVariant("HelloWorld");
	init();
}

void PickingScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

	/* Engine callbacks */
	mEngine->attachCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(), EEventType::eKey, 0.1));
	mEventsHandler.push_back(
			std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
	mEngine->getCurrentScene()->setCursor(make_unique<Cursor>(mEngine.get(),
	                                                          mEngine->storeTexture("textures/cursor/standard_blue.png")));

	/* Make cursor visible for current scene */
	mEngine->attachCallback(make_unique<FollowCustomCursorCallback>(mEngine.get()));

	/* Picking info text which will be modified frequently */
	pText pickInfo = mEngine->storeText("Nothing picked", "fonts/Titania", glm::vec2(-0.95, 0.80), 60.0);

	auto program = ProgramLoader(mEngine.get()).getProgram(EProgram::basic);

	/* build ball model */
	puModel ballModel1 = make_unique<PickableModel>("left ball",
	                                                pickInfo,
	                                                mEngine.get(),
	                                                program,
	                                                "meshes/sphere.obj",
	                                                "64_128_255.checkboard");
	ballModel1->scaleTo(0.1);
	ballModel1->moveBy(glm::vec3(-3.0, 0.0, 0.0));
	puModel ballModel2 = make_unique<PickableModel>("right ball",
	                                                pickInfo,
	                                                mEngine.get(),
	                                                program,
	                                                "meshes/sphere.obj",
	                                                "64_128_255.checkboard");
	ballModel2->scaleTo(0.1);
	ballModel2->moveBy(glm::vec3(3.0, 0.0, 0.0));
	puModel ballModel3 = make_unique<PickableModel>("center ball",
	                                                pickInfo,
	                                                mEngine.get(),
	                                                program,
	                                                "meshes/sphere.obj",
	                                                "64_128_255.checkboard");
	ballModel3->scaleTo(0.1);
	puModel ballModel4 = make_unique<PickableModel>("up ball",
	                                                pickInfo,
	                                                mEngine.get(),
	                                                program,
	                                                "meshes/sphere.obj",
	                                                "64_128_255.checkboard");
	ballModel4->scaleTo(0.1);
	ballModel4->moveBy(glm::vec3(0.0, 3.0, 0.0));
	puModel ballModel5 = make_unique<PickableModel>("down ball",
	                                                pickInfo,
	                                                mEngine.get(),
	                                                program,
	                                                "meshes/sphere.obj",
	                                                "64_128_255.checkboard");
	ballModel5->scaleTo(0.1);
	ballModel5->moveBy(glm::vec3(0.0, -3.0, 0.0));

	/* Register ball model as a pickable model in scene */
	mEngine->getCurrentScene()->registerPickable(ballModel1.get()); // xxx is register pickable safe ?
	mEngine->getCurrentScene()->registerPickable(ballModel2.get());
	mEngine->getCurrentScene()->registerPickable(ballModel3.get());
	mEngine->getCurrentScene()->registerPickable(ballModel4.get());
	mEngine->getCurrentScene()->registerPickable(ballModel5.get());

	/* Attach ball model to ball entity */
	mEngine->getCurrentScene()->attach(std::move(ballModel1));
	mEngine->getCurrentScene()->attach(std::move(ballModel2));
	mEngine->getCurrentScene()->attach(std::move(ballModel3));
	mEngine->getCurrentScene()->attach(std::move(ballModel4));
	mEngine->getCurrentScene()->attach(std::move(ballModel5));

	/* Register picking callback */
	mEngine->attachCallback(make_unique<ColorPickingCallback>(mEngine.get()));

	/* Description */
	pText description = mEngine->storeText("Fillwave example cursor picking",
	                                       "fonts/Titania",
	                                       glm::vec2(-0.95, 0.95),
	                                       100.0);

	pText hint0 = mEngine->storeText("Pick a sphere", "fonts/Titania", glm::vec2(-0.95, -0.80), 70.0);
}

void PickingScene::perform() {

}

}