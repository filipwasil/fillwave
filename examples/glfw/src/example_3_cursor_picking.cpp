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

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);
  ContextGLFW::cursorHide();

  auto engine = ContextGLFW::mGraphics;

  engine->attachHandler([engine](const Event& event) {
    CursorPositionEventData e = event.getData();
    auto xPosition = ( ( e.xPosition / engine->getScreenSize()[0]) * 2.0 - 1.0);
    auto yPosition = (-( e.yPosition / engine->getScreenSize()[1]) * 2.0 + 1.0);
    engine->getCurrentScene()->getCursor()->move(glm::vec2(xPosition, yPosition));
  }, flw::flf::EEventType::cursorPosition);

  ContextGLFW::mGraphics->attachHandler([](const flw::flf::Event& event) {
    flw::flf::KeyboardEventData e = event.getData();
    if (GLFW_KEY_D == e.key && e.action == GLFW_RELEASE) {
      ContextGLFW::mGraphics->configDebugger(flw::EDebuggerState::toggleState);
    }
  }, flw::flf::EEventType::key);

  engine->attachHandler([engine](const Event& event) {
    MouseButtonEventData e = event.getData();
    if (e.action == GLFW_RELEASE) {
      engine->pick(e.whereX, e.whereY);
    }
  }, flw::flf::EEventType::mouseButton);

  auto scene = std::make_unique<Scene>();
  auto camera = std::make_unique<CameraPerspective>(glm::vec3(0.0, 0.0, 6.0),
                                                    glm::quat(),
                                                    glm::radians(90.0),
                                                    1.0,
                                                    0.1,
                                                    1000.0);

  scene->setCamera(std::move(camera));

  scene->setCursor(std::make_unique<Cursor>(
    engine, engine->storeTexture("textures/cursor/cool.png")));

  engine->setCurrentScene(std::move(scene));

  auto info = engine->storeText("Nothing picked", "fonts/Titania", glm::vec2(-0.98, 0.98), 60.0);
  engine->getCurrentScene()->attachNew<PickableModel>("left", info, engine, glm::vec3(-3.0, 0.0, 0.0));
  engine->getCurrentScene()->attachNew<PickableModel>("right", info, engine, glm::vec3(3.0, 0.0, 0.0));
  engine->getCurrentScene()->attachNew<PickableModel>("center", info, engine, glm::vec3(0.0, 0.0, 0.0));
  engine->getCurrentScene()->attachNew<PickableModel>("up", info, engine, glm::vec3(0.0, 3.0, 0.0));
  engine->getCurrentScene()->attachNew<PickableModel>("down", info, engine, glm::vec3(0.0, -3.0, 0.0));

  mContext.render();
  exit(EXIT_SUCCESS);
}

