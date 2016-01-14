/*
 * Button.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#include <fillwave/hud/Button.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

Button::Button(
		Engine* engine,
		glm::vec2 position,
		glm::vec2 scale)
		: IHUDNode(engine->storeTextureRenderable(),
				ProgramLoader(engine).getHUD(),
				position, scale) {

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
