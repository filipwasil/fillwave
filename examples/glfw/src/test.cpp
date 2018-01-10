//============================================================================
// Name        : example_callbacks.cpp
// Author      : Filip Wasil
// Version     :
// Copyright   : none
// Description : Fillwave engine example callbacks
//============================================================================

#include <example.h>

/* Audio */
//#include <portaudio.h>
/* Graphics */
#include <CallbacksGLFW/MoveCameraCallback.h>
#include <CallbacksGLFW/TimeStopCallback.h>
#include <ContextGLFW.h>

/* Physics */
//#include <bullet>
using namespace flw;
using namespace flw::flf;
using namespace std;
using namespace glm;

const GLint SPHERES = 5;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::mGraphics->onResizeScreen(mContext.getScreenWidth(), mContext.getScreenHeight());
  init();
  perform();
  showDescription();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void init() {
}

void perform() {
  auto mEngine = ContextGLFW::mGraphics;
  mEngine->setCurrentScene(make_unique<Scene>());
  mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>());

  /* Entities */
  auto light = std::make_unique<Entity>();
  light->moveTo(glm::vec3(0.0, 0.0, 3.0));

  /* Texture */
  flc::Texture2D *textureN = mEngine->storeTexture("255_255_255.color");
  flc::Texture2D *textureS = mEngine->storeTexture("");

  /* Lights */
  mEngine->storeLightSpot(glm::vec3(1.0, 1.0, 3.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), light.get());

  auto model = make_unique<Model>(mEngine,
                                  ProgramLoader(mEngine).getProgram(EProgram::basic),
                                  "meshes/sphere.obj",
                                  mEngine->storeTextureDynamic("shaders/water/water.frag"));
  model->moveBy(glm::vec3(0.0, 0.0, -15.0));
  mEngine->getCurrentScene()->attach(std::move(model));

  /* Description */
  pText hint5 = mEngine->storeText("To move the camera push rigth mouse button and move",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.40),
                                   70.0);
  pText hint3 = mEngine->storeText("Use 'S' for camera back", "fonts/Titania", glm::vec2(-0.95, -0.50), 70.0);
  pText hint4 = mEngine->storeText("Use 'W' for camera forward", "fonts/Titania", glm::vec2(-0.95, -0.60), 70.0);
  pText hint1 = mEngine->storeText("Use 'T' to resume/stop time", "fonts/Titania", glm::vec2(-0.95, -0.70), 70.0);
  pText hint6 = mEngine->storeText("Use 'D' for toggle debugger On/Off",
                                   "fonts/Titania",
                                   glm::vec2(-0.95, -0.80),
                                   70.0);

  auto screenSize = mEngine->getScreenSize();

  auto textureFile = TextureLoader().loadEmpty(screenSize.x, screenSize.y);

  flc::ParameterList parameters = {
      flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
      , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
      , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
      , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  auto program = ProgramLoader(mEngine).getProgram(EProgram::basic);

  flw::flc::Texture2DRenderable t(GL_COLOR_ATTACHMENT0, textureFile, parameters);
}

void quit() {
//
}

void setupParam(const char* , glm::vec2 ) {
}

void showDescription() {
}

