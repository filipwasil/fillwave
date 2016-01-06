/*
 * MeshTerrain.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: filip
 */

#include <fillwave/models/MeshTerrain.h>
#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/management/LightManager.h>

FLOGINIT("MeshTerrain", FERROR | FFATAL)

namespace fillwave {
namespace framework {

MeshTerrain::MeshTerrain(
		Engine* engine,
		pProgram program,
		TerrainConstructor* constructor,
		const Material& /*material*/, //xxx to be used
		const std::string& diffuseMapPath,
		const std::string& normalMapPath,
		const std::string& specularMapPath,
		GLuint radius,
		GLuint density)
		:
				Programmable(program),
				mLightManager(engine->getLightManager()),
				mChunkWidth(radius * 0.2 * 16 / density),
				mJumpStep(density * 0.2 * 16 / density) {

	Material _material;

	pTexture diffuseMap = engine->storeTexture(diffuseMapPath.c_str(),
			aiTextureType_DIFFUSE);

	pTexture normalMap = engine->storeTexture(normalMapPath.c_str(),
			aiTextureType_NORMALS);

	pTexture specularMap = engine->storeTexture(specularMapPath.c_str(),
			aiTextureType_SPECULAR);

	int pointsWidth, pointsWidthNext, offset;

	std::vector<GLuint> indices;

	indices.reserve(density * density);

	for (GLuint z = 0; z < density; z++) {
		for (GLuint x = 0; x < density; x++) {
			pointsWidth = density + 1;
			pointsWidthNext = density + 2;
			offset = x + z * pointsWidth;
			indices.push_back(0 + offset);
			indices.push_back(pointsWidth + offset);
			indices.push_back(pointsWidthNext + offset);
			indices.push_back(1 + offset);
			indices.push_back(0 + offset);
			indices.push_back(pointsWidthNext + offset);
		}
	}

	GLfloat gapSize = 0.2 * 16 / density;
	GLint indexTerrainChunk = radius;

	ProgramLoader loader(engine);

	for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; x++) {
		for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; z++) {
			pMesh ptr = pMesh(
					new Mesh(engine, _material,
							buildTextureRegion(diffuseMap),
							buildTextureRegion(normalMap),
							buildTextureRegion(specularMap), program,
							loader.getShadow(),
							loader.getShadowColorCoded(),
							loader.getOcclusionOptimizedQuery(),
							loader.getAmbientOcclusionGeometry(),
							loader.getAmbientOcclusionColor(),
							engine->getLightManager(),
							pVertexBufferBasic(
									new core::VertexBufferBasic(constructor, density,
											gapSize, indices)),
							pIndexBufferBasic(new core::IndexBufferBasic(indices))));

			ptr->moveTo(
					glm::vec3(density * gapSize * (GLfloat(x)), 0.0,
							density * gapSize * (GLfloat(z))));
			attach(ptr);
		}
	}
}

void MeshTerrain::draw(ICamera& camera) {
	distanceCheck(camera);
	drawWithEffects(camera);
}

void MeshTerrain::drawPBRP(ICamera& camera) {
	distanceCheck(camera);
	mLightManager->pushLightUniforms(mProgram.get());
	mLightManager->bindShadowmaps();
	for (auto& it : mChildren) {
		it->drawPBRP(camera);
	}
}

void MeshTerrain::updateRenderer(IRenderer& renderer) {
	GLuint id = mProgram.get()->getHandle();
	renderer.update(&id, this);
}

inline void MeshTerrain::distanceCheck(ICamera& camera) {
	/* check if there are any children too far away from the camera */
	glm::vec3 distanceToCamera;
	GLfloat direction = 0.0f;

	distanceToCamera = camera.getTranslation() - getTranslation();

	GLfloat maximumDistance = mJumpStep * 2;
	GLfloat jumpStep = mJumpStep * 2;
	if (glm::abs(distanceToCamera.x) > maximumDistance) { //OK
		if (distanceToCamera.x > 0.0f) {
			direction = 1.0;
		} else {
			direction = -1.0;
		}
		moveBy(glm::vec3(direction * jumpStep, 0.0, 0.0));
	}

	if (glm::abs(distanceToCamera.z) > maximumDistance) { //OK
		if (distanceToCamera.z > 0.0f) {
			direction = 1.0;
		} else {
			direction = -1.0;
		}
		moveBy(glm::vec3(0.0, 0.0, direction * jumpStep));
	}
}

} /* framework */
} /* fillwave */
