#include <example.h>
#include <ContextGLFW.h>
#include <fillwave/models/shapes/Sphere.h>

using namespace flw;
using namespace flw::flf;
using namespace flw::flc;
using namespace flw::flc;

//const GLint SPHERES = 5;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  init();
  mContext.render();
  exit(EXIT_SUCCESS);
}

void init() {
  ContextGLFW::mGraphics->setCurrentScene(std::make_unique<Scene>());
  ContextGLFW::mGraphics->getCurrentScene()->setCamera(std::make_unique<CameraPerspective>());

  auto engine = ContextGLFW::mGraphics;

  /* Entities */
  auto light = std::make_unique<Entity>();
  light->moveTo(glm::vec3(0.0, 0.0, 3.0));

  /* Texture */
  //auto textureN = engine->storeTexture("255_255_255.color");
  //auto textureS = engine->storeTexture("");

  /* Lights */
  engine->storeLightSpot(glm::vec3(1.0, 1.0, 3.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), light.get());

  auto cube = std::make_unique<Model>(
    engine
    , ProgramLoader(engine).getProgram(EProgram::basic)
    , flw::flf::Sphere(0.1)
    , engine->storeTexture("255_255_0.checkboard"));
  engine->getCurrentScene()->attach(std::move(cube));

  auto model = std::make_unique<Model>(
    engine
    , ProgramLoader(engine).getProgram(EProgram::basicAnimated)
    , "animations/beast/beast.dae"
    , engine->storeTexture("textures/beast/beast_dxt1.DDS"));
  model->rotateByX(glm::radians(90.0f));
  model->moveByZ(-1.0f);
  model->setActiveAnimation(0);
  engine->getCurrentScene()->attach(std::move(model));


//  auto screenSize = engine->getScreenSize();

//  auto textureFile = TextureLoader().loadEmpty(screenSize.x, screenSize.y);

  flc::ParameterList parameters = {
    flc::Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    , flc::Parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    , flc::Parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
  };

  engine->storeText("Animation", "FreeSans", glm::vec2(-0.95f, 0.2f), 50.0f);

  //auto program = ProgramLoader(engine).getProgram(EProgram::basic);

//  flw::flc::Texture2DRenderable t(GL_COLOR_ATTACHMENT0, textureFile, parameters);
}
