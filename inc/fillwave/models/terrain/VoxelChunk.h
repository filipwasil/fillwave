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
#include <fillwave/core/texturing/Texture.h>
#include <fillwave/models/base/Reloadable.h>
#include <fillwave/models/Entity.h>

namespace fillwave {
class Engine;
namespace framework {
class LightManager;

/*! \class VoxelChunk
 * \brief Block of Voxel objects.
 */

class VoxelChunk: public Entity, public Reloadable {
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

	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);

   void updateRenderpass(std::unordered_map<GLuint, std::vector<Entity*> >& renderpasses);

	GLint getSize();

protected:
	const GLfloat mVoxelGap;

private:
	GLint mSize;
	Voxel*** mVoxels;
	pProgram mProgram;
	pTexture mTexture;
	pVertexBufferBasic mVBO;
	LightManager* mLightManager;

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
