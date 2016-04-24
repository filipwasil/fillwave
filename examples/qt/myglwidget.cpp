/**
 * Copyright (C) 2015, Dariusz Kluska <darkenk@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <fillwave/space/ScenePerspective.h>
#include "myglwidget.hpp"

using namespace fillwave;
using namespace fillwave::framework;
using namespace std;

MyGLWidget::MyGLWidget(int argc, char* argv[], QWidget* parent) :
    QGLWidget{parent}, mArgc{argc}, mArgv{argv}
{
    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    setFormat(glFormat);
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::initializeGL()
{
    mEngine = unique_ptr<Engine>(new Engine(mArgc, mArgv));
    pCameraPerspective camera = make_shared<CameraPerspective>(glm::vec3(0.0,0.0,6.0), glm::quat());
    auto scene = make_shared<ScenePerspective>(camera);
    mEngine->setCurrentScene(scene);
    mEngine->storeText("Fillwave QT widget example", "FreeSans", glm::vec2(-0.95f, 0.2f), 50.0f);
}

void MyGLWidget::paintGL()
{
    static int i = 0;
    mEngine->draw(static_cast<float>(++i));
    update();
}

void MyGLWidget::resizeGL(int width, int height)
{
    mEngine->insertResizeScreen(static_cast<GLuint>(width), static_cast<GLuint>(height));
}
