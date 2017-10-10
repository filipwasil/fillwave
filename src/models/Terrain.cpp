/*
 * Terrain.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: filip
 *
 * Copyright (c) 2017, Fillwave developers
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


#include <fillwave/models/Terrain.h>
#include <fillwave/Fillwave.h>
#include <fillwave/management/LightSystem.h>

static int FILLWAVE_VOXEL_CHUNK_SIZE = 16;

namespace flw {
namespace flf {

Terrain::Terrain(Engine *engine, flc::Program *program, GLint radius, GLfloat gap)
    : mProgram(program)
    , mLights(engine->getLightSystem())
    , mRadius(radius)
    , mGap(gap) {

}

void Terrain::draw(ICamera &camera) {
  distanceCheck(camera);
  for (auto &it : mVoxelChunks) {
    it->draw(camera);
  }
}

void Terrain::drawPBRP(ICamera &camera) {
  distanceCheck(camera);
  mLights.pushLightUniforms(mProgram);
  mLights.bindShadowmaps();
  for (auto &it : mVoxelChunks) {
    it->drawPBRP(camera);
  }
}

inline void Terrain::distanceCheck(ICamera &camera) {
  /* check if there are any children too far away from the camera */
  glm::vec3 distanceToCamera;

  GLint centralChunkIndex = ((mRadius * 2 + 1) * (mRadius * 2 + 1) - 1) / 2;
  distanceToCamera = camera.getTranslation() - glm::vec3(mVoxelChunks[centralChunkIndex]->getTranslation());

  GLfloat singleChunkWidth = FILLWAVE_VOXEL_CHUNK_SIZE * mGap * mRadius;
  GLfloat maximumDistance = singleChunkWidth * 0.5f;

  if (glm::abs(distanceToCamera.x) > maximumDistance) {
    const float direction = distanceToCamera.x > 0.0f ? 1.0f : -1.0f;
    for (auto &it : mVoxelChunks) {
      it->moveByX(direction * singleChunkWidth);
    }
  }

  if (glm::abs(distanceToCamera.z) > maximumDistance) {
    const float direction = distanceToCamera.z > 0.0f ? 1.0f : -1.0f;
    for (auto &it : mVoxelChunks) {
      it->moveByZ(direction * singleChunkWidth);
    }
  }
}

void Terrain::addChunk(pVoxelChunk chunk) {
  mVoxelChunks.push_back(chunk);
}

void Terrain::updateRenderer(IRenderer &renderer) {
  renderer.update(this);
}

bool Terrain::getRenderItem(RenderItem &item) {
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
  item.mRenderStatus = 0x02; // vao, ibo, diff, norm, spec, blend, cont, anima
  return true;
}

} /* flf */
puTerrain buildTerrainVoxel(Engine *engine,
    flc::Program *program,
    const std::string &texturePath,
    flf::VoxelConstructor *constructor,
    GLint radius) {

  const GLfloat voxelGap = 0.2f;

  puTerrain terrain = std::make_unique<flf::Terrain>(engine, program, radius, voxelGap);

  for (GLint i = 0; i <= radius; i++) {
    for (GLint x = 0; x < 1 + 2 * i; x++) {
      for (GLint z = 0; z < 1 + 2 * i; z++) {
        pVoxelChunk chunk = pVoxelChunk(new flf::VoxelChunk(program,
                                                                  engine,
                                                                  texturePath,
                                                                  FILLWAVE_VOXEL_CHUNK_SIZE,
                                                                  constructor,
                                                                  voxelGap));
        chunk->moveTo(glm::vec3(
            FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * x - FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * (radius),
            0.0,
            FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * z - FILLWAVE_VOXEL_CHUNK_SIZE * voxelGap * (radius)));
        terrain->addChunk(chunk);
      }
    }
  }
  return terrain;
}
} /* flw */
