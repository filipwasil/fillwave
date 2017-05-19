#include "scene/callbacks/Callbacks.h"
#include "HudScene.h"

using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

namespace scene {

HudScene::HudScene(int argc, char **argv)
		: AScene(argc, argv) {
	mSceneParameters["mText"] = QVariant("HelloWorld");
	init();
}

void HudScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

	puHUD hud = make_unique<HUD>();

	hud->attach(make_unique<Button>(mEngine.get(),
	                                mEngine->storeTexture("buttons/start-1.png"),
	                                vec2(-0.95, 0.9),
	                                vec2(0.1)));

	hud->attach(make_unique<Button>(mEngine.get(),
	                                mEngine->storeTexture("buttons/player-1.png"),
	                                vec2(-0.95, 0.80),
	                                vec2(0.1)));

	hud->attach(make_unique<Button>(mEngine.get(),
	                                mEngine->storeTexture("buttons/help-1.png"),
	                                vec2(-0.95, 0.70),
	                                vec2(0.1)));

	hud->attach(make_unique<Button>(mEngine.get(),
	                                mEngine->storeTexture("buttons/exit-1.png"),
	                                vec2(-0.95, 0.60),
	                                vec2(0.1)));

	auto bar = make_unique<ProgressBar>(mEngine.get(),
	                                    mEngine->storeTexture("128_128_64.color"),
	                                    "shaders/progress_bar/progress.frag",
	                                    vec2(-0.75, -.45),
	                                    vec2(1.5, 0.1));


	hud->attach(std::move(bar));

	mEngine->getCurrentScene()->setHUD(std::move(hud));

	pText t1 = mEngine->storeText("Fillwave Buttons", "fonts/bridgenorth", vec2(-0.95, -0.8), 100.0);
}

void HudScene::perform() {

}

}
