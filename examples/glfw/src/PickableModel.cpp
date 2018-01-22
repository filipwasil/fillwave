/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "PickableModel.h"
#include <fillwave/Log.h>

PickableModel::PickableModel(std::string name,
    flw::ps<flw::flf::Text> text,
    flw::Engine* engine,
    flw::flc::Program* program,
    const std::string& shapePath,
    const std::string& texturePath)
    : flw::flf::Model(engine, program, shapePath, texturePath)
    , mText(text)
    , mPickedEffect(std::make_shared<flw::flf::BoostColor>(2.0f))
    , mName(name) {
  // nothing
}

PickableModel::~PickableModel() {
  // nothing
}

void PickableModel::onPicked() {
  mText->editString("Picked " + mName);
  addEffect(mPickedEffect);
}

void PickableModel::onUnpicked() {
  removeEffect(mPickedEffect);
}
