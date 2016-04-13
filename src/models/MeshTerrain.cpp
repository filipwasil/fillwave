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
#include <fillwave/management/LightSystem.h>

FLOGINIT("MeshTerrain", FERROR | FFATAL)

namespace fillwave {
namespace framework {

//xxx code duplication in constructors. fix
MeshTerrain::MeshTerrain(
   Engine* engine,
   core::Program* program,
   TerrainConstructor* constructor,
   const Material& /*material*/, //xxx to be used
   const std::string& diffuseMapPath,
   const std::string& normalMapPath,
   const std::string& specularMapPath,
   GLuint radius,
   GLuint density) :
	Programmable(program),
	mLights(engine->getLightSystem()),
	mChunkWidth(radius * 0.2 * 16 / density),
	mJumpStep(density * 0.2 * 16 / density) {

	std::vector<GLuint> indices;

	initIBO(indices, density);

	GLfloat gapSize = 0.2 * 16 / density;
	GLint indexTerrainChunk = radius;
	ProgramLoader loader(engine);

	core::VertexArray* vao = new core::VertexArray();
	core::VertexBufferBasic* vbo = engine->storeBuffer<core::VertexBufferBasic>(vao, constructor, density, gapSize, indices);
	core::IndexBufferBasic* ibo = engine->storeBuffer<core::IndexBufferBasic>(vao, indices);

	Material m;

	for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; x++) {
		for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; z++) {
			pMesh ptr =
			   std::make_shared < Mesh
			   > (engine, m,
			           engine->storeTexture(diffuseMapPath.c_str()),
			           engine->storeTexture(normalMapPath.c_str()),
			           engine->storeTexture(specularMapPath.c_str()),
			           program,
			           loader.getShadow(),
			      loader.getShadowColorCoded(), loader.getOcclusionOptimizedQuery(),
			      loader.getAmbientOcclusionGeometry(), loader.getAmbientOcclusionColor(),
			      engine->getLightSystem(),
			      vbo,
			      ibo, nullptr, GL_TRIANGLES, vao);

			ptr->moveTo(
			   glm::vec3(density * gapSize * (GLfloat(x)), 0.0,
			             density * gapSize * (GLfloat(z))));
			attach(ptr);
		}
	}
}

//xxx code duplication in constructors. fix
MeshTerrain::MeshTerrain(
   Engine* engine,
   core::Program* program,
   TerrainConstructor* constructor,
   const Material& /*material*/, //xxx to be used
   core::Texture2D* diffuseMap,
   core::Texture2D* normalMap,
   core::Texture2D* specularMap,
   GLuint radius,
   GLuint density) :
	Programmable(program),
	mLights(engine->getLightSystem()),
	mChunkWidth(radius * 0.2 * 16 / density),
	mJumpStep(density * 0.2 * 16 / density) {

	std::vector<GLuint> indices;

	initIBO(indices, density);

	GLfloat gapSize = 0.2 * 16 / density;
	GLint indexTerrainChunk = radius;
	ProgramLoader loader(engine);

    core::VertexArray* vao = new core::VertexArray();
    core::VertexBufferBasic* vbo = engine->storeBuffer<core::VertexBufferBasic>(vao, constructor, density, gapSize, indices);
    core::IndexBufferBasic* ibo = engine->storeBuffer<core::IndexBufferBasic>(vao, indices);

    Material m;

	for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; x++) {
		for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; z++) {
			pMesh ptr =
			   std::make_shared < Mesh
			   > (engine, m, diffuseMap,
			         normalMap, specularMap, program, loader.getShadow(),
			      loader.getShadowColorCoded(), loader.getOcclusionOptimizedQuery(),
			      loader.getAmbientOcclusionGeometry(), loader.getAmbientOcclusionColor(),
			      engine->getLightSystem(), vbo, ibo, nullptr, GL_TRIANGLES, vao);

			ptr->moveTo(
			   glm::vec3(density * gapSize * (GLfloat(x)), 0.0,
			             density * gapSize * (GLfloat(z))));
			attach(ptr);
		}
	}
}

void MeshTerrain::initIBO(std::vector<GLuint>& indices, GLuint density) {
	int pointsWidth, pointsWidthNext, offset;

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
}

void MeshTerrain::draw(ICamera& camera) {
	distanceCheck(camera);
	drawWithEffects(camera);
}

void MeshTerrain::drawPBRP(ICamera& camera) {
	distanceCheck(camera);
	mLights->pushLightUniforms(mProgram);
	mLights->bindShadowmaps();
	for (auto& it : mChildren) {
		it->drawPBRP(camera);
	}
}

void MeshTerrain::updateRenderer(IRenderer& renderer) {
	renderer.update(this);
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
