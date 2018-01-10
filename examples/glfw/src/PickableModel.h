#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

using namespace flw;

class PickableModel : public flf::Model {
private:
  flf::ps<flf::Text> mText;
  pIEffect mPickedEffect;
  std::string mName;
public:
  PickableModel(std::string name,
      flf::ps<flf::Text> text,
      Engine *engine,
      flc::Program *program,
      const std::string &shapePath,
      const std::string &texturePath);

  virtual ~PickableModel();

  void onPicked();

  void onUnpicked();
};
