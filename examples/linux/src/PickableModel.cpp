/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "../../linux/src/PickableModel.h"

#include <fillwave/Log.h>
#include <fillwave/models/effects/BoostColor.h>

FLOGINIT("PickableModel", FERROR | FFATAL)

PickableModel::PickableModel(std::string name,
    pText text,
    Engine *engine,
    flc::Program *program,
    const std::string &shapePath,
    const std::string &texturePath)
    : flf::Model(engine, program, shapePath, texturePath), mText(text), mName(name) {
  mPickedEffect = std::make_shared<flf::BoostColor>(2.0f);
}

PickableModel::~PickableModel() {

}

void PickableModel::onPicked() {
  mText->editString("Picked " + mName);
  addEffect(mPickedEffect);
}

void PickableModel::onUnpicked() {
  removeEffect(mPickedEffect);
}
