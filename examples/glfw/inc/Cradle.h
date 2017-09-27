#pragma once

#include "fillwave/Fillwave.h"

class Cradle {
public:
  Cradle(flw::Engine* engine);
  void setAcceleration(float vertical, float horizontal, float frontal);

private:
  flw::pText mAccelerationF;
  flw::pText mAccelerationH;
  flw::pText mAccelerationV;
  flw::pText mSpeed;
};
