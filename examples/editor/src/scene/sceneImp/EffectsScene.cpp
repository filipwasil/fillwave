#include "scene/callbacks/Callbacks.h"
#include "EffectsScene.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {
void EffectsScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

	/* Lights */
	mEngine->storeLightSpot(glm::vec3 (1.0, 1.0, 6.0),
	                        glm::quat (),
	                        glm::vec4 (1.0, 0.0, 0.0, 0.0));

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>
			                          (mEngine.get()));
	mEngine->registerCallback(make_unique<MoveCameraCallback>
			                          (mEngine.get(),
			                           eEventType::eKey,
			                           0.1));
//	mEngine->registerCallback(make_unique<MoveCameraCallback>
//			                          (mEngine,
//			                           eEventType::eCursorPosition, 0.1, ContextGLFW::mWindow));
}

void EffectsScene::perform() {
	puModel model = make_unique<Model>(mEngine.get(),
	                                   ProgramLoader(mEngine.get()).getDefault(), "meshes/sphere.obj",
	                                   "64_128_255.checkboard");
	pIEffect fog = make_shared<Fog>();
	pIEffect boost = make_shared<BoostColor>(10.0);
	model->addEffect(make_shared<Fog>());
	model->addEffect(make_shared<BoostColor>(10.0));

	model->moveBy(glm::vec3(0.0, 0.0, -15.0));

	mEngine->getCurrentScene()->attach(std::move(model));

	/* Description */
	pText description =
			mEngine->storeText("Fillwave example effects",
			                   "fonts/Titania",
			                   glm::vec2(-0.95,
			                             0.95),
			                   100.0);

	pText hint0 =
			mEngine->storeText("Fillwave example effects",
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

}
