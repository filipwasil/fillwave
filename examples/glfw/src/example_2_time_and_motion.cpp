#include "example_2_time_and_motion.h"

CubeModel::CubeModel(int i, float t)
  : Model(
  ContextGLFW::mGraphics
  , flw::flf::ProgramLoader(ContextGLFW::mGraphics).getProgram(flw::flf::EProgram::basic)
  , "meshes/cubemap.obj"
  , "textures/test.png") {

  scaleTo(0.005);
  moveByX(-4 + 2 * i);
  rotateByX(glm::radians(45.0f));
  scaleBy(t, glm::vec3(0.05f), ElasticEaseIn);
  scaleTo(t, glm::vec3(0.005f), ElasticEaseIn);
  rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseIn);
  rotateBy(t, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0), BounceEaseOut);
  moveBy(t, glm::vec3(-(0.5f * 5.0f) + i, -2.0, 0.0), ElasticEaseIn);
  moveBy(t, glm::vec3( (0.5f * 5.0f) - i, 2.0, 0.0), ElasticEaseIn);
  loop(10);

  scaleTo(3.0f);
  rotateByX(90.0f);
}

CubeModel::~CubeModel() = default;

WallModel::WallModel()
  : Model(
  ContextGLFW::mGraphics
  , flw::flf::ProgramLoader(ContextGLFW::mGraphics).getProgram(flw::flf::EProgram::basic)
  , "meshes/floor.obj") {

  rotateByX(glm::radians(90.0));
  moveInDirection(glm::vec3(0.0, -10.0, 0.0));
  scaleTo(3.0);
}

WallModel::~WallModel() = default;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);

  ContextGLFW::mGraphics->storeLightSpot(glm::vec3(0.0, 0.0, 5.0), glm::quat(), glm::vec4(0.0, 1.0, 0.0, 0.0));

  ContextGLFW::mGraphics->attachHandler([](const flw::flf::Event& event) {
    flw::flf::KeyboardEventData e = event.getData();
    if (GLFW_KEY_T == e.key) {
      ContextGLFW::mGraphics->configTime(0.0f);
    } else {
      ContextGLFW::mGraphics->configTime(1.0f);
    }
  }, flw::flf::EEventType::key);

  auto camera = std::make_unique<flw::flf::CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0);
  camera->moveTo(glm::vec3(0.0, 0.0, 7.0));

  auto scene = std::make_unique<flw::flf::Scene>();
  for (GLint i = 0; i < 5; ++i) {
    const auto t = 1.0f + static_cast<float>(i) * 0.5f;
    scene->attachNew<CubeModel>(i, t);
  }
  scene->attachNew<WallModel>();
  scene->setCamera(std::move(camera));

  ContextGLFW::mGraphics->setCurrentScene(std::move(scene));

  mContext.render();
  exit(EXIT_SUCCESS);
}

