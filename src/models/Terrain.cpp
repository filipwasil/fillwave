/*
 * Terrain.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: filip
 */

#include <fillwave/models/Terrain.h>
#include <fillwave/Fillwave.h>
#include <fillwave/management/LightSystem.h>
#include <fillwave/Log.h>

FLOGINIT("Terrain", FERROR | FFATAL)

namespace fillwave {
namespace framework {

Terrain::Terrain(Engine* engine, core::Program* program, GLint radius,
                 GLfloat gap) :
	mProgram(program),
	mLights(engine->getLightSystem()),
	mRadius(radius),
	mGap(gap) {

}

void Terrain::draw(ICamera& camera) {
	distanceCheck(camera);
	for (auto& it : mVoxelChunks) {
		it->draw(camera);
	}
}

void Terrain::drawPBRP(ICamera& camera) {
	distanceCheck(camera);
	mLights->pushLightUniforms(mProgram);
	mLights->bindShadowmaps();
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

void Terrain::updateRenderer(IRenderer& renderer) {
	renderer.update(this);
}

bool Terrain::getRenderItem(RenderItem& item) {
	item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
	item.mRenderStatus = 0x02; // vao, ibo, diff, norm, spec, blend, cont, anima
	return true;
}

} /* models */
puTerrain buildTerrainVoxel(
   Engine* engine,
   core::Program* program,
   const std::string& texturePath,
   framework::VoxelConstructor* constructor,
   GLint radius) {

	GLfloat voxelGap = 0.2;

	puTerrain terrain = std::make_unique < framework::Terrain
	                    > (engine, program, radius, voxelGap);

	for (GLint i = 0; i <= radius; i++) {
		for (GLint x = 0; x < 1 + 2 * i; x++) {
			for (GLint z = 0; z < 1 + 2 * i; z++) {
				pVoxelChunk chunk = pVoxelChunk(
				                       new framework::VoxelChunk(program, engine, texturePath,
				                             FILLWAVE_VOXEL_CHUNK_SIZE, constructor, voxelGap));
				chunk->moveTo(
				   glm::vec3(
				      FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * x
				      - FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * (radius), 0.0,
				      FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * z
				      - FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * (radius)));
				terrain->addChunk(chunk);
			}
		}
	}
	return terrain;
}
} /* fillwave */
