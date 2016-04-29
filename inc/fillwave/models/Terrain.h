/*
 * Terrain.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Filip Wasil
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <fillwave/models/terrain/VoxelChunk.h>

namespace fillwave {
class Engine;
namespace framework {

#define FILLWAVE_VOXEL_CHUNK_SIZE 16
#define FILLWAVE_QUAD_CHUNK_SIZE 16

/*! \class Terrain
 * \brief Entity to provide terrain generation functionality.
 */

class Terrain: public Entity {
 public:
	Terrain(Engine* engine, core::Program* program, GLint radius, GLfloat gap);
	virtual ~Terrain() = default;

	void addChunk(pVoxelChunk chunk);
	void distanceCheck(ICamera& camera);

	/* IDrawable */
	void draw(ICamera& camera) override;
	void drawPBRP(ICamera& camera) override;

	/* IRenderable */
	void updateRenderer(IRenderer& renderer) override;
	bool getRenderItem(RenderItem& item) override;

 protected:
	void updateRendererData();

 private:
	core::Program* mProgram;
	LightSystem* mLights;
	GLint mRadius;
	GLfloat mGap;
	std::vector<pVoxelChunk> mVoxelChunks;
};

} /* framework */
typedef std::unique_ptr<framework::Terrain> puTerrain;

puTerrain buildTerrainVoxel(
   Engine* engine,
   core::Program* program,
   const std::string& texturePath,
   framework::VoxelConstructor* constructor,
   GLint radius = 0);

} /* fillwave*/

#endif /* TERRAIN_H_ */
