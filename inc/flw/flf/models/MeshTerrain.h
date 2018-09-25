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

#include <flw/flf/models/Mesh.h>
#include <flw/flf/models/base/Programmable.h>
#include <flw/flf/models/terrain/TerrainConstructor.h>

namespace flw {
class Engine;
namespace flf {

/*! \class MeshTerrain
 * \brief Programmable to provide mesh terrain functionality.
 */

class MeshTerrain : public Programmable {
public:
  MeshTerrain(Engine *engine,
      flc::Program *program,
      TerrainConstructor *constructor,
      const Material &material,
      const std::string &diffuseMapPath,
      const std::string &normalMapPath,
      const std::string &specularMapPath,
      GLuint radius,
      GLuint density = 8);

  MeshTerrain(Engine *engine,
      flc::Program *program,
      TerrainConstructor *constructor,
      const Material &material,
      flc::Texture2D *diffuseMapPath,
      flc::Texture2D *normalMapPath,
      flc::Texture2D *specularMapPath,
      GLuint radius,
      GLuint density = 8);

  ~MeshTerrain() override = default;

  void initIBO(std::vector<GLuint> &indices, GLuint density);

  /* IDrawable */
  void draw(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  /* IRenderable */
  void updateRenderer(IRenderer &renderer) override;

private:
  LightSystem &mLights;
  GLfloat mJumpStep;

  void distanceCheck(ICamera &camera);
};

} /* flf */
} /* flw */
