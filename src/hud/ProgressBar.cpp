/*
 * ProgressBar.cpp
 *
 *  Created on: Jan 11, 2016
 *      Author: filip
 */

#include <fillwave/hud/ProgressBar.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>

FLOGINIT_DEFAULT()

namespace fillwave {
namespace framework {

ProgressBar::ProgressBar(
   Engine* engine,
   core::Texture2D* texture,
   const std::string& shaderPath,
   glm::vec2 position,
   glm::vec2 scale)
	:
	IHUDNode(texture,
	        ProgramLoader(engine).getHUDCustomFragmentShader(shaderPath),
	        position, scale),
	mProgress(0.0) {

}

void ProgressBar::draw() {
	mProgram->use();
	mProgram->uniformPush("uProgress", mProgress);
	IHUDNode::draw();
}

void ProgressBar::setProgress(GLfloat progress) {
	mProgress = progress;
}

} /* namespace framework */
} /* namespace fillwave */
