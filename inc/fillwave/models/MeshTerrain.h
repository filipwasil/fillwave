/*
 * MeshTerrain.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Filip Wasil
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

#ifndef INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_
#define INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_

#include <fillwave/models/Mesh.h>
#include <fillwave/models/base/Programmable.h>
#include <fillwave/models/terrain/TerrainConstructor.h>

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

  virtual ~MeshTerrain() = default;

  void initIBO(std::vector<GLuint> &indices, GLuint density);

  /* IDrawable */
  void draw(ICamera &camera);

  void drawPBRP(ICamera &camera);

  /* IRenderable */
  void updateRenderer(IRenderer &renderer) override;

private:
  LightSystem *mLights;
  GLfloat mChunkWidth;
  GLfloat mJumpStep;

  void distanceCheck(ICamera &camera);
};

} /* flf */
typedef std::unique_ptr<flf::MeshTerrain> puMeshTerrain;
} /* flw */

#endif /* INC_FILLWAVE_TERRAIN_MESHTERRAIN_H_ */
