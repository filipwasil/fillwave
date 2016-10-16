/*
 * TransformFeedback.cpp
 *
 *  Created on: May 30, 2014
 *      Author: filip
 *
 * Copyright (c) 2016, Filip Wasil
 * All rights reserved.
 *
 * Fillwave C++14 graphics engine.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <fillwave/core/rendering/TransformFeedback.h>
#include <fillwave/Log.h>

FLOGINIT("TransformFeedback", FERROR | FFATAL)

namespace fillwave {
namespace core {

TransformFeedback::TransformFeedback(GLsizei howMany) :
	GLObject(howMany), mTarget(GL_TRANSFORM_FEEDBACK) {
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
#ifdef FILLWAVE_GLES_3_0
#else
	      && primitiveMode != GL_TRIANGLES_ADJACENCY
	      && primitiveMode != GL_TRIANGLE_STRIP_ADJACENCY
	      && primitiveMode != GL_LINES_ADJACENCY
	      && primitiveMode != GL_LINE_STRIP_ADJACENCY
#endif
	   ) {
		fLogE("not valid primitive type");
	} else {
		glBeginTransformFeedback(primitiveMode);
	}
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
