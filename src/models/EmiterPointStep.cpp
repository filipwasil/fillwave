/*
 * EmiterPointStep.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: filip
 */

#include <fillwave/models/EmiterPointStep.h>

#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

EmiterPointStep::EmiterPointStep(
		Engine* engine,
		GLint howMany,
		GLenum blendingSource,
		GLenum blendingDestination,
		pTexture texture)
		: EmiterPoint(engine, howMany, 100, //size
				1, //lifetime
				texture, glm::vec4(1.0, 1.0, 1.0, 0.0), // color
				blendingSource, blendingDestination,
				GL_FALSE, 1.0) {

}

} /* framework */
} /* fillwave */
