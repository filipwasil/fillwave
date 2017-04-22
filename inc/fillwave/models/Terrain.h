#pragma once

/*
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

#include <fillwave/models/terrain/VoxelChunk.h>

namespace flw {
class Engine;
namespace flf {

/*! \class Terrain
 * \brief Entity to provide terrain generation functionality.
 */

class Terrain : public Entity {
public:
  Terrain(Engine *engine, flc::Program *program, GLint radius, GLfloat gap);

  virtual ~Terrain() = default;

  void addChunk(pVoxelChunk chunk);

  void distanceCheck(ICamera &camera);

  /* IDrawable */
  void draw(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  /* IRenderable */
  void updateRenderer(IRenderer &renderer) override;

  bool getRenderItem(RenderItem &item) override;

protected:
  void updateRendererData();

private:
  flc::Program *mProgram;
  LightSystem &mLights;
  GLint mRadius;
  GLfloat mGap;
  std::vector<pVoxelChunk> mVoxelChunks;
};

} /* flf */
typedef std::unique_ptr<flf::Terrain> puTerrain;

puTerrain buildTerrainVoxel(Engine *engine,
    flc::Program *program,
    const std::string &texturePath,
    flf::VoxelConstructor *constructor,
    GLint radius = 0);

} /* flw */
