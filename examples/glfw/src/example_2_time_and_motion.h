#pragma once

#include <example.h>
#include <ContextGLFW.h>

class CubeModel : public flw::flf::Model {
 public:
  CubeModel(int i, float t);

  ~CubeModel() override;
};

class WallModel : public flw::flf::Model {
 public:
  WallModel();

  ~WallModel() override;
};

void initCallbacks();
