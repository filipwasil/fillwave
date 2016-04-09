/*
 * PostProcessingPass.cpp
 *
 *  Created on: 4 mar 2015
 *      Author: filip
 */

#include <fillwave/core/operations/PostProcessingPass.h>

namespace fillwave {
namespace core {

PostProcessingPass::PostProcessingPass(
   core::Program* program,
   core::Texture2DRenderableDynamic* frame,
   GLfloat lifetime) :
	Finishable(lifetime), mFrame(frame), mProgram(program) {
}

core::Texture2DRenderableDynamic* PostProcessingPass::getFrame() const {
	return mFrame;
}

core::Program* PostProcessingPass::getProgram() const {
	return mProgram;
}

} /* core */
} /* fillwave */
