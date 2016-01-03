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
	Terrain(pProgram program, GLint radius, GLfloat gap);

	virtual ~Terrain() = default;

	void addChunk(pVoxelChunk chunk);

	void draw(ICamera& camera);
	void drawPBRP(ICamera& camera);

	void distanceCheck(ICamera& camera);
   void updateRenderpass(std::map<GLuint, std::vector<Entity*> >& renderpasses);

private:
   pProgram mProgram;
	GLint mRadius;
	GLfloat mGap;
	std::vector<pVoxelChunk> mVoxelChunks;
};

} /* framework */
typedef std::shared_ptr<framework::Terrain> pTerrain;

static pTerrain buildTerrainVoxel(
		Engine* engine,
		pProgram program,
		const std::string& texturePath,
		framework::VoxelConstructor* constructor,
		GLint radius = 0) {

	GLfloat voxelGap = 0.2;

	pTerrain terrain = pTerrain(new framework::Terrain(program, radius, voxelGap));

	for (GLint i = 0; i <= radius; i++) {
		for (GLint x = 0; x < 1 + 2 * i; x++) {
			for (GLint z = 0; z < 1 + 2 * i; z++) {
				pVoxelChunk chunk = pVoxelChunk(
						new framework::VoxelChunk(program, engine, texturePath,
						FILLWAVE_VOXEL_CHUNK_SIZE, constructor, voxelGap));
				chunk->moveTo(
						glm::vec3(
								FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * x
										- FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * (radius),
								0.0,
								FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * z
										- FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap
												* (radius)));
				terrain->addChunk(chunk);
			}
		}
	}
	return terrain;

}

} /* fillwave*/

#endif /* TERRAIN_H_ */
