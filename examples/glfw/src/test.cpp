#include <example.h>
#include <ContextGLFW.h>
#include <flw/flf/models/shapes/Sphere.h>
#include <memory>

using namespace flw;
using namespace flw::flf;
using namespace flw::flc;

int main(int argc, char* argv[]) {
  auto context = std::make_unique<ContextGLFW>(argc, argv);
#if defined(FILLWAVE_BACKEND_OPENGL_ES_PC)
  ContextGLFW::mGraphics = new flw::EnginePCGLES(argc, argv, glfwGetProcAddress);
#else
  ContextGLFW::mGraphics = new flw::EnginePC(argc, argv);
#endif
  init();
  initCallbacks();
  context->render();
  delete ContextGLFW::mGraphics;
  exit(EXIT_SUCCESS);
}

void init() {
  auto engine = ContextGLFW::mGraphics;

  engine->setCurrentScene(std::make_unique<Scene>());
  engine->getCurrentScene()->setCamera(std::make_unique<CameraPerspective>());

  auto programs = ProgramLoader(engine);
  /* light spot */
  auto light = std::make_unique<Entity>();
  light->moveTo(glm::vec3(0.0, 0.0, 3.0));
  engine->storeLightSpot(glm::vec3(1.0, 1.0, 3.0), glm::quat(), glm::vec4(1.0, 1.0, 1.0, 0.0), light.get());

  /* Model constructor 1 */
  auto sut1 = std::make_unique<Model>(
    engine
    , programs.getProgram(EProgram::basic)
    , flw::flf::Sphere(0.1)
    , engine->storeTexture("255_255_0.checkboard"));
  sut1->moveBy(glm::vec3(1.4f, 1.5f, -1.0f));
  engine->getCurrentScene()->attach(std::move(sut1));

  /* Model constructor 2 animated*/
  auto sut2 = std::make_unique<Model>(
    engine
    , programs.getProgram(EProgram::basicAnimated)
    , "animations/beast/beast.dae"
    , engine->storeTexture("textures/beast/beast_dxt1.DDS"));
  sut2->rotateByX(glm::radians(90.0f));
  sut2->moveByZ(-1.0f);
  sut2->setActiveAnimation(0);
  engine->getCurrentScene()->attach(std::move(sut2));

  /* Model constructor 2 not animated */
  auto sut3 = std::make_unique<Model>(
    engine
    , programs.getProgram(EProgram::basic)
    , "meshes/sphere.obj"
    , engine->storeTexture("255_0_0.checkboard"));
  sut3->scaleTo(0.01f);
  sut3->moveBy(glm::vec3(-0.7f, 0.7f, 0.0f));
  engine->getCurrentScene()->attach(std::move(sut3));

  /* Model constructor 3 */
  auto sut4 = std::make_unique<Model>(
    engine
    , programs.getProgram(EProgram::basic)
    , "meshes/sphere.obj"
    , "125_125_255.checkboard");
  sut4->scaleTo(0.01f);
  sut4->moveBy(glm::vec3(0.0f, 0.7f, 0.0f));
  engine->getCurrentScene()->attach(std::move(sut4));

  /* Model constructor 3 dynamic texture */
  auto sut5 = std::make_unique<Model>(
    engine
    , programs.getProgram(EProgram::basic)
    , "meshes/sphere.obj"
    , &engine->storeTextureDynamic("shaders/water/water.frag")->mTexture2DRenderable.mTexture2D);

  sut5->scaleTo(0.01f);
  sut5->moveBy(glm::vec3(-0.7f, 0.0f, 0.0f));
  engine->getCurrentScene()->attach(std::move(sut5));

  /* Emiter 1 CPU */
  auto emiter1 = std::make_unique<EmiterPointCPU>(
    engine
    , 0.3
    , 60000.0
    , glm::vec4(0.1, 0.1, 1.0, 1.0)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.9, 0.9, 0.9)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.0, 0.0, 0.0)
    , 10.0
    , 10.0
    , engine->storeTexture("textures/particle.png")
    , GL_SRC_ALPHA
    , GL_ONE
    , GL_FALSE);
  emiter1->moveBy(glm::vec3(-8.0, -4.0, -15.0));
  engine->getCurrentScene()->attach(std::move(emiter1));

  /* Emiter 2 GPU */
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  auto emiter2 = std::make_unique<EmiterPointGPU>(
    engine
    , 0.3
    , 600.0
    , glm::vec4(1.0, 1.0, 1.0, 1.0)
    , glm::vec3(0.0, 1.0, 0.0)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.9, 0.9, 0.9)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.6, 0.6, 0.6)
    , 1.0
    , 1.0
    , engine->storeTexture("textures/particle.png")
    , GL_SRC_ALPHA
    , GL_ONE
    , GL_FALSE);
  emiter2->moveBy(glm::vec3(0.0, -4.0, -15.0));
  engine->getCurrentScene()->attach(std::move(emiter2));

    engine->getCurrentScene()->setSkybox(std::make_unique<Skybox>(
    engine
    , engine->storeTexture3D(
      "textures/skybox/skybox/frozendusk/frozendusk_right.jpg"
      , "textures/skybox/skybox/frozendusk/frozendusk_left.jpg"
      , "textures/skybox/skybox/frozendusk/frozendusk_top.jpg"
      , ""
      , "textures/skybox/skybox/frozendusk/frozendusk_front.jpg"
      , "textures/skybox/skybox/frozendusk/frozendusk_back.jpg")));

#endif

  /* Emiter 3 CPU */
  auto emiter3 = std::make_unique<EmiterPointCPU>(
    engine
    , 0.3
    , 60000.0
    , glm::vec4(1.0, 1.0, 0.0, 1.0)
    , glm::vec3(0.0, 2.0, 0.0)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.9, 0.9, 0.9)
    , glm::vec3(0.0, 0.0, 0.0)
    , glm::vec3(0.0, 0.0, 0.0)
    , 10.0
    , 10.0
    , engine->storeTexture("textures/particle.png")
    , GL_SRC_ALPHA
    , GL_ONE
    , GL_FALSE);

  engine->getCurrentScene()->setCursor(std::make_unique<Cursor>(
    engine
    , engine->storeTexture("textures/cursor/standard_blue.png")));

  emiter3->moveBy(glm::vec3(8.0, -4.0, -15.0));
  engine->getCurrentScene()->attach(std::move(emiter3));

  engine->configFPSCounter("FreeSans", glm::vec2(-0.95f, 0.95f), 50.0f);
  engine->storeText("Benchmark", "FreeSans", glm::vec2(-0.95f, -0.85f), 50.0f);

  flw::Material m{};
  auto terrain = std::make_unique<MeshTerrain>(
    engine
    , programs.getProgram(EProgram::basic)
    , [](float x, float z) { return glm::abs(glm::sin(glm::radians(360 * x)) * glm::sin(glm::radians(360 * z))); }
    , m
    , "textures/test.png"
    , "textures/testNormal.png"
    , ""
    , 4
    , 4);
  terrain->scaleTo(0.1);
  terrain->moveToY(-2.0);
  engine->getCurrentScene()->attach(std::move(terrain));
}

void initCallbacks() {
  auto eng = ContextGLFW::mGraphics;
  eng->attachHandler([eng](const Event& event) {
    CursorPositionEventData e = event.getData();
    auto xPosition = ( ( e.xPosition / eng->getScreenSize()[0]) * 2.0 - 1.0);
    auto yPosition = (-( e.yPosition / eng->getScreenSize()[1]) * 2.0 + 1.0);
    eng->getCurrentScene()->getCursor()->move(glm::vec2(xPosition, yPosition));
  }, flw::flf::EEventType::cursorPosition);

  eng->attachHandler([eng](const flw::flf::Event& event) {
    flw::flf::KeyboardEventData e = event.getData();
    if (GLFW_KEY_D == e.key && e.action == GLFW_RELEASE) {
      eng->configDebugger(flw::EDebuggerState::toggleState);
    }
  }, flw::flf::EEventType::key);

  eng->attachHandler([eng](const Event& event) {
    MouseButtonEventData e = event.getData();
    if (e.action == GLFW_RELEASE) {
      eng->onPick(e.whereX, e.whereY);
    }
  }, flw::flf::EEventType::mouseButton);
}