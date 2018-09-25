#pragma once

#include <flw/Fillwave.h>
#include <QGLWidget>
#include <chrono>
#include <memory>
#include <QMap>
#include <QVariant>
#include "AScene.h"

class Renderer : public QGLWidget {
 public:
  explicit Renderer(int argc, char* argv[], QWidget* parent = nullptr);

  virtual ~Renderer() = default;

  void setNewScene(std::shared_ptr<scene::AScene> scen);

  std::shared_ptr<scene::AScene> getScen();

 public slots:

  void onUpdate(int sliderNo, int value) const;

 protected:
  virtual void initializeGL();

  virtual void paintGL();

  virtual void resizeGL(int width, int height);

 private:
  int mArgc;
  char** mArgv;
  decltype(std::chrono::high_resolution_clock::now()) mTime;
  std::shared_ptr<scene::AScene> mScene;
};
