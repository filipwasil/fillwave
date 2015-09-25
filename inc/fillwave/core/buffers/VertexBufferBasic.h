/*
 * VertexBufferBasic.h
 *
 *  Created on: May 17, 2014
 *      Author: filip
 */

#ifndef VERTEXBUFFERBASIC_H_
#define VERTEXBUFFERBASIC_H_

/*************************************************************************
 *
 * Copyright (C) 2015 Filip Wasil
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and may be covered by Polish and foreign patents, patents
 * in process, and are protected by trade secret or copyright
 * law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/core/buffers/VertexBuffer.h>
#include <fillwave/terrain/TerrainConstructor.h>
#include <fillwave/Assets.h>

namespace fillwave {

namespace manager {
class BoneManager;
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

class VertexBufferBasic: public VertexBuffer<VertexBasic> {
public:
	VertexBufferBasic(const fMesh* shape, manager::BoneManager* boneManager =
			nullptr, GLuint dataStoreModification = GL_STATIC_DRAW);

	VertexBufferBasic(
			terrain::TerrainConstructor* constructor,
			GLint chunkDensity,
			GLfloat gapSize,
			std::vector<GLuint>& indices,
			GLuint dataStoreModification = GL_STATIC_DRAW);

	VertexBufferBasic(
			std::vector<core::VertexBasic>& vertices,
			GLuint dataStoreModification = GL_STATIC_DRAW);

	~VertexBufferBasic();

	glm::vec3 getOcclusionBoxSize();

	void log();
};

} /* core */
typedef std::shared_ptr<core::VertexBufferBasic> pVertexBufferBasic;
} /* fillwave */

#endif /* VERTEXBUFFERBASIC_H_ */
