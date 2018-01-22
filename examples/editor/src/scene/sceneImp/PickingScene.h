#pragma once

#include <fillwave/Fillwave.h>
#include "scene/AScene.h"
#include "scene/callbacks/Callbacks.h"

namespace scene {
class PickingScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  PickingScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~PickingScene(){}

  void init() override;

  void perform() override;

private:
  flw::ps<flw::flf::Text> mText;
  int mArgc;
  char **mArgv;
  std::unique_ptr<flw::flf::TimeStopCallback> mTimeCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mCameraCallback;
  std::unique_ptr<flw::flf::FollowCustomCursorCallback> mCustomCursorCallback;
  std::unique_ptr<flw::flf::ColorPickingCallback> mColorCallback;
};

}
