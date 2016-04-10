/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "../../android/src/PickableModel.h"

#include <fillwave/Log.h>
#include <fillwave/models/effects/BoostColor.h>

FLOGINIT("name", FERROR | FFATAL)

using namespace fillwave;
using namespace fillwave::framework;

PickableModel::PickableModel(std::string name,
                             pText text,
                             Engine* engine,
                             core::Program* program,
                             const std::string& shapePath):Model(engine,
                                                                           program,
                                                                           shapePath),
                                                                     mText(text),
                                                                     mName(name){
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
