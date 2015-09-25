/*
 * PickableModel.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: filip
 */

#include "PickableModel.h"
#include <fillwave/extras/Log.h>
#include <fillwave/effects/BoostColor.h>

FLOGINIT("PickableModel", FERROR | FFATAL)

PickableModel::PickableModel(std::string name,
                             pText text,
                             Engine* engine,
                             pProgram program,
                             const std::string& shapePath,
                             const std::string& texturePath):models::Model(engine,
                                                                           program,
                                                                           shapePath,
                                                                           texturePath),
                                                                     mText(text),
                                                                     mName(name){
   mPickedEffect = pEffect(new effects::BoostColor(2.0f));
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
