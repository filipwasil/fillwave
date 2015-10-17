/*
 * TextureOnly.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: filip
 */

#include <fillwave/effects/TextureOnly.h>

namespace fillwave {
namespace effects {

void TextureOnly::preDrawAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", true);
}

void TextureOnly::postDrawAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", false);
}

void TextureOnly::stopAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", false);
}

void TextureOnly::startAction(core::Program* program) {
	program->uniformPush("uTextureOnlyEffect", true);
}

} /* effects*/
} /* fillwave */
