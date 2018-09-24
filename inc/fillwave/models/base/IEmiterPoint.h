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
#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/core/buffers/VertexBufferParticles.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/pipeline/Blending.h>
#include <fillwave/models/base/IReloadable.h>

namespace flw {
class Engine;
namespace flf {

/*! \class IEmiterPoint
 * \brief Drawable Entity which emits particles.
 */

class IEmiterPoint : public IReloadable, public Entity {
public:
  IEmiterPoint(Engine *engine,
      GLuint howMany,
      GLfloat size,
      GLfloat lifetime,
      flc::Texture2D *texture,
      glm::vec4 color,
      GLenum blendingSource,
      GLenum blendingDestination,
      GLboolean depthTesting,
      GLfloat alphaCutOff);

  ~IEmiterPoint() override = default;

  void setBlending(GLenum sourceFactor, GLenum destinationFactor);

  virtual void update(GLfloat timeElapsedSec) = 0;

  void draw(ICamera &camera) override = 0;

  /* IRenderable */
  void updateRenderer(IRenderer &renderer) override;

protected:
  GLfloat mStartSize;
  GLfloat mLifetime;
  flc::Texture2D* mTexture;
  glm::vec4 mColor;
  GLuint mHowMany;
  GLboolean mDepthTesting;
  GLfloat mAlphaCutOff;
  flc::Program *mProgram;
  flc::IndexBuffer *mIBO;
  Blending mBlending;
};

} /* flf */
} /* flw */
