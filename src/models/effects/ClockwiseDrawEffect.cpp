/*
 * ClockwiseDrawEffect.cpp
 *
 *  Created on: 24 Jul 2014
 *      Author: filip
 */

#include <fillwave/models/effects/ClockwiseDrawEffect.h>

namespace fillwave {
namespace framework {

void ClockwiseDrawEffect::preDrawAction(core::Program*) {
	glFrontFace(GL_CW);
}

void ClockwiseDrawEffect::postDrawAction(core::Program*) {
	glFrontFace(GL_CCW);
}

void ClockwiseDrawEffect::stopAction(core::Program*) {

}

void ClockwiseDrawEffect::startAction(core::Program*) {

}

} /* framework */
} /* fillwave */
