//
// Created by filip on 25.04.16.
//

#include "MainWidget.h"
#include "Renderer.h"
#include "Panel.h"
#include <QVBoxLayout>
#include <QVBoxLayout>

//#include <QSlider>
//#include <QLabel>

MainWidget::MainWidget(int argc, char* argv[], QWidget* parent) :
        QWidget(parent),
        mRenderer(new Renderer (argc, argv)),
        mPanel(new Panel (this, "assets/logo.png"))
{
    /* Main layout */
    QVBoxLayout *horizontal = new QVBoxLayout();
    horizontal->setDirection(QBoxLayout::LeftToRight);

    /* Panel layout */

    /* OpenGL layout */
    QVBoxLayout *layoutEngineWindow = new QVBoxLayout();
    mRenderer->setLayout(layoutEngineWindow);
    resize(800,400);

    /* Main assemply */
    this->setLayout(horizontal);
    horizontal->addWidget(mPanel);
    horizontal->addWidget(mRenderer);

    QObject::connect(mPanel, &Panel::onChanged,
                     mRenderer, &Renderer::onUpdate);
}

MainWidget::~MainWidget()
{

}
