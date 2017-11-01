#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/models/EmiterPointCPU.h>
#include "scene/AScene.h"

namespace scene {
class ParticlesScene : public AScene {
  Q_OBJECT
  Q_PROPERTY(QMap sceneParameter READ getParameters WRITE setParameters)
public:
  ParticlesScene(int argc, char **argv, QMap<QString, QVariant> varValues);

  virtual ~ParticlesScene(){}

  void init() override;

  void perform() override;

private:
  float mAcceleration;
  float mSpeed;
  float mRP;
  float mRV;
  float mWaterColor;
  float mSandColor;
  flw::flf::EmiterPointCPU* mWaterPtr;
  flw::flf::EmiterPointCPU* mSandPtr;
  int mArgc;
  char **mArgv;
  std::unique_ptr<flw::flf::TimeStopCallback> mTimeCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mCameraCallback;
  std::unique_ptr<flw::flf::MoveCameraCallback> mSecondCameraCallback;
};

}
