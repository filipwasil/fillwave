#pragma once

#include <fillwave/Fillwave.h>
#include <memory>
#include "scene/AScene.h"

namespace scene {

class TerrainScene : public AScene {
Q_OBJECT
  Q_PROPERTY(QMap sceneParameter
                 READ
                 getParameters
                 WRITE
                 setParameters)
public:
  TerrainScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  ~TerrainScene() override = default;

  void init() override;

  void perform() override;

private:
  flw::ps<flw::flf::Text> mText;
  std::unique_ptr<flw::flf::TimeStopCallback> mTimeCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mCameraCallback;
  std::unique_ptr<flw::flf::FollowCustomCursorCallback> mSecondCameraCallback;
};

}



