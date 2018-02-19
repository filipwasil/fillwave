#pragma once

#include <example.h>
#include <ContextGLFW.h>

class PickableModel : public flw::flf::Model {
 public:

  PickableModel(std::string name,
    flw::ps<flw::flf::Text> text,
    flw::Engine* engine,
    glm::vec3 initialPosition);

  ~PickableModel() override;

  void onPicked() override;

  void onUnpicked() override;

 private:
  flw::ps<flw::flf::Text> mText;
  flw::ps<flw::flf::IEffect> mPickedEffect;
  std::string mName;
};

void initCallbacks();
