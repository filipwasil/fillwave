/*
 * Painter.cpp
 *
 *  Created on: Oct 6, 2014
 *      Author: filip
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
 * fillwave@gmail.com
 *
 */

#include <fillwave/effects/Painter.h>

namespace fillwave {
namespace effects {

Painter::Painter(glm::vec4 color)
		: mColor(color) {

}

Painter::~Painter() {

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

} /* effects */
} /* fillwave */
