#include "scene/callbacks/Callbacks.h"
#include "SkyboxScene.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

void SkyboxScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 16.0),
	                                                                     glm::quat(),
	                                                                     glm::radians(90.0),
	                                                                     1.0,
	                                                                     0.1,
	                                                                     1000.0));

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));
//	mEngine->registerCallback(make_unique<MoveCameraCallback>(mEngine,
//	                                                          eEventType::eCursorPosition,
//	                                                          0.1,
//	                                                          ContextGLFW::mWindow));
}

void SkyboxScene::perform() {
	mEngine->getCurrentScene()->setSkybox(make_unique<Skybox>(mEngine.get(),
	                                                          mEngine->storeTexture3D(
			                                                          "textures/skybox/emerald/emerald_right.jpg",
			                                                          "textures/skybox/emerald/emerald_left.jpg",
			                                                          "textures/skybox/emerald/emerald_top.jpg",
			                                                          "",
			                                                          "textures/skybox/emerald/emerald_front.jpg",
			                                                          "textures/skybox/emerald/emerald_back.jpg")));
	pText hint0 = mEngine->storeText("Fillwave example skybox", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
}

}