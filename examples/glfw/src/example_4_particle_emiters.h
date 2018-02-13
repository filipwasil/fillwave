#pragma once

#include <example.h>
#include <ContextGLFW.h>

struct WaterEmiter : public flw::flf::EmiterPointCPU {
  WaterEmiter();

  ~WaterEmiter() override;
};

struct SandEmiter : public flw::flf::EmiterPointCPU {
  SandEmiter();

  ~SandEmiter() override;
};

struct SnowEmiter : public flw::flf::EmiterPointGPU {
  SnowEmiter();

  ~SnowEmiter() override;
};
