/*
 * VertexBufferBasic.cpp
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

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
#include <fillwave/models/animations/Animator.h>
#include <fillwave/Assets.h>
#endif

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/Log.h>

FLOGINIT("VertexBufferBasic", FERROR | FFATAL)

namespace fillwave {
namespace core {

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
VertexBufferBasic::VertexBufferBasic(
   const aiMesh* shape,
   framework::Animator* animator,
   GLuint dataStoreModification) :
	TVertexBuffer<VertexBasic>(dataStoreModification) {

	mTotalElements = shape->mNumVertices;

	mDataVertices.resize(mTotalElements);

	int threadID, numberOfThreads, chunkSize = 64;
	(void) threadID;
	(void) numberOfThreads;
	(void) chunkSize;
	{
		#pragma omp parallel for schedule(guided) num_threads(2) if (mTotalElements > 1000)
		for (GLuint i = 0; i < mTotalElements; i++) {
			VertexBasic& vertex = mDataVertices[i];

			if (shape->HasVertexColors(0)) {
				vertex.mColor[0] = shape->mColors[0]->r;
				vertex.mColor[1] = shape->mColors[0]->g;
				vertex.mColor[2] = shape->mColors[0]->b;
				vertex.mColor[3] = shape->mColors[0]->a;
				abort();
			} else {
				vertex.mColor[0] = 0.0f;
				vertex.mColor[1] = 0.0f;
				vertex.mColor[2] = 0.0f;
				vertex.mColor[3] = 1.0f;
			}

			vertex.mPosition[0] = shape->mVertices[i].x;
			vertex.mPosition[1] = shape->mVertices[i].y;
			vertex.mPosition[2] = shape->mVertices[i].z;
			vertex.mPosition[3] = 1.0f;

			/* One normal each triangle - on */
			if (shape->HasNormals()) {
				vertex.mNormal[0] = shape->mNormals[i].x;
				vertex.mNormal[1] = shape->mNormals[i].y;
				vertex.mNormal[2] = shape->mNormals[i].z;
			} else {
				vertex.mNormal[0] = 0;
				vertex.mNormal[1] = 0;
				vertex.mNormal[2] = 0;
			}

			if (shape->HasTextureCoords(0)) { //xxx what is this ?
				vertex.mTextureUV[0] = shape->mTextureCoords[0][i].x;
				vertex.mTextureUV[1] = shape->mTextureCoords[0][i].y;
			} else {
				vertex.mTextureUV[0] = 0;
				vertex.mTextureUV[1] = 0;
			}

			if (shape->HasTangentsAndBitangents()) {
				vertex.mNormalTangentMap[0] = shape->mTangents[i].x;
				vertex.mNormalTangentMap[1] = shape->mTangents[i].y;
				vertex.mNormalTangentMap[2] = shape->mTangents[i].z;
			} else {
				vertex.mNormalTangentMap[0] = 0;
				vertex.mNormalTangentMap[1] = 0;
				vertex.mNormalTangentMap[2] = 0;
			}
			for (int k = 0; k < FILLWAVE_MAX_BONES_DEPENDENCIES; k++) {
				vertex.mBoneID[k] = 0.0f;
				vertex.mBoneWeight[k] = 0.0f;
			}
		}
	}

	mData = mDataVertices.data();
	mSize = mTotalElements * sizeof(VertexBasic);

	if (animator) {
		std::vector<int> boneIdForEachVertex;
		boneIdForEachVertex.reserve(mDataVertices.size());
		for (size_t z = 0; z < mDataVertices.size(); z++) {
			boneIdForEachVertex[z] = 0;
		}
		/* Bones */
		for (GLuint i = 0; i < shape->mNumBones; i++) {
			for (GLuint j = 0; j < shape->mBones[i]->mNumWeights; j++) {
				GLuint VertexID = shape->mBones[i]->mWeights[j].mVertexId;
				float Weight = shape->mBones[i]->mWeights[j].mWeight;
				if (boneIdForEachVertex[VertexID] < FILLWAVE_MAX_BONES_DEPENDENCIES) {
					mDataVertices[VertexID].mBoneID[boneIdForEachVertex[VertexID]] =
					   animator->getId(shape->mBones[i]->mName.C_Str());
					mDataVertices[VertexID].mBoneWeight[boneIdForEachVertex[VertexID]] =
					   Weight;
					boneIdForEachVertex[VertexID]++;
				} else {
					FLOG_FATAL("Crater can handle maximum %d bone dependencies.",
					           FILLWAVE_MAX_BONES_DEPENDENCIES);
				}
			}
		}
	}
}
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

VertexBufferBasic::VertexBufferBasic(
   framework::TerrainConstructor* constructor,
   GLint chunkDensity,
   GLfloat gapSize,
   const std::vector<GLuint>& indices,
   GLuint dataStoreModification) :
	TVertexBuffer<VertexBasic>(dataStoreModification) {

	core::VertexBasic vertex;

	for (float z = 0; z <= chunkDensity; z++) {
		for (float x = 0; x <= chunkDensity; x++) {

			vertex.mColor[0] = 0.0f;
			vertex.mColor[1] = 0.0f;
			vertex.mColor[2] = 0.0f;
			vertex.mColor[3] = 1.0f;

			vertex.mPosition[0] = gapSize * (x - chunkDensity / 2);
			vertex.mPosition[2] = gapSize * (z - chunkDensity / 2);

			vertex.mPosition[3] = 1.0;

			vertex.mTextureUV[0] = x / chunkDensity;
			vertex.mTextureUV[1] = z / chunkDensity;

			vertex.mPosition[1] = constructor->calculateHeight(
			                         vertex.mTextureUV[0], vertex.mTextureUV[1]); // calculate height 0.0f;

			mDataVertices.push_back(vertex);
		}
	}

	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;

	for (size_t i = 0; i < mDataVertices.size(); i++) {
		normals.push_back(glm::vec3(0.0));
		tangents.push_back(glm::vec3(0.0));
	}

	int j, z;

	for (size_t i = 0; i < indices.size(); i += 3) {

		/* Normals */

		j = i + 1;
		z = i + 2;

		glm::vec3 v0(mDataVertices[indices[i]].mPosition[0],
		             mDataVertices[indices[i]].mPosition[1],
		             mDataVertices[indices[i]].mPosition[2]);
		glm::vec3 v1(mDataVertices[indices[j]].mPosition[0],
		             mDataVertices[indices[j]].mPosition[1],
		             mDataVertices[indices[j]].mPosition[2]);
		glm::vec3 v2(mDataVertices[indices[z]].mPosition[0],
		             mDataVertices[indices[z]].mPosition[1],
		             mDataVertices[indices[z]].mPosition[2]);

		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

		normals[indices[i]] += normal;
		normals[indices[j]] += normal;
		normals[indices[z]] += normal;

		/* Tangents */
		glm::vec3 deltaPosition;
		if (v0 == v1) {
			deltaPosition = v2 - v0;
		} else {
			deltaPosition = v1 - v0;
		}

		glm::vec2 deltaUV1(
		   mDataVertices[indices[j]].mTextureUV[0]
		   - mDataVertices[indices[i]].mTextureUV[0],
		   mDataVertices[indices[j]].mTextureUV[1]
		   - mDataVertices[indices[i]].mTextureUV[1]);

		glm::vec3 tangent = deltaPosition / (deltaUV1.s != 0 ? deltaUV1.s :
		                                     1.0f); //xxx check if 0.0f  stackOverflow 17000255
		tangent = glm::normalize(tangent - glm::dot(normal, tangent) * normal);

		tangents[indices[i]] += tangent;
		tangents[indices[j]] += tangent;
		tangents[indices[z]] += tangent;
	}

	for (size_t i = 0; i < indices.size(); i++) {
		glm::vec3 vector3_n = glm::normalize(normals[indices[i]]);
		glm::vec3 vector3_t = glm::normalize(tangents[indices[i]]);
		mDataVertices[indices[i]].mNormal[0] = vector3_n.x;
		mDataVertices[indices[i]].mNormal[1] = vector3_n.y;
		mDataVertices[indices[i]].mNormal[2] = vector3_n.z;
		mDataVertices[indices[i]].mNormalTangentMap[0] = vector3_t.x;
		mDataVertices[indices[i]].mNormalTangentMap[1] = vector3_t.y;
		mDataVertices[indices[i]].mNormalTangentMap[2] = vector3_t.z;
	}

	mTotalElements = mDataVertices.size();
	mData = mDataVertices.data();
	mSize = mTotalElements * sizeof(VertexBasic);
}

VertexBufferBasic::VertexBufferBasic(
   const std::vector<core::VertexBasic>& vertices,
   GLuint dataStoreModification) :
	TVertexBuffer<VertexBasic>(vertices, dataStoreModification) {

}

glm::vec3 VertexBufferBasic::getOcclusionBoxSize() {
	glm::vec3 maximum(-10000.0, -10000.0, -10000.0);
	glm::vec3 minimum(10000.0, 10000.0, 10000.0);

	for (GLuint i = 0; i < mTotalElements; i++) {
		if (mDataVertices[i].mPosition[0] > maximum.x)
			maximum.x = mDataVertices[i].mPosition[0];
		if (mDataVertices[i].mPosition[1] > maximum.y)
			maximum.y = mDataVertices[i].mPosition[1];
		if (mDataVertices[i].mPosition[2] > maximum.z)
			maximum.z = mDataVertices[i].mPosition[2];
		if (mDataVertices[i].mPosition[0] < minimum.x)
			minimum.x = mDataVertices[i].mPosition[0];
		if (mDataVertices[i].mPosition[1] < minimum.y)
			minimum.y = mDataVertices[i].mPosition[1];
		if (mDataVertices[i].mPosition[2] < minimum.z)
			minimum.z = mDataVertices[i].mPosition[2];
	}

	glm::vec3 result = maximum - minimum;

	if (result.x > result.y) {
		if (result.x > result.z) {
			result = glm::vec3(result.x);
		} else {
			result = glm::vec3(result.z);
		}
	} else {
		if (result.y > result.z) {
			result = glm::vec3(result.y);
		} else {
			result = glm::vec3(result.z);
		}
	}
	return result * 0.5f;
}

void VertexBufferBasic::log() const {
	for (auto it : mDataVertices) {
		FLOG_INFO("Vertex UV: %f %f", static_cast<double>(it.mTextureUV[0]),
		          static_cast<double>(it.mTextureUV[1]));
		FLOG_INFO("Vertex normal: %f %f %f", static_cast<double>(it.mNormal[0]),
		          static_cast<double>(it.mNormal[1]),
		          static_cast<double>(it.mNormal[2]));
		FLOG_INFO("Vertex position: %f %f %f",
		          static_cast<double>(it.mPosition[0]),
		          static_cast<double>(it.mPosition[1]),
		          static_cast<double>(it.mPosition[2]));
	}
}

} /* core */
} /* fillwave */
