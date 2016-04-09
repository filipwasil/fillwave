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
	VertexBufferBasic(const fMesh* shape, framework::Animator* boneManager =
	                     nullptr, GLuint dataStoreModification = GL_STATIC_DRAW);

	VertexBufferBasic(
	   framework::TerrainConstructor* constructor,
	   GLint chunkDensity,
	   GLfloat gapSize,
	   std::vector<GLuint>& indices,
	   GLuint dataStoreModification = GL_STATIC_DRAW);

	VertexBufferBasic(
	   std::vector<core::VertexBasic>& vertices,
	   GLuint dataStoreModification = GL_STATIC_DRAW);

	~VertexBufferBasic() = default;

	glm::vec3 getOcclusionBoxSize();

	void log() const;
};

} /* core */
typedef std::shared_ptr<core::VertexBufferBasic> pVertexBufferBasic;
} /* fillwave */

#endif /* VERTEXBUFFERBASIC_H_ */
