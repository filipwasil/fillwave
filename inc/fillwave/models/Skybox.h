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

#include <fillwave/models/Entity.h>
#include <fillwave/core/texturing/Texture3D.h>
#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/base/IReloadable.h>

namespace flw {
class Engine;
namespace flf {

/*! \class Skybox
 * \brief Entity which moves with the camera clipping the view space with an image.
 */

class Skybox : public Entity, public IReloadable {
public:
  Skybox(Engine *engine, flc::Texture3D *texture);

  virtual ~Skybox() = default;

  /* IDrawable */
  void draw(ICamera &camera);

  void drawDR(ICamera &camera);

  /* IRenderable */
  bool getRenderItem(RenderItem &item);

protected:
  flc::Program *mProgram;
  flc::Program *mProgramDR;

private:
  flc::Texture3D *mTexture;
  flc::VertexBufferPosition *mVBO;
  flc::IndexBuffer *mIBO;
  GLint mULCCameraPosition, mULCModelMatrixPosition, mULCViewProjectionMatrix, mULCTextureUnit;

  void initBuffers();

  void initPipeline();

  void initUniformsCache();

  void initVAO();

  void initVBO();
};

} /* flf */
typedef std::unique_ptr<flf::Skybox> puSkybox;
} /* flw */
