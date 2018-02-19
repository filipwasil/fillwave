#include "example_3_cursor_picking.h"

using namespace flw;
using namespace flw::flf;
using namespace flw::flc;
using namespace flw::flc;

PickableModel::PickableModel(std::string name,
  flw::ps<flw::flf::Text> text,
  flw::Engine* engine,
  glm::vec3 initialPosition)
  : flw::flf::Model(engine
    , ProgramLoader(engine).getProgram(EProgram::basic)
    , "meshes/sphere.obj"
    , "64_128_255.checkboard")
    , mText(text)
    , mPickedEffect(std::make_shared<flw::flf::BoostColor>(6.0f))
    , mName(name) {
  scaleTo(0.1);
  moveBy(initialPosition);
  ContextGLFW::mGraphics->getCurrentScene()->registerPickable(this);
}

PickableModel::~PickableModel() {
  // nothing
}

void PickableModel::onPicked() {
  mText->editString("Picked " + mName);
  addEffect(mPickedEffect);
}

void PickableModel::onUnpicked() {
  removeEffect(mPickedEffect);
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
      eng->pick(e.whereX, e.whereY);
    }
  }, flw::flf::EEventType::mouseButton);
}

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::cursorHide();

  auto eng = ContextGLFW::mGraphics;

  initCallbacks();

  auto scene = std::make_unique<Scene>();
  auto camera = std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0);

  scene->setCamera(std::move(camera));

  scene->setCursor(std::make_unique<Cursor>(eng, eng->storeTexture("textures/cursor/cool.png")));

  eng->setCurrentScene(std::move(scene));

  auto info = eng->storeText("Nothing picked", "fonts/Titania", glm::vec2(-0.98, 0.98), 60.0);
  eng->getCurrentScene()->attachNew<PickableModel>("left", info, eng, glm::vec3(-3.0, 0.0, 0.0));
  eng->getCurrentScene()->attachNew<PickableModel>("right", info, eng, glm::vec3(3.0, 0.0, 0.0));
  eng->getCurrentScene()->attachNew<PickableModel>("center", info, eng, glm::vec3(0.0, 0.0, 0.0));
  eng->getCurrentScene()->attachNew<PickableModel>("up", info, eng, glm::vec3(0.0, 3.0, 0.0));
  eng->getCurrentScene()->attachNew<PickableModel>("down", info, eng, glm::vec3(0.0, -3.0, 0.0));

  mContext.render();
  exit(EXIT_SUCCESS);
}

