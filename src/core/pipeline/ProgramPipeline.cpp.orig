/*
 * ProgramPipeline.cpp
 *
 *  Created on: May 30, 2014
 *      Author: filip
 */

#include <fillwave/core/pipeline/ProgramPipeline.h>
#include <fillwave/Log.h>

#ifdef FILLWAVE_GLES_3_0
#else

namespace fillwave {
namespace core {

ProgramPipeline::ProgramPipeline(GLbitfield stage, GLsizei howMany) :
		GLObject(howMany), mStage(stage), mTarget(GL_TRANSFORM_FEEDBACK) {
	glGenProgramPipelines(mHowMany, mHandles);
}

ProgramPipeline::~ProgramPipeline() {
	glDeleteProgramPipelines(mHowMany, mHandles);
}

void ProgramPipeline::bind(GLuint id) const {
	glBindProgramPipeline(mHandles[id]);
}

void ProgramPipeline::use(GLuint programHandle, GLuint id) const {
	glUseProgramStages(mHandles[id], mStage, programHandle);
}

} /* core */
} /* fillwave  */

#endif /* FILLWAVE_GLES_3_0 */
