#pragma once

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

#include <fillwave/models/terrain/VoxelChunk.h>

namespace flw {
class Engine;
namespace flf {

/*! \class Terrain
 * \brief Entity to provide terrain generation functionality.
 */

class Terrain : public Entity {
public:
  Terrain(Engine* engine, flc::Program* program, GLint radius, GLfloat gap);

  ~Terrain() override = default;

  void addChunk(pu<VoxelChunk> chunk);

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
  std::vector<pu<VoxelChunk>> mVoxelChunks;
};

} /* flf */

pu<flf::Terrain>
  buildTerrainVoxel(Engine*, flc::Program*, const std::string& path, flf::VoxelConstructor*, GLint radius = 0);

} /* flw */
