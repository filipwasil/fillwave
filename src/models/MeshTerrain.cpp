/*
 * MeshTerrain.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: filip
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


#include <fillwave/models/MeshTerrain.h>
#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/management/LightSystem.h>


namespace flw {
namespace flf {

//xxx code duplication in constructors. fix
MeshTerrain::MeshTerrain(Engine *engine,
    flc::Program *program,
    TerrainConstructor *constructor,
    const Material & /*material*/, //xxx to be used
    const std::string &diffuseMapPath,
    const std::string &normalMapPath,
    const std::string &specularMapPath,
    GLuint radius,
    GLuint density)
    : Programmable(program)
    , mLights(engine->getLightSystem())
    , mChunkWidth(radius * 0.2f * 16.0f / density)
    , mJumpStep(density * 0.2f * 16.0f / density) {

  std::vector<GLuint> indices;

  initIBO(indices, density);

  GLfloat gapSize = 0.2f * 16.0f / density;
  GLint indexTerrainChunk = radius;
  ProgramLoader loader(engine);

  flc::VertexArray *vao = new flc::VertexArray();
  flc::VertexBufferBasic *vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao,
                                                                              constructor,
                                                                              density,
                                                                              gapSize,
                                                                              indices);
  flc::IndexBuffer *ibo = engine->storeBuffer<flc::IndexBuffer>(vao, indices);

  Material m;

  for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; x++) {
    for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; z++) {
      puMesh ptr = std::make_unique<Mesh>(engine,
                                          m,
                                          engine->storeTexture(diffuseMapPath.c_str()),
                                          engine->storeTexture(normalMapPath.c_str()),
                                          engine->storeTexture(specularMapPath.c_str()),
                                          program,
                                          loader.getShadow(),
                                          loader.getShadowColorCoded(),
                                          loader.getOcclusionOptimizedQuery(),
                                          loader.getAmbientOcclusionGeometry(),
                                          loader.getAmbientOcclusionColor(),
                                          engine->getLightSystem(),
                                          vbo,
                                          ibo,
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
                                          nullptr,
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
                                          GL_TRIANGLES,
                                          vao);

      ptr->moveTo(glm::vec3(density * gapSize * (GLfloat(x)), 0.0, density * gapSize * (GLfloat(z))));

      attach(std::move(ptr));
    }
  }
}

//xxx code duplication in constructors. fix
MeshTerrain::MeshTerrain(Engine *engine,
    flc::Program *program,
    TerrainConstructor *constructor,
    const Material & /*material*/, //xxx to be used
    flc::Texture2D *diffuseMap,
    flc::Texture2D *normalMap,
    flc::Texture2D *specularMap,
    GLuint radius,
    GLuint density)
    : Programmable(program)
    , mLights(engine->getLightSystem())
    , mChunkWidth(radius * 0.2f * 16.0f / density)
    , mJumpStep(density * 0.2f * 16.0f / density) {

  std::vector<GLuint> indices;

  initIBO(indices, density);

  GLfloat gapSize = 0.2f * 16.0f / density;
  GLint indexTerrainChunk = radius;
  ProgramLoader loader(engine);

  flc::VertexArray *vao = new flc::VertexArray();
  flc::VertexBufferBasic *vbo = engine->storeBuffer<flc::VertexBufferBasic>(vao,
                                                                              constructor,
                                                                              density,
                                                                              gapSize,
                                                                              indices);
  flc::IndexBuffer *ibo = engine->storeBuffer<flc::IndexBuffer>(vao, indices);

  Material m;

  for (GLint x = -indexTerrainChunk; x <= indexTerrainChunk; x++) {
    for (GLint z = -indexTerrainChunk; z <= indexTerrainChunk; z++) {
      puMesh ptr = std::make_unique<Mesh>(engine,
                                          m,
                                          diffuseMap,
                                          normalMap,
                                          specularMap,
                                          program,
                                          loader.getShadow(),
                                          loader.getShadowColorCoded(),
                                          loader.getOcclusionOptimizedQuery(),
                                          loader.getAmbientOcclusionGeometry(),
                                          loader.getAmbientOcclusionColor(),
                                          engine->getLightSystem(),
                                          vbo,
                                          ibo,
#ifdef FILLWAVE_MODEL_LOADER_ASSIMP
                                          nullptr,
#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */
                                          GL_TRIANGLES,
                                          vao);

      ptr->moveTo(glm::vec3(density * gapSize * (GLfloat(x)), 0.0, density * gapSize * (GLfloat(z))));
      attach(std::move(ptr));
    }
  }
}

void MeshTerrain::initIBO(std::vector<GLuint> &indices, GLuint density) {
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

void MeshTerrain::draw(ICamera &camera) {
  distanceCheck(camera);
  drawWithEffects(camera);
}

void MeshTerrain::drawPBRP(ICamera &camera) {
  distanceCheck(camera);
  mLights->pushLightUniforms(mProgram);
  mLights->bindShadowmaps();
  for (auto &it : mChildren) {
    it->drawPBRP(camera);
  }
}

void MeshTerrain::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

inline void MeshTerrain::distanceCheck(ICamera &camera) {
  /* check if there are any children too far away from the camera */
  glm::vec3 distanceToCamera;
  GLfloat direction = 0.0f;

  distanceToCamera = camera.getTranslation() - getTranslation();

  GLfloat maximumDistance = mJumpStep * 2;
  GLfloat jumpStep = mJumpStep * 2;
  if (glm::abs(distanceToCamera.x) > maximumDistance) {
      direction = distanceToCamera.x > 0.0f ? 1.0f : -1.0f;
      moveBy(glm::vec3(direction * jumpStep, 0.0, 0.0));
  }

  if (glm::abs(distanceToCamera.z) > maximumDistance) {
    direction = distanceToCamera.z > 0.0f ? 1.0f : -1.0f;
    moveBy(glm::vec3(0.0, 0.0, direction * jumpStep));
  }
}

} /* flf */
} /* flw */
