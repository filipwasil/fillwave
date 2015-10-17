/*
 * ClockwiseDrawEffect.cpp
 *
 *  Created on: 24 Jul 2014
 *      Author: filip
 */

#include <fillwave/effects/ClockwiseDrawEffect.h>

namespace fillwave {
namespace effects {

void ClockwiseDrawEffect::preDrawAction(core::Program* program) {
	glFrontFace(GL_CW);
}

void ClockwiseDrawEffect::postDrawAction(core::Program* program) {
	glFrontFace(GL_CCW);
}

void ClockwiseDrawEffect::stopAction(core::Program* program) {

}

void ClockwiseDrawEffect::startAction(core::Program* program) {

}

} /* effects */
} /* fillwave */
