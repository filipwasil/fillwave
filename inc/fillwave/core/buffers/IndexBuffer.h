/*
 * IndexBuffer.h
 *
 *  Created on: 16 Apr 2015
 *      Author: Filip Wasil
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

#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include <fillwave/core/buffers/IBuffer.h>
#include <fillwave/Assets.h>

namespace fillwave {
namespace core {

/*! \class IndexBuffer
 * \brief IndexBufferObject - IBO.
 */

class IndexBuffer: public IBuffer {
 public:
	// xxx fill - fills buffer with sequential data
	IndexBuffer(GLuint elements, bool fill,
	            GLuint dataStoreModification = GL_STATIC_DRAW);
	IndexBuffer(const std::vector<GLuint>& data,
	            GLuint dataStoreModification  = GL_STATIC_DRAW);
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	IndexBuffer(const aiMesh* shape, GLuint dataStoreModification = GL_STATIC_DRAW);
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

	virtual ~IndexBuffer() = default;

	GLuint* getDataInternal();

	void emptyCPU() override;
	void emptyGPU() override;

 protected:
	std::vector<GLuint> mDataIndices;
};

} /* core */
} /* fillwave */
#endif /* INDEXBUFFER_H_ */
