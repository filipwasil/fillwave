#include <example.h>
#include <ContextGLFW.h>
#include <fillwave/Log.h>

using namespace flw;
using namespace flw::flf;
using namespace flw::flc;
using namespace flw::flc;

FLOGINIT_DEFAULT()

int main(int argc, char* argv[]) {
  ContextGLFW mContext(argc, argv);

  ContextGLFW::mGraphics->attachHandler([](const Event& event) {
    CursorPositionEventData e = event.getData();
    auto xPosition = ( ( e.xPosition / ContextGLFW::mGraphics->getScreenSize()[0]) * 2.0 - 1.0);
    auto yPosition = (-( e.yPosition / ContextGLFW::mGraphics->getScreenSize()[1]) * 2.0 + 1.0);
    ContextGLFW::mGraphics->getCurrentScene()->getCursor()->move(glm::vec2(xPosition, yPosition));
  }, flw::flf::eEventType::cursorPosition);

  auto scene = std::make_unique<Scene>();
  scene->setCamera(std::make_unique<CameraPerspective>());

  auto textureC = ContextGLFW::mGraphics->storeTexture("textures/cursor/standard_blue.png");

  scene->setCursor(std::make_unique<Cursor>(ContextGLFW::mGraphics, textureC));

  ContextGLFW::mGraphics->setCurrentScene(std::move(scene));

  mContext.render();
  exit(EXIT_SUCCESS);
}

