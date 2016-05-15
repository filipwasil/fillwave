/*
 * VertexBufferBasic.h
 *
 *  Created on: May 17, 2014
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

#ifndef VERTEXBUFFERBASIC_H_
#define VERTEXBUFFERBASIC_H_

#include <fillwave/models/terrain/TerrainConstructor.h>
#include <fillwave/Assets.h>
#include <fillwave/core/buffers/TVertexBuffer.h>

namespace fillwave {

namespace framework {
class Animator;
}

namespace core {

/*! \struct VertexBasic
 * \brief Stores the basic vertex data.
 */

struct VertexBasic {
	GLfloat mPosition[4];
	GLfloat mColor[4];
	GLfloat mNormal[3];
	GLfloat mNormalTangentMap[3];
	GLfloat mTextureUV[2];
	GLint mBoneID[FILLWAVE_MAX_BONES_DEPENDENCIES];
	GLfloat mBoneWeight[FILLWAVE_MAX_BONES_DEPENDENCIES];
};

/*! \struct FaceBasic
 * \brief Stores the face data for geometry built on Vertex Basic.
 */

struct FaceBasic {
	core::VertexBasic vertices[3];
};

/*! \class VertexBufferBasic
 * \brief Vertex buffer specialized with VertexBasic data structure.
 */

class VertexBufferBasic: public TVertexBuffer<VertexBasic> {
 public:
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
	VertexBufferBasic(const aiMesh* shape, framework::Animator* animator =
	                     nullptr, GLuint dataStoreModification = GL_STATIC_DRAW);
#else
	VertexBufferBasic(tinyobj::shape_t& shape, framework::Animator* animator =
	                     nullptr, GLuint dataStoreModification = GL_STATIC_DRAW);

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

	VertexBufferBasic(
	   framework::TerrainConstructor* constructor,
	   GLint chunkDensity,
	   GLfloat gapSize,
	   const std::vector<GLuint>& indices,
	   GLuint dataStoreModification = GL_STATIC_DRAW);

	VertexBufferBasic(
	   const std::vector<core::VertexBasic>& vertices,
	   GLuint dataStoreModification = GL_STATIC_DRAW);

	~VertexBufferBasic() = default;

	glm::vec3 getOcclusionBoxSize();

	void log() const;
};

} /* core */
} /* fillwave */

#endif /* VERTEXBUFFERBASIC_H_ */
