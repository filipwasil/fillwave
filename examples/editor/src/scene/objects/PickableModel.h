#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

using namespace flw;

class PickableModel: public flf::Model {
 private:
	flw::ps<flw::flf::Text> mText;
    ps<flf::IEffect> mPickedEffect;
	std::string mName;
 public:
	PickableModel(std::string name,
	              flw::ps<flw::flf::Text> text,
	              Engine* engine,
	              flc::Program* program,
	              const std::string& shapePath,
	              const std::string& texturePath);
	virtual ~PickableModel();
	void onPicked() override;
	void onUnpicked() override;
};
