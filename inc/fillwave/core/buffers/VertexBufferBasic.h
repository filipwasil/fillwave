/*
 * VertexBufferBasic.h
 *
 *  Created on: May 17, 2014
 *      Author: filip
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
