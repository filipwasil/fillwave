/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "PickableModel.h"
#include <fillwave/Log.h>

PickableModel::PickableModel(std::string name,
                             flw::flf::ps<flw::flf::Text> text,
                             Engine* engine,
                             flc::Program* program,
                             const std::string& shapePath,
                             const std::string& texturePath): flf::Model(engine,
	                                   program,
	                                   shapePath,
	                                   texturePath),
	mText(text),
	mName(name) {
	mPickedEffect = pIEffect(new flf::BoostColor(2.0f));
}

PickableModel::~PickableModel() = default;

void PickableModel::onPicked() {
	mText->editString("Picked " + mName);
	addEffect(mPickedEffect);
}

void PickableModel::onUnpicked() {
	removeEffect(mPickedEffect);
}
