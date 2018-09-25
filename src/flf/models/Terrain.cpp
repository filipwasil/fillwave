/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <flw/flf/models/Terrain.h>

#include <flw/flf/management/LightSystem.h>

#include <flw/Fillwave.h>

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

void Terrain::addChunk(pu<VoxelChunk> chunk) {
  mVoxelChunks.push_back(std::move(chunk));
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
pu<flf::Terrain> buildTerrainVoxel(Engine *engine,
    flc::Program *program,
    const std::string &texturePath,
    flf::VoxelConstructor *constructor,
    GLint radius) {

  const GLfloat gap = 0.2f;

  auto terrain = std::make_unique<flf::Terrain>(engine, program, radius, gap);

  for (GLint i = 0; i <= radius; i++) {
    for (GLint x = 0; x < 1 + 2 * i; x++) {
      for (GLint z = 0; z < 1 + 2 * i; z++) {
        auto chunk =
          std::make_unique<flf::VoxelChunk>(program,engine, texturePath, FILLWAVE_VOXEL_CHUNK_SIZE, constructor, gap);
        chunk->moveTo(glm::vec3(
            FILLWAVE_VOXEL_CHUNK_SIZE * gap * x - FILLWAVE_VOXEL_CHUNK_SIZE * gap * (radius),
            0.0,
            FILLWAVE_VOXEL_CHUNK_SIZE * gap * z - FILLWAVE_VOXEL_CHUNK_SIZE * gap * (radius)));
        terrain->addChunk(std::move(chunk));
      }
    }
  }
  return terrain;
}
} /* flw */
