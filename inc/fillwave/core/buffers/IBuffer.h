/*
 * Buffer.h
 *
 * Created on: 1 Mar 2013
 * Author: Filip Wasil
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

#ifndef BUFFER_H_
#define BUFFER_H_

#include <fillwave/core/GLObject.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class IBuffer
 * \brief Base for all buffer types.
 */

class IBuffer: public GLObject {
 public:
	IBuffer(
	   GLuint target,
	   GLuint drawType = GL_STATIC_DRAW,
	   GLuint index = 0,
	   GLsizei howMany = 1);

	virtual ~IBuffer();

	void bind(GLuint id = 0) const;
	void bind(GLuint externalTarget, GLuint id) const;
	void bindBase(GLuint id = 0) const;
	void bindBase(GLuint externalTarget, GLuint id) const;
	void unbind();
	void unbindBase(GLuint externalTarget);

	void unmap() const;
	void send();

	void setTarget(GLuint target);
	void setDrawType(GLuint drawType);

	bool isLoaded();
	void setLoaded(GLboolean loaded);

	GLuint getElements() const;
	GLuint getSize() const;
	GLvoid* getData() const;

	void reload();

	GLvoid* mapRange(GLenum access, GLuint size = 0);

	/* Feature not available in OpenGL ES  < 3.1 */
#ifdef FILLWAVE_GLES_3_0
#else
	GLvoid* map(GLenum access) const;
#endif

 protected:
	GLboolean mLoaded;
	GLuint mTarget;
	GLuint mDataStoreType;
	GLuint mIndex;
	GLvoid* mData;
	GLuint mSize;
	GLuint mTotalElements;
	void setElements(GLuint elements);
	void setSize(GLuint size);
	virtual void emptyCPU() = 0;
	virtual void emptyGPU() = 0;
};

void unbindBuffer(GLuint target);
void bindBuffer(GLuint target, GLuint handle);

} /* core */
} /* fillwave */

#endif /* BUFFER_H_ */
