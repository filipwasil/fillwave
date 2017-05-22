#include "CursorScene.h"
#include "scene/callbacks/Callbacks.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

CursorScene::CursorScene(int argc, char **argv, QMap<QString, QVariant> varValues)
		: AScene(argc, argv, varValues) {
	mSceneParameters["mText"] = QVariant("HelloWorld");
	init();
}

void CursorScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));

	/* Cursor texture */
	flc::Texture2D *textureC = mEngine->storeTexture("textures/cursor/standard_blue.png");

	/* Cursor */
	mEngine->getCurrentScene()->setCursor(make_unique<Cursor>(mEngine.get(), textureC));

	/* Make cursor visible for current scene */
	mEngine->registerCallback(make_unique<FollowCustomCursorCallback>(mEngine.get()));

	/* Description */
	pText description = mEngine->storeText("Fillwave example cursor", "fonts/Titania", glm::vec2(-0.95, 0.95), 100.0);
}

void CursorScene::perform() {

}

}
