#include "scene/callbacks/Callbacks.h"
#include "PostProcessingScene.h"
#include "scene/callbacks/StandardKeyboardEventHandler.h"
#include "scene/callbacks/StandardMouseEventHandler.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

PostProcessingScene::PostProcessingScene(int argc, char **argv, QMap<QString, QVariant> varValues)
		: AScene(argc, argv, varValues) {
	mSceneParameters["mText"] = QVariant("HelloWorld");
	init();
}

void PostProcessingScene::init() {
//	/* Scene and camera */
//	mEngine->setCurrentScene(make_unique<Scene>());
//	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
//	                                                                     glm::quat(),
//	                                                                     glm::radians(90.0),
//	                                                                     1.0,
//	                                                                     0.1,
//	                                                                     1000.0));
//	/* Entities */
//	puEntity entity = buildEntity();
//
//	/* Texture */
//	mEngine->addPostProcess("shaders/process/process1.frag", 8.0);
//
//	flc::Texture2D *textureDynamic = mEngine->storeTextureDynamic("shaders/water/water.frag");
//
//	/* Models */
//
//	puModel model = make_unique<Model>(mEngine.get(),
//	                                   ProgramLoader(mEngine.get()).getProgram(EProgram::basic),
//	                                   "meshes/sphere.obj",
//	                                   textureDynamic);
//	model->moveBy(glm::vec3(0.0, 0.0, -15.0));
//
//	/* Lights */
//	mEngine->storeLightSpot(glm::vec3(1.0, 1.0, 3.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), entity.get());
//
//	entity->moveTo(glm::vec3(0.0, 0.0, 3.0));
//
//	/* Engine callbacks */
//	mEngine->attachCallback(make_unique<TimeStopCallback>(mEngine.get()));
//	mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(), EEventType::eKey, 0.1));
//	mEngine->attachCallback(make_unique<MoveCameraCallback>(mEngine.get(),
//	                                                          EEventType::eCursorPosition,
//	                                                          0.01));
//	mEventsHandler.push_back(
//			std::make_unique<scene::callbacks::StandardKeyboardEventHandler>(mEngine));
//	mEventsHandler.push_back(
//			std::make_unique<scene::callbacks::StandardMouseEventHandler>(mEngine));
//
//	mEngine->getCurrentScene()->attach(std::move(model));
//
//	/* Description */
//	flw::ps<flw::flf::Text> description = mEngine->storeText("Fillwave example post processing shader",
//	                                       "fonts/Titania",
//	                                       glm::vec2(-0.95, 0.95),
//	                                       100.0);
}

void PostProcessingScene::perform() {

}

}