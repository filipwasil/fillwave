/*
 * Fog.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: Filip Wasil
 */

#include <fillwave/models/effects/Fog.h>

#include <fillwave/Log.h>

FLOGINIT("Fog", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Fog::Fog(glm::vec3 colour, GLfloat near, GLfloat far) :
		mColour(colour), mNearDistance(near), mFarDistance(far) {
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

} /* framework */
} /* fillwave */
