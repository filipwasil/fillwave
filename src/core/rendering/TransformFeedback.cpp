/*
 * TransformFeedback.cpp
 *
 *  Created on: May 30, 2014
 *      Author: filip
 */

#include <fillwave/core/rendering/TransformFeedback.h>
#include <fillwave/extras/Log.h>

FLOGINIT("TransformFeedback", FERROR | FFATAL)

namespace fillwave {
namespace core {

TransformFeedback::TransformFeedback(GLsizei howMany)
		: GLObject(howMany), mTarget(GL_TRANSFORM_FEEDBACK) {
	glGenTransformFeedbacks(mHowMany, mHandles);
}

TransformFeedback::~TransformFeedback() {
	glDeleteTransformFeedbacks(mHowMany, mHandles);
}

void TransformFeedback::bind(GLuint id) const {
	glBindTransformFeedback(mTarget, mHandles[id]);
}

void TransformFeedback::begin(GLenum primitiveMode) {
	if (primitiveMode != GL_POINTS && primitiveMode != GL_LINES
			&& primitiveMode != GL_TRIANGLES
#ifndef __ANDROID__
			&& primitiveMode != GL_TRIANGLES_ADJACENCY
			&& primitiveMode != GL_TRIANGLE_STRIP_ADJACENCY
			&& primitiveMode != GL_LINES_ADJACENCY
			&& primitiveMode != GL_LINE_STRIP_ADJACENCY
#endif
	)
		FLOG_ERROR("not valid primitive type");
	else
		glBeginTransformFeedback(primitiveMode);
}

void TransformFeedback::end() {
	glEndTransformFeedback();
}

void TransformFeedback::pause() {
	glPauseTransformFeedback();
}

void TransformFeedback::resume() {
	glResumeTransformFeedback();
}

} /* core */
} /* fillwave */
