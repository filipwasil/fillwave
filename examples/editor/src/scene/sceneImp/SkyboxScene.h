#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"
#include "scene/callbacks/Callbacks.h"

namespace scene {
class SkyboxScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  SkyboxScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~SkyboxScene() {}

  void init() override;

  void perform() override;

private:
  flw::pText mText;
  int mArgc;
  char **mArgv;
  std::unique_ptr<flw::flf::TimeStopCallback> mTimeCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mCameraCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mSecondCameraCallback;
};

}
