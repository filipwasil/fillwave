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
		const pTexture2D& texture,
		glm::vec2 position,
		glm::vec2 scale) :
			IHUDNode(texture, ProgramLoader(engine).getHUD(), position,
				glm::vec2(scale.x, scale.y * engine->getScreenAspectRatio())) {

}

void Button::pick(glm::vec3 /*color*/) {
	mFlagPickable = true;
}

void Button::unpick() {
	mFlagPickable = false;
}

void Button::onPicked() {

}

void Button::onUnpicked() {

}

} /* namespace framework */
} /* namespace fillwave */
