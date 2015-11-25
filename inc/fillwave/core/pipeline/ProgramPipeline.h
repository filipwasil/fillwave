/*
 * ProgramPipeline.h
 *
 *  Created on: May 30, 2014
 *      Author: Filip Wasil
 */

#ifndef PROGRAMPIPELINE_H_
#define PROGRAMPIPELINE_H_

#include <fillwave/core/GLObject.h>

#ifdef FILLWAVE_GLES_3_0
#else

namespace fillwave {
namespace core {

/*! \class ProgramPipeline
 * \brief Not used.
 *
 */

class ProgramPipeline: public GLObject {
public:
	ProgramPipeline(GLbitfield stage, GLsizei howMany = 1);
	virtual ~ProgramPipeline();
	void bind(GLuint id = 0) const;
	void use(GLuint programHandle, GLuint id = 0) const;

private:
	GLbitfield mStage;
	GLuint mTarget;
};

} /* core */
} /* fillwave */

#endif /* PROGRAMPIPELINE_H_ */

#endif /* FILLWAVE_GLES_3_0 */
