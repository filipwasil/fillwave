//============================================================================
// Name        : example_text.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example text
//============================================================================

#include <ContextGLFW.h>
#include <example.h>

/* Graphics */
#include <fillwave/Fillwave.h>

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;
using namespace glm;

pCameraPerspective gCamera;
pScenePerspective gScene;

int main(int argc, char* argv[]) {
   ContextGLFW mContext;
   ContextGLFW::mGraphicsEngine = new Engine(argc, argv);
   ContextGLFW::mGraphicsEngine->insertResizeScreen(mContext.getScreenWidth(),
                                                   mContext.getScreenHeight());
   perform();
   mContext.render();
   delete ContextGLFW::mGraphicsEngine;
   exit(EXIT_SUCCESS);
}

void perform() {
   /* Scene */
   gScene = buildScenePerspective();

   /* Camera */
   gCamera = make_shared<CameraPerspective>();

   /* Create scene */
   gScene->setCamera(gCamera);

   /* Attach camera to scene*/
	ContextGLFW::mGraphicsEngine->setCurrentScene(gScene);

	pHUD hud = make_shared<HUD>();

	hud->attach(
			make_shared < Button
					> (ContextGLFW::mGraphicsEngine, ContextGLFW::mGraphicsEngine->storeTexture(
							"buttons/start-1.png"), vec2(-0.95, 0.9), vec2(0.1)));

	hud->attach(
			make_shared < Button
					> (ContextGLFW::mGraphicsEngine, ContextGLFW::mGraphicsEngine->storeTexture(
							"buttons/player-1.png"), vec2(-0.95, 0.80), vec2(0.1)));

	hud->attach(
			make_shared < Button
					> (ContextGLFW::mGraphicsEngine, ContextGLFW::mGraphicsEngine->storeTexture(
							"buttons/help-1.png"), vec2(-0.95, 0.70), vec2(0.1)));

	hud->attach(
			make_shared < Button
					> (ContextGLFW::mGraphicsEngine, ContextGLFW::mGraphicsEngine->storeTexture(
							"buttons/exit-1.png"), vec2(-0.95, 0.60), vec2(0.1)));

	pProgressBar bar = make_shared < ProgressBar
						> (ContextGLFW::mGraphicsEngine, ContextGLFW::mGraphicsEngine->storeTexture(
								"128_128_64.color"), "shaders/progress_bar/progress.frag", vec2(-0.75, -.45), vec2(1.5, 0.1));

	bar->setProgress(0.33);

	hud->attach(bar);

	gScene->setHUD(hud);

	pText t1 = ContextGLFW::mGraphicsEngine->storeText("Fillwave Buttons",
			"fonts/bridgenorth", vec2(-0.95, -0.8), 100.0);
}
