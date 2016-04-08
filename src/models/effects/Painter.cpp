/*
 * Painter.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: filip
 */

#include <fillwave/models/effects/Painter.h>

namespace fillwave {
namespace framework {

Painter::Painter(glm::vec4 color) :
	mColor(color) {

}

void Painter::setColor(glm::vec4 color) {
	mColor = color;
}

void Painter::preDrawAction(core::Program* program) {
	program->uniformPush("uPainterEffect", true);
	program->uniformPush("uPainterColor", mColor);
}

void Painter::postDrawAction(core::Program* program) {
	program->uniformPush("uPainterEffect", false);
}

void Painter::stopAction(core::Program* program) {
	program->uniformPush("uPainterEffect", false);
}

void Painter::startAction(core::Program* program) {
	program->uniformPush("uPainterColor", mColor);
}

} /* framework */
} /* fillwave */
