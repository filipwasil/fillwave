#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

class PickableModel : public flw::flf::Model {
public:
  PickableModel(std::string name,
      flw::ps<flw::flf::Text> text,
      flw::Engine* engine,
      flw::flc::Program* program,
      const std::string& shapePath,
      const std::string& texturePath);

  ~PickableModel() override;

  void onPicked() override;

  void onUnpicked() override;

private:
    flw::ps<flw::flf::Text> mText;
    flw::ps<flw::flf::IEffect> mPickedEffect;
    std::string mName;
};
