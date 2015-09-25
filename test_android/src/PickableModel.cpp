/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "PickableModel.h"
#include <fillwave/extras/Log.h>
#include <fillwave/effects/BoostColor.h>

FLOGINIT("name", FERROR | FFATAL)

using namespace fillwave;

PickableModel::PickableModel(std::string name,
                             pText text,
                             Engine* engine,
                             pProgram program,
                             const std::string& shapePath):models::Model(engine,
                                                                           program,
                                                                           shapePath),
                                                                     mText(text),
                                                                     mName(name){
   mPickedEffect = pEffect(new effects::BoostColor(2.0f));
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
