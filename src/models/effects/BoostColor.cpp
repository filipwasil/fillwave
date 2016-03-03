/*
 * BoostColor.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: filip
 */

#include <fillwave/models/effects/BoostColor.h>

namespace fillwave {
namespace framework {

BoostColor::BoostColor(GLfloat boost) :
		mBoost(boost) {

}

void BoostColor::preDrawAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", true);
	program->uniformPush("uBoostColorFactor", mBoost);
}

void BoostColor::postDrawAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", false);
}

void BoostColor::stopAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", false);
}

void BoostColor::startAction(core::Program* program) {
	program->uniformPush("uBoostColorEffect", true);
}

} /* framework*/
} /* fillwave */
