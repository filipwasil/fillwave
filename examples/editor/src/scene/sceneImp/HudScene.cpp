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
#include <fillwave/Framework.h>

using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

void perform() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene().setCamera(
	   make_unique<CameraPerspective>());

	puHUD hud = make_unique<HUD>();

	hud->attach(
	   make_unique < Button
	   > (mEngine, mEngine->storeTexture(
	         "buttons/start-1.png"), vec2(-0.95, 0.9), vec2(0.1)));

	hud->attach(
	   make_unique < Button
	   > (mEngine, mEngine->storeTexture(
	         "buttons/player-1.png"), vec2(-0.95, 0.80), vec2(0.1)));

	hud->attach(
	   make_unique < Button
	   > (mEngine, mEngine->storeTexture(
	         "buttons/help-1.png"), vec2(-0.95, 0.70), vec2(0.1)));

	hud->attach(
	   make_unique < Button
	   > (mEngine, mEngine->storeTexture(
	         "buttons/exit-1.png"), vec2(-0.95, 0.60), vec2(0.1)));

	auto bar = make_unique < ProgressBar
	           > (mEngine, mEngine->storeTexture(
	                 "128_128_64.color"), "shaders/progress_bar/progress.frag", vec2(-0.75, -.45),
	              vec2(1.5, 0.1));


	hud->attach(std::move(bar));

	mEngine->getCurrentScene().setHUD(std::move(hud));

	pText t1 = mEngine->storeText("Fillwave Buttons",
	           "fonts/bridgenorth", vec2(-0.95, -0.8), 100.0);
}
