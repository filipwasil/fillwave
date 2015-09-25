/*
 * Terrain.h
 *
 *  Created on: Sep 23, 2014
 *      Author: Filip Wasil
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

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

#include <fillwave/terrain/VoxelChunk.h>

namespace fillwave {
class Engine;
namespace terrain {

#define FILLWAVE_VOXEL_CHUNK_SIZE 16
#define FILLWAVE_QUAD_CHUNK_SIZE 16

/*! \class Terrain
 * \brief Entity to provide terrain generation functionality.
 */

class Terrain: public models::Entity {
public:
	Terrain(GLint radius, GLfloat gap);

	virtual ~Terrain();

	void draw(space::Camera& camera);

	void addChunk(pVoxelChunk chunk);

private:
	GLint mRadius;
	GLfloat mGap;
	std::vector<pVoxelChunk> mVoxelChunks;

	void drawVoxels(space::Camera& camera);
};

} /* terrain */
typedef std::shared_ptr<terrain::Terrain> pTerrain;

static pTerrain buildTerrainVoxel(
		Engine* engine,
		pProgram program,
		const std::string& texturePath,
		terrain::VoxelConstructor* constructor,
		GLint radius = 0) {

	GLfloat voxelGap = 0.2;

	pTerrain terrain = pTerrain(new terrain::Terrain(radius, voxelGap));

	for (GLint i = 0; i <= radius; i++) {
		for (GLint x = 0; x < 1 + 2 * i; x++) {
			for (GLint z = 0; z < 1 + 2 * i; z++) {
				pVoxelChunk chunk = pVoxelChunk(
						new terrain::VoxelChunk(program, engine, texturePath,
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
