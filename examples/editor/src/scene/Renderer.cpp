#include "Renderer.h"
#include "scene/sceneImp/AnimationScene.h"
#include "scene/ScensFactory.h"

using namespace flw;
using namespace flw::flf;
using namespace std;

Renderer::Renderer(int argc, char *argv[], QWidget *parent)
    : QGLWidget{parent}, mArgc{argc}, mArgv{argv} {
  QGLFormat glFormat;
  glFormat.setVersion(3, 3);
  glFormat.setProfile(QGLFormat::CoreProfile);
  setFormat(glFormat);
  this->makeCurrent();
  mScene = std::make_shared<scene::AnimationScene>(mArgc, mArgv);
}

Renderer::~Renderer() {
}

void Renderer::initializeGL() {

}

void Renderer::paintGL() {
  mScene->getEngine()->draw(1.0f / 60.0f);
  update();
}

void Renderer::resizeGL(int width, int height) {
  mScene->getEngine()->insertResizeScreen(static_cast<GLuint>(width), static_cast<GLuint>(height));
}

void Renderer::onUpdate(int /*sliderNo*/, int /*value*/) const {

}

void Renderer::setNewScene(std::shared_ptr<scene::AScene> scen) {
  mScene = scen;
}

std::shared_ptr<scene::AScene> Renderer::getScen() {
  return mScene;
}
