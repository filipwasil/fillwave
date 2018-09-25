/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "../../android/src/PickableModel.h"

#include <flw/Log.h>
#include <flw/flf/models/effects/BoostColor.h>

FLOGINIT("name", FERROR | FFATAL)

using namespace flw;
using namespace flw::framework;

PickableModel::PickableModel(std::string name,
    flw::flf::ps<flw::flf::Text> text,
    Engine *engine,
    flc::Program *program,
    const std::string &shapePath)
    : Model(engine, program, shapePath), mText(text), mName(name) {
  mPickedEffect = pIEffect(new BoostColor(2.0f));
}

PickableModel::~PickableModel() {

}

void PickableModel::onPicked() {
  mText->editString("Picked " + mName);
  addEffect(mPickedEffect);
  this->setActiveAnimation(0);
}

void PickableModel::onUnpicked() {
  removeEffect(mPickedEffect);
  this->setActiveAnimation(FILLWAVE_DO_NOT_ANIMATE);
}
