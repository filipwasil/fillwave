/*
 * VoxelChunk.h
 *
 *  Created on: Dec 1, 2014
 *      Author: Filip Wasil
 */

#ifndef VOXELCHUNK_H_
#define VOXELCHUNK_H_

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

#include <fillwave/terrain/Voxel.h>
#include <fillwave/terrain/VoxelConstructor.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/core/texturing/Texture.h>
#include <fillwave/management/LightManager.h>
#include <fillwave/models/Reloadable.h>

namespace fillwave {
class Engine;
namespace terrain {

/*! \class VoxelChunk
 * \brief Block of Voxel objects.
 */

class VoxelChunk: public models::Entity, public models::Reloadable {
public:
	VoxelChunk(
			pProgram program,
			Engine* engine,
			const std::string& texturePath,
			GLint size,
			VoxelConstructor* constructor = nullptr,
			GLfloat gap = 0.2);

	~VoxelChunk();

	void setType(GLint type);

	void reloadVBO();

	void reloadVoxels(VoxelConstructor* constructor);

	void draw(space::Camera& camera);

	GLint getSize();

protected:
	const GLfloat mVoxelGap;

private:
	GLint mSize;
	Voxel*** mVoxels;
	pTexture mTexture;
	pVertexBufferBasic mVBO;
	pProgram mProgram;
	manager::LightManager* mLightManager;

	GLint mUniformLocationCacheModelMatrix, mUniformLocationCacheCameraPosition,
			mUniformLocationCacheViewProjectionMatrix;

	void onDraw();

	void coreDraw();

	void initBuffers();

	void initPipeline();

	void initVBO();

	void initVAO();

	void initUniformsCache();
};

} /* models */
typedef std::shared_ptr<terrain::VoxelChunk> pVoxelChunk;
} /* fillwave*/

#endif /* VOXELCHUNK_H_ */
