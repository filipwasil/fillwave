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

#include <fillwave/core/buffers/VertexBufferFloat.h>
#include <fillwave/core/operations/TQuery.h>
#include <fillwave/models/base/IEmiterPoint.h>

namespace flw {
namespace flf {

/*! \class EmiterPointCPU
 * \brief Polynomial particle Emiter.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointCPU : public IEmiterPoint {
public:
  EmiterPointCPU(Engine *engine,
      GLfloat emitingSourceRate,
      GLuint howMany,
      glm::vec4 color,
      glm::vec3 acceleration = glm::vec3(0.0),
      glm::vec3 startVelocity = glm::vec3(0.0),
      glm::vec3 robustnessVelocity = glm::vec3(0.0),
      glm::vec3 startPosition = glm::vec3(0.0),
      glm::vec3 robustnessPosition = glm::vec3(0.0),
      GLfloat startSize = 1.0,
      GLfloat lifetime = 6.0,
      flc::Texture *texture = nullptr,
      GLenum blendingSource = GL_SRC_ALPHA,
      GLenum blendingDestination = GL_ONE_MINUS_SRC_ALPHA,
      GLboolean depthTesting = GL_TRUE,
      GLfloat alphaCutOffLevel = 0.0f);

  virtual ~EmiterPointCPU() override = default;

  /* IEmiterPoint */
  void update(GLfloat timeElapsedSec) override;

  /* IDrawable */
  void draw(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  /* IRenderable */
  bool getRenderItem(RenderItem &item) override;

private:
  glm::vec3 mAcceleration;
  glm::vec3 mStartVelocity;
  glm::vec3 mStartPosition;
  glm::vec3 mCameraPosition;

  /* ULC - Uniform location cache */
  flc::VertexBufferParticles *mVBO;
  GLint mULCModelMatrix;
  GLint mULCTextureUnit;
  GLint mULCViewProjectionMatrix;
  GLint mULCCameraPosition;
  GLint mULCPointSize;
  GLint mULCColor;
  GLint mULCAcceleration;
  GLint mULCLifeTime;
  GLint mULCAlphaCutOff;
  GLint mULCTimeElapsed;

  void initBuffers() override;

  void initPipeline() override;

  void initUniformsCache() override;

  void initVAO() override;

  void initVBO() override;

  void coreDraw();
};

} /* flf */
} /* flw */
