#include "scene/callbacks/Callbacks.h"
#include "ParticlesScene.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

namespace scene {

ParticlesScene::ParticlesScene(int argc, char **argv, QMap<QString, QVariant> varValues)
		: AScene(argc, argv, varValues) {
	init();
}

void ParticlesScene::init() {
	/* Scene and camera */
	mEngine->setCurrentScene(make_unique<Scene>());
	mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
	                                                                     glm::quat(),
	                                                                     glm::radians(90.0),
	                                                                     1.0,
	                                                                     0.1,
	                                                                     1000.0));

	/* Engine callbacks */
	mEngine->registerCallback(make_unique<TimeStopCallback>(mEngine.get()));
	mEngine->registerCallback(make_unique<MoveCameraCallback>(mEngine.get(), eEventType::eKey, 0.1));
//	mEngine->registerCallback(make_unique<MoveCameraCallback>(
//			mEngine, eEventType::eCursorPosition, 0.1,
//			ContextGLFW::mWindow));

	/* Attach emiters to entities */
	puIEmiterPoint water = make_unique<EmiterPointCPU>(mEngine.get(),
	                                                   0.3,
	                                                   60000.0,
	                                                   glm::vec4(0.1, 0.1, 1.0, 1.0),
	                                                   glm::vec3(0.0, 0.0, 0.0),
	                                                   glm::vec3(0.0, 0.0, 0.0),
	                                                   glm::vec3(0.9, 0.9, 0.9),
	                                                   glm::vec3(0.0, 0.0, 0.0),
	                                                   glm::vec3(0.0, 0.0, 0.0),
	                                                   10.0,
	                                                   10.0,
	                                                   mEngine->storeTexture("textures/particle.png"),
	                                                   GL_SRC_ALPHA,
	                                                   GL_ONE,
	                                                   GL_FALSE);
	water->moveBy(glm::vec3(0.0, -1.0, -1.0));

	puIEmiterPoint sand = make_unique<EmiterPointCPU>(mEngine.get(),
	                                                  0.3,
	                                                  60000.0,
	                                                  glm::vec4(1.0, 1.0, 0.0, 1.0),
	                                                  glm::vec3(0.0, 2.0, 0.0),
	                                                  glm::vec3(0.0, 0.0, 0.0),
	                                                  glm::vec3(0.9, 0.9, 0.9),
	                                                  glm::vec3(0.0, 0.0, 0.0),
	                                                  glm::vec3(0.0, 0.0, 0.0),
	                                                  10.0,
	                                                  10.0,
	                                                  mEngine->storeTexture("textures/particle.png"),
	                                                  GL_SRC_ALPHA,
	                                                  GL_ONE,
	                                                  GL_FALSE);

	puIEmiterPoint snow = make_unique<EmiterPointGPU>(mEngine.get(),
	                                                  0.3,
	                                                  600.0,
	                                                  glm::vec4(1.0, 1.0, 1.0, 1.0),
	                                                  glm::vec3(0.0, 1.0, 0.0),
	                                                  glm::vec3(0.0, 0.0, 0.0),
	                                                  glm::vec3(0.9, 0.9, 0.9),
	                                                  glm::vec3(0.0, 0.0, 0.0),
	                                                  glm::vec3(0.6, 0.6, 0.6),
	                                                  1.0,
	                                                  1.0,
	                                                  mEngine->storeTexture("textures/particle.png"),
	                                                  GL_SRC_ALPHA,
	                                                  GL_ONE,
	                                                  GL_FALSE);

	/* For time updates */
	snow->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(snow.get(), FILLWAVE_ENDLESS));
	water->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(water.get(), FILLWAVE_ENDLESS));
	sand->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(sand.get(), FILLWAVE_ENDLESS));

	mEngine->getCurrentScene()->attach(std::move(sand));
	mEngine->getCurrentScene()->attach(std::move(water));
	//mEngine->getCurrentScene()->attach(std::move(snow));

	pText hint0 = mEngine->storeText("Fillwave example particles", "fonts/Titania", glm::vec2(-0.95, 0.80), 100.0);
	pText hint5 = mEngine->storeText("Use mouse to move the camera", "fonts/Titania", glm::vec2(-0.95, -0.40), 70.0);
	pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
	pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
	pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
	pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
	                                 "fonts/Titania",
	                                 glm::vec2(-0.95, -0.80),
	                                 70.0);
}

void ParticlesScene::perform() {
//Example
	QVariant tmp = mSceneParameters["mVar1"];
	int value1 = tmp.toInt();
}

}
