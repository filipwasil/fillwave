/*
 * EmiterPoint.h
 *
 *  Created on: 16 Jun 2014
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

#ifndef EMITERPOINT_H_
#define EMITERPOINT_H_

#include <fillwave/models/Entity.h>
#include <fillwave/core/buffers/IndexBuffer.h>
#include <fillwave/core/buffers/VertexBufferParticles.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/core/texturing/Texture.h>
#include <fillwave/core/rendering/TransformFeedback.h>
#include <fillwave/core/pipeline/Blending.h>
#include <fillwave/models/base/IReloadable.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class IEmiterPoint
 * \brief Drawable Entity which emits particles.
 */

class IEmiterPoint : public IReloadable, public Entity {
public:
  IEmiterPoint(Engine *engine,
      GLuint howMany,
      GLfloat size,
      GLfloat lifetime,
      core::Texture *texture,
      glm::vec4 color,
      GLenum blendingSource,
      GLenum blendingDestination,
      GLboolean depthTesting,
      GLfloat alphaCutOff);

  virtual ~IEmiterPoint() = default;

  void setBlending(GLenum sourceFactor, GLenum destinationFactor);

  virtual void update(GLfloat timeElapsedSec) = 0;

  virtual void draw(ICamera &camera) = 0;

  /* IRenderable */
  void updateRenderer(IRenderer &renderer) override;

protected:
  GLfloat mStartSize;
  GLfloat mLifetime;
  core::Texture *mTexture;
  glm::vec4 mColor;
  GLuint mHowMany;
  GLboolean mDepthTesting;
  GLfloat mAlphaCutOff;
  core::Program *mProgram;
  core::IndexBuffer *mIBO;
  Blending mBlending;
};

} /* framework */
typedef std::unique_ptr<framework::IEmiterPoint> puIEmiterPoint;
} /* fillwave */

#endif /* EMITERPOINT_H_ */
