//
// Created by filip on 30.04.16.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <fillwave/Fillwave.h>
#include <QGLWidget>
#include <memory>

class Renderer : public QGLWidget
{
    Q_OBJECT
public:
    explicit Renderer(int argc, char* argv[], QWidget *parent = 0);
    virtual ~Renderer();

public slots:
    void onUpdate(int sliderNo, int value) const;

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);

private:
    std::unique_ptr<fillwave::Engine> mEngine;
    int mArgc;
    char** mArgv;
};


#endif //FILLWAVE_QT_EXAMPLE_RENDERER_H
