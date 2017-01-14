#include <fillwave/space/Scene.h>
#include <fillwave/models/EmiterPointGPU.h>
#include <fillwave/actions/callbacks/TimedEmiterUpdateCallback.h>
#include "Renderer.h"

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

Renderer::Renderer(int argc, char* argv[], QWidget* parent) :
        QGLWidget{parent}, mArgc{argc}, mArgv{argv}
{
    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    setFormat(glFormat);
}

Renderer::~Renderer()
{
}

void Renderer::initializeGL()
{
    mEngine = unique_ptr<Engine>(new Engine(mArgc, mArgv));

    mEngine->setCurrentScene(make_unique<Scene>());
    mEngine->getCurrentScene()->setCamera(make_unique<CameraPerspective>(glm::vec3(0.0,0.0,6.0),
                                                                         glm::quat(),
                                                                         glm::radians(90.0),
                                                                         1.0,
                                                                         0.1,
                                                                         1000.0));
    puIEmiterPoint snow = make_unique<EmiterPointCPU>(mEngine.get(),
                                                          0.3,
                                                          600.0,
                                                          glm::vec4(1.0,1.0,1.0,1.0),
                                                          glm::vec3(0.0,1.0,0.0),
                                                          glm::vec3(0.0,0.0,0.0),
                                                          glm::vec3(0.9,0.9,0.9),
                                                          glm::vec3(0.0,0.0,0.0),
                                                          glm::vec3(0.6,0.6,0.6),
                                                          1.0,
                                                          1.0,
                                                          mEngine->storeTexture("assets/alphaMask.png"),
                                                          GL_SRC_ALPHA,
                                                          GL_ONE,
                                                          GL_FALSE);

    snow->attachHierarchyCallback(make_unique<TimedEmiterUpdateCallback>(snow.get(), FILLWAVE_ENDLESS));

    mEngine->getCurrentScene()->attach(std::move(snow));

    mEngine->storeText("Fillwave editor", "FreeSans", glm::vec2(-0.95f, 0.95f), 50.0f);
}

void Renderer::paintGL()
{
    mEngine->draw(1.0f/60.0f);
    update();
}

void Renderer::resizeGL(int width, int height)
{
    mEngine->insertResizeScreen(static_cast<GLuint>(width), static_cast<GLuint>(height));
}

void Renderer::onUpdate(int /*sliderNo*/, int /*value*/) const
{
    abort(); /* Testing */
}