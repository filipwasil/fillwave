/*
 * VoxelChunk.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * fillwave@gmail.com
 *
 */

#include <fillwave/terrain/VoxelChunk.h>

#include <fillwave/Fillwave.h>

FLOGINIT("VoxelChunk", FERROR | FFATAL)

namespace fillwave {
namespace terrain {

const GLfloat voxelPositions[] = {
		0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		0.100000,
		0.100000,
		0.100000,
		0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		0.100000,
		-0.100000,
		0.100000,
		-0.100000,
		-0.100000,
		-0.100000,
		0.100000,
		-0.100000 };

const GLfloat voxelNormals[] = { 0.0, -1.0, 0.0, //-y
		0.0,
		-1.0,
		0.0,
		0.0,
		-1.0,
		0.0,
		0.0,
		1.0,
		0.0, //+y
		0.0,
		1.0,
		0.0,
		0.0,
		1.0,
		0.0,
		1.0,
		0.0,
		0.0, //+x
		1.0,
		0.0,
		0.0,
		1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0, //+z
		0.0,
		0.0,
		1.0,
		0.0,
		0.0,
		1.0,
		-1.0,
		0.0,
		0.0, //-x
		-1.0,
		0.0,
		0.0,
		-1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		-1.0, //-z
		0.0,
		0.0,
		-1.0,
		0.0,
		0.0,
		-1.0,
		0.0,
		-1.0,
		0.0, //-y
		0.0,
		-1.0,
		0.0,
		0.0,
		-1.0,
		0.0,
		0.0,
		1.0,
		0.0, //+y
		0.0,
		1.0,
		0.0,
		0.0,
		1.0,
		0.0,
		1.0,
		0.0,
		0.0, //+x
		1.0,
		0.0,
		0.0,
		1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		1.0, //+z
		0.0,
		0.0,
		1.0,
		0.0,
		0.0,
		1.0,
		-1.0,
		0.0,
		0.0, //-x
		-1.0,
		0.0,
		0.0,
		-1.0,
		0.0,
		0.0,
		0.0,
		0.0,
		-1.0, //-z
		0.0,
		0.0,
		-1.0,
		0.0,
		0.0,
		-1.0 };

const GLfloat voxelUV[] = {
		0.333333,
		0.666667,
		0.333333,
		1.000000,
		0.000000,
		1.000000,
		0.666667,
		0.666667,

		0.333333,
		0.666667,
		0.333333,
		0.333333,
		0.666667,
		0.333333,
		0.333333,
		0.333333,

		0.333333,
		0.000000,
		0.000000,
		0.333333,
		0.000000,
		0.000000,
		0.333333,
		0.000000,

		0.666667,
		0.333333,
		0.666667,
		0.000000,
		1.000000,
		0.000000,
		0.333333,
		0.333333,

		0.333333,
		0.666667,
		0.000000,
		0.666667,
		0.000000,
		0.666667,
		0.333333,
		0.666667,

		0.000000,
		1.000000,
		0.666667,
		0.333333,
		0.666667,
		0.666667,
		0.333333,
		0.333333,

		0.666667,
		0.000000,
		0.666667,
		0.333333,
		0.333333,
		0.000000,
		0.333333,
		0.333333,

		0.000000,
		0.333333,
		0.333333,
		0.000000,
		1.000000,
		0.333333,
		0.666667,
		0.333333,

		1.000000,
		0.000000,
		0.000000,
		0.333333,
		0.333333,
		0.333333,
		0.000000,
		0.666667 };

VoxelChunk::VoxelChunk(
		pProgram program,
		Engine* engine,
		const std::string& texturePath,
		GLint size,
		VoxelConstructor* constructor,
		GLfloat gap)
		:
				Reloadable(engine),
				mVoxelGap(gap),
				mSize(size),
				mProgram(program),
				mTexture(
						engine->storeTexture(texturePath.c_str(),
								aiTextureType_DIFFUSE)),
				mLightManager(engine->getLightManager()) {

	mVoxels = new Voxel**[mSize];
	std::vector<core::VertexBasic> vertices;
	vertices.reserve(mSize * mSize * mSize * 36);
	for (GLint x = 0; x < mSize; x++) {
		mVoxels[x] = new Voxel*[mSize];
		for (GLint z = 0; z < mSize; z++) {
			mVoxels[x][z] = new Voxel[mSize];
			for (GLint y = 0; y < mSize; y++) {
				GLboolean active =
						constructor ?
								constructor->calculateActiveVoxel(
										(GLfloat) x / (GLfloat) ((mSize - 1)),
										(GLfloat) z / (GLfloat) ((mSize - 1)),
										(GLfloat) y / (GLfloat) ((mSize - 1))) :
								GL_TRUE;
				mVoxels[x][z][y].setActive(active);
				if (mVoxels[x][z][y].isActive()) {
					core::VertexBasic v;
					for (GLint i = 0; i < 36; i++) {
						v.mPosition[0] = voxelPositions[3 * i]
								+ mVoxelGap * (GLfloat) x
								- (GLfloat) mVoxelGap * (mSize - 1) / 2.0f;
						v.mPosition[1] = voxelPositions[3 * i + 1]
								+ mVoxelGap * (GLfloat) y
								- (GLfloat) mVoxelGap * (mSize - 1) / 2.0f;
						v.mPosition[2] = voxelPositions[3 * i + 2]
								+ mVoxelGap * (GLfloat) z
								- (GLfloat) mVoxelGap * (mSize - 1) / 2.0f;
						v.mPosition[3] = 1.0;
						v.mNormal[0] = voxelNormals[3 * i];
						v.mNormal[1] = voxelNormals[3 * i + 1];
						v.mNormal[2] = voxelNormals[3 * i + 2];
						v.mTextureUV[0] = voxelUV[2 * i];
						v.mTextureUV[1] = voxelUV[2 * i + 1];
						vertices.push_back(v);
					}
				}
			}
		}
	}
	mVBO = pVertexBufferBasic(new core::VertexBufferBasic(vertices));

	initPipeline();
	initVBO();
	initVAO();
	initUniformsCache();
}

VoxelChunk::~VoxelChunk() {
	for (GLint x = 0; x < mSize; x++) {
		for (GLint z = 0; z < mSize; z++) {
			delete[] mVoxels[x][z];
		}
		delete[] mVoxels[x];
	}
	delete[] mVoxels;
}

void VoxelChunk::setType(GLint type) {
	for (GLint x = 0; x < mSize; x++) {
		for (GLint z = 0; z < mSize; z++) {
			for (GLint y = 0; z < mSize; y++) {
				mVoxels[x][z][y].setType(type);
			}
		}
	}
}

void VoxelChunk::reloadVBO() {

	std::vector<core::VertexBasic> vertices;
	for (GLint x = 0; x < mSize; x++) {
		mVoxels[x] = new Voxel*[mSize];
		for (GLint z = 0; z < mSize; z++) {
			mVoxels[x][z] = new Voxel[mSize];
			for (GLint y = 0; y < mSize; y++) {
				if (mVoxels[x][z][y].isActive()) {
					core::VertexBasic v;
					for (GLint i = 0; i < 36; i++) {
						v.mPosition[0] = voxelPositions[3 * i]
								+ mVoxelGap * (GLfloat) x
								- (GLfloat) (mSize - 1) / 2.0f;
						v.mPosition[1] = voxelPositions[3 * i + 1]
								+ mVoxelGap * (GLfloat) y
								- (GLfloat) (mSize - 1) / 2.0f;
						v.mPosition[2] = voxelPositions[3 * i + 2]
								+ mVoxelGap * (GLfloat) z
								- (GLfloat) (mSize - 1) / 2.0f;
						v.mPosition[3] = 1.0;
						v.mNormal[0] = voxelNormals[3 * i];
						v.mNormal[1] = voxelNormals[3 * i + 1];
						v.mNormal[2] = voxelNormals[3 * i + 2];
						v.mTextureUV[0] = voxelUV[2 * i];
						v.mTextureUV[1] = voxelUV[2 * i + 1];
						vertices.push_back(v);
					}
				}
			}
		}
	}

	mVBO = pVertexBufferBasic(new core::VertexBufferBasic(vertices)); //xxx todo needs to be in manager

	initVBO();

	initVAO();
}

void VoxelChunk::reloadVoxels(VoxelConstructor* constructor) {
	std::vector<core::VertexBasic> vertices;
	vertices.reserve(mSize * mSize * mSize);
	for (GLint x = 0; x < mSize; x++) {
		for (GLint z = 0; z < mSize; z++) {
			for (GLint y = 0; y < mSize; y++) {
				mVoxels[x][z][y].setActive(
						constructor->calculateActiveVoxel(
								(GLfloat) x / (GLfloat) mSize,
								(GLfloat) z / (GLfloat) mSize,
								(GLfloat) y / (GLfloat) mSize));
			}
		}
	}
	reloadVBO();
}

void VoxelChunk::draw(space::Camera& camera) {
	/* Parent-children transformations */
	updateMatrixTree();

	mProgram->use();

	core::Uniform::push(mUniformLocationCacheModelMatrix, mTransformation);
	core::Uniform::push(mUniformLocationCacheCameraPosition,
			camera.getTranslation());
	core::Uniform::push(mUniformLocationCacheViewProjectionMatrix,
			camera.getViewProjection());

	mLightManager->pushLightUniforms(camera, mProgram.get());

	mLightManager->bindShadowmaps();

	mVAO->bind();

	coreDraw();

	mVAO->unbind();

	core::Program::disusePrograms();
}

GLint VoxelChunk::getSize() {
	return mSize;
}

inline void VoxelChunk::coreDraw() {
	if (mTexture) {
		mTexture->bind();
	}

	onDraw();

	core::Texture2D::unbind2DTextures();
}

inline void VoxelChunk::onDraw() {
	glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
	FLOG_CHECK("Could not draw");
}

inline void VoxelChunk::initBuffers() {
	if (mVBO) {
		mVBO->reload();
	}
}

inline void VoxelChunk::initPipeline() {

}

inline void VoxelChunk::initUniformsCache() {
	mUniformLocationCacheModelMatrix = mProgram->getUniformLocation(
			"uModelMatrix");
	mUniformLocationCacheCameraPosition = mProgram->getUniformLocation(
			"uCameraPosition");
	mUniformLocationCacheViewProjectionMatrix = mProgram->getUniformLocation(
			"uViewProjectionMatrix");
}

inline void VoxelChunk::initVAO() {
	mSampler->bind();
	mVAO->bind();

	mVBO->bind();
	mVBO->attributesSetForVAO();
	mVBO->setReady();
	mVBO->send();

	mVAO->unbind();
}

inline void VoxelChunk::initVBO() {
	mVBO->getAttributes(mProgram->getHandle());
	mVBO->attributesBind(mProgram);
}

} /* models */
} /* fillwave*/
