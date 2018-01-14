#pragma once

#include <fillwave/Fillwave.h>
#include <fillwave/Framework.h>

using namespace flw;

class PickableModel: public flf::Model {
 private:
	flw::flf::ps<flw::flf::Text> mText;
	pIEffect mPickedEffect;
	std::string mName;
 public:
	PickableModel(std::string name,
	              flw::flf::ps<flw::flf::Text> text,
	              Engine* engine,
	              flc::Program* program,
	              const std::string& shapePath,
	              const std::string& texturePath);
	virtual ~PickableModel();
	void onPicked() override;
	void onUnpicked() override;
};
