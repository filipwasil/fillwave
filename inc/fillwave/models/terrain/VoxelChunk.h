/*
 * VoxelChunk.h
 *
 *  Created on: Dec 1, 2014
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

#ifndef VOXELCHUNK_H_
#define VOXELCHUNK_H_

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/models/terrain/Voxel.h>
#include <fillwave/models/terrain/VoxelConstructor.h>
#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/models/base/IReloadable.h>
#include <fillwave/models/Entity.h>

namespace fillwave {
class Engine;
namespace framework {
class LightSystem;

/*! \class VoxelChunk
 * \brief Block of Voxel objects.
 */

class VoxelChunk: public Entity, public IReloadable {
 public:
	VoxelChunk(
	   core::Program* program,
	   Engine* engine,
	   const std::string& texturePath,
	   GLint size,
	   VoxelConstructor* constructor = nullptr,
	   GLfloat gap = 0.2);

	~VoxelChunk();

	void setType(GLint type);

	void reloadVBO();
	void reloadVoxels(VoxelConstructor* constructor);

	/* IDrawable */
	void draw(ICamera& camera) override;
	void drawPBRP(ICamera& camera) override;

	/* IRenderable */
	void updateRenderer(IRenderer& renderer) override;
	bool getRenderItem(RenderItem& item) override;

	GLint getSize();

 protected:
	Engine* mEngine;
	const GLfloat mVoxelGap;

 private:
	GLint mSize;
	Voxel*** mVoxels;
	core::Program* mProgram;
	core::Texture2D* mTexture;
	core::VertexBufferBasic* mVBO;
	LightSystem* mLights;

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

} /* framework */
typedef std::shared_ptr<framework::VoxelChunk> pVoxelChunk;
} /* fillwave*/

#endif /* VOXELCHUNK_H_ */
