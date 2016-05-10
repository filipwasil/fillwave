/*
 * VertexBufferPosition.h
 *
 *  Created on: Dec 7, 2014
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

#ifndef VertexBufferPosition_H_
#define VertexBufferPosition_H_

#include <fillwave/core/buffers/TVertexBuffer.h>

namespace fillwave {
namespace core {

/*! \struct VertexPosition
 * \brief Not used. Stores the position vertex data.
 */

struct VertexPosition {
	GLfloat mPosition[4];
};

/*! \class VertexBufferPosition
 * \brief Not used. Vertex buffer specialized with VertexPosition data structure.
 */

class VertexBufferPosition: public TVertexBuffer<VertexPosition> {
 public:
	VertexBufferPosition(
	   framework::Shape<VertexPosition>& shape,
	   GLuint dataStoreModification = GL_STATIC_DRAW);
	VertexBufferPosition(
	   const std::vector<VertexPosition>& vertices,
	   GLuint dataStoreModification = GL_STATIC_DRAW);
	virtual ~VertexBufferPosition() = default;
	void log() const;
};

} /* core */
} /* fillwave*/

#endif /* VertexBufferPosition_H_ */
