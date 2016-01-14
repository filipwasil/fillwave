/*
 * ProgressBar.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#include <fillwave/hud/ProgressBar.h>
#include <fillwave/Fillwave.h>

namespace fillwave {
namespace framework {

ProgressBar::ProgressBar(
		Engine* engine,
		const std::string& shaderPath,
		glm::vec2 position,
		glm::vec2 scale)
		:
				IHUDNode(engine->storeTextureRenderable(),
						ProgramLoader(engine).getHUDCustomFragmentShader(shaderPath),
						position, scale),
				mProgress(0.0) {

}

void ProgressBar::draw() {
	mProgram->use();
	mProgram->uniformPush("uTextureUnit",
	FILLWAVE_DIFFUSE_UNIT);
   mProgram->uniformPush("uProgress", mProgress);
   mProgram->uniformPush("uPosition", mPosition);
   mProgram->uniformPush("uScale", mScale);
	mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	mTexture->unbind();
}

} /* namespace framework */
} /* namespace fillwave */
