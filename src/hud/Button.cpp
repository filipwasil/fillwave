/*
 * Button.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#include <fillwave/hud/Button.h>

namespace fillwave {
namespace framework {

Button::Button(
		pTexture2D texture,
		GLfloat xPosition,
		GLfloat yPosition)
		: IHUDNode(texture, xPosition, yPosition, 1) {

}

Button::~Button() {

}

void Button::onPicked() {

}

void Button::onUnpicked() {

}

void Button::draw() {

}

} /* namespace framework */
} /* namespace fillwave */
