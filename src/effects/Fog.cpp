/*
 * Fog.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: Filip Wasil
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/effects/Fog.h>

#include <fillwave/extras/Log.h>

FLOGINIT("Fog", FERROR | FFATAL)

namespace fillwave {
namespace effects {

Fog::Fog(glm::vec3 colour,
         GLfloat near,
         GLfloat far):mColour(colour),
                      mNearDistance(near),
                      mFarDistance(far){
}

Fog::~Fog() {

}

void Fog::preDrawAction(core::Program* program) {
   program->uniformPush("uFogEffect", true);
}

void Fog::postDrawAction(core::Program* program) {
   program->uniformPush("uFogEffect", false);
}

void Fog::stopAction(core::Program* program) {
   program->uniformPush("uFogEffect", false);
}

void Fog::startAction(core::Program* program) {
   program->uniformPush("uFogEffect", true);
   program->uniformPush("uFogColor", mColour);
   program->uniformPush("uFogNearDistance", mNearDistance);
   program->uniformPush("uFogFarDistance", mFarDistance);
}

} /* effects */
} /* fillwave */
