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

#include <fillwave/models/Entity.h>
#include <fillwave/core/extended/texturing/Texture3D.h>
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
} /* flw */
