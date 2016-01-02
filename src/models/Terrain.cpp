/*
 * Terrain.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: filip
 */

#include <fillwave/models/Terrain.h>
#include <fillwave/Fillwave.h>

FLOGINIT("Terrain", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Terrain::Terrain(GLint radius, GLfloat gap)
		: mRadius(radius), mGap(gap) {
}

void Terrain::draw(ICamera& camera) {
	distanceCheck(camera);
	for (auto& it : mVoxelChunks) {
		it->draw(camera);
	}
}

void Terrain::drawPBRP(ICamera& camera) {
	distanceCheck(camera);
	for (auto& it : mVoxelChunks) {
		it->drawPBRP(camera);
	}
}

inline void Terrain::distanceCheck(ICamera& camera) {
	/* check if there are any children too far away from the camera */
	glm::vec3 distanceToCamera;
	GLfloat direction = 0.0f;

	GLint cenralChunkIndex = ((mRadius * 2 + 1) * (mRadius * 2 + 1) - 1) / 2;
	distanceToCamera = camera.getTranslation()
			- glm::vec3(mVoxelChunks[cenralChunkIndex]->getTranslation());

	GLfloat singleChunkWidth = FILLWAVE_VOXEL_CHUNK_SIZE * mGap * mRadius;
	GLfloat maximumDistance = singleChunkWidth * 0.5f;

	if (glm::abs(distanceToCamera.x) > maximumDistance) { //OK
		if (distanceToCamera.x > 0.0f) {
			direction = 1.0;
		} else {
			direction = -1.0;
		}
		for (auto& it : mVoxelChunks) {
			it->moveBy(glm::vec3(direction * singleChunkWidth, 0.0, 0.0)); //OK
		}
	}

	if (glm::abs(distanceToCamera.z) > maximumDistance) { //OK
		if (distanceToCamera.z > 0.0f) {
			direction = 1.0;
		} else {
			direction = -1.0;
		}
		for (auto& it : mVoxelChunks) {
			it->moveBy(glm::vec3(0.0, 0.0, direction * singleChunkWidth)); //OK
		}
	}
}

void Terrain::addChunk(pVoxelChunk chunk) {
	mVoxelChunks.push_back(chunk);
}

} /* models */
} /* fillwave */
