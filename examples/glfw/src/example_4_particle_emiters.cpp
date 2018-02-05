#include <example.h>
#include <ContextGLFW.h>

using namespace flw;
using namespace flw::flf;
using namespace flw::flc;
using namespace flw::flc;

struct WaterEmiter : public EmiterPointCPU {
  WaterEmiter()
    : EmiterPointCPU(ContextGLFW::mGraphics,
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
                     ContextGLFW::mGraphics->storeTexture("textures/particle.png"),
                     GL_SRC_ALPHA,
                     GL_ONE,
                     GL_FALSE) {
    moveBy(glm::vec3(0.0, -1.0, -1.0));
  }
};

struct SandEmiter : public EmiterPointCPU {
  SandEmiter()
    : EmiterPointCPU(ContextGLFW::mGraphics,
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
                     ContextGLFW::mGraphics->storeTexture("textures/particle.png"),
                     GL_SRC_ALPHA,
                     GL_ONE,
                     GL_FALSE) {
    // nothing
  }
};

struct SnowEmiter : public EmiterPointGPU {
  SnowEmiter()
    : EmiterPointGPU(ContextGLFW::mGraphics,
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
                     ContextGLFW::mGraphics->storeTexture("textures/particle.png"),
                     GL_SRC_ALPHA,
                     GL_ONE,
                     GL_FALSE) {
    // nothing
  }
};

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::mGraphics->attachHandler([](const Event& event) {
    KeyboardEventData e = event.getData();
    if (GLFW_KEY_T == e.key) {
      ContextGLFW::mGraphics->configTime(0.0f);
    } else {
      ContextGLFW::mGraphics->configTime(1.0f);
    }
  }, flw::flf::eEventType::key);

  auto camera = std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0);
  camera->moveTo(glm::vec3(0.0, 0.0, 7.0));

  auto scene = std::make_unique<Scene>();
  scene->attachNew<WaterEmiter>();
  scene->attachNew<SandEmiter>();
  scene->attachNew<SnowEmiter>();
  scene->setCamera(std::move(camera));

  ContextGLFW::mGraphics->setCurrentScene(std::move(scene));

  mContext.render();
  exit(EXIT_SUCCESS);
}

