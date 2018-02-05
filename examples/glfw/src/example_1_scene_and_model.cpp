#include <example.h>
#include <ContextGLFW.h>

using namespace flw;
using namespace flw::flf;
using namespace flw::flc;
using namespace flw::flc;

const GLint SPHERES = 5;

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  init();
  mContext.render();
  exit(EXIT_SUCCESS);
}

class TestModel : public Model {
 public:
  TestModel()
    : Model(
      ContextGLFW::mGraphics
      , ProgramLoader(ContextGLFW::mGraphics).getProgram(EProgram::basicAnimated)
      , "animations/beast/beast.dae") {

    attachHandler([this](const Event& event) {
      KeyboardEventData e = event.getData();
      if (GLFW_KEY_0 == e.key) {
        setActiveAnimation(0);
      } else {
        setActiveAnimation(1);
      }
    }, flw::flf::eEventType::key);

    scaleTo(3.0f);
    rotateByX(90.0f);
  }
};

void init() {
  auto scene = std::make_unique<Scene>();
  auto camera = std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0);

  scene->attachNew<TestModel>();

  scene->setCamera(std::move(camera));

  ContextGLFW::mGraphics->setCurrentScene(std::move(scene));
}
