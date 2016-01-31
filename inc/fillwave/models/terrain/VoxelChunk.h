/*
 * VoxelChunk.h
 *
 *  Created on: Dec 1, 2014
 *      Author: Filip Wasil
 */

#ifndef VOXELCHUNK_H_
#define VOXELCHUNK_H_

#include <fillwave/models/terrain/Voxel.h>
#include <fillwave/models/terrain/VoxelConstructor.h>
#include <fillwave/core/buffers/VertexBufferBasic.h>
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

	/* IDrawable */
	void draw(ICamera& camera) override;
	void drawPBRP(ICamera& camera) override;

	/* IRenderable */
   void updateRenderer(IRenderer& renderer) override;
   bool getRenderItem(RenderItem& item) override;

	GLint getSize();

protected:
	const GLfloat mVoxelGap;

private:
	GLint mSize;
	Voxel*** mVoxels;
	pProgram mProgram;
	pTexture2D mTexture;
	pVertexBufferBasic mVBO;
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
