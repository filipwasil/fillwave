#include "Renderer.h"
#include "scene/sceneImp/EmptyScene.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

using Time = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;

Renderer::Renderer(int argc, char* argv[], QWidget* parent)
  : QGLWidget{parent}
  , mArgc{argc}
  , mArgv{argv} {
  QGLFormat glFormat;
  glFormat.setVersion(3, 3);
  glFormat.setProfile(QGLFormat::CoreProfile);
  setFormat(glFormat);
  this->makeCurrent();
  QMap<QString, QVariant> text;
  text["mText"] = "Hello World";
  mScene = std::make_shared<scene::EmptyScene>(mArgc, mArgv);
  mTime = Time::now();
  this->setFocusPolicy(Qt::StrongFocus);
  this->setMouseTracking(true);
}

void Renderer::initializeGL() {

}

void Renderer::paintGL() {
  auto currentTime = Time::now();
  flw::flf::EventData eventdata;
  eventdata.mTime.timePassed = std::chrono::duration<float>(currentTime - mTime).count();
  flw::flf::Event event(flw::flf::EEventType::time, eventdata);
  mScene->getEngine()->onEvent(event);
  mScene->getEngine()->draw();
  mTime = currentTime;
  update();
}

void Renderer::resizeGL(int width, int height) {
  mScene->getEngine()->onResizeScreen(static_cast<GLuint>(width), static_cast<GLuint>(height));
}

void Renderer::onUpdate(int /*sliderNo*/, int /*value*/) const {

}

void Renderer::setNewScene(std::shared_ptr<scene::AScene> scen) {
}

std::shared_ptr<scene::AScene> Renderer::getScen() {
  return mScene;
}
