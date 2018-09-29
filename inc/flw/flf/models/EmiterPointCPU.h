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

#include <flw/flf/models/base/IEmiterPoint.h>

#include <flw/flc/buffers/mVertexBufferFloat.h>
#include <flw/flc/operations/TQuery.h>

namespace flw {
class ICamera;

namespace flf {

/*! \class EmiterPointCPU
 * \brief Polynomial particle Emiter.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointCPU : public IReloadable, public Entity, public IEmiterPoint {
public:
  EmiterPointCPU(
    Engine *engine
    , GLfloat emitingSourceRate
    , GLuint howMany
    , glm::vec4 color
    , glm::vec3 acceleration = glm::vec3(0.0)
    , glm::vec3 startVelocity = glm::vec3(0.0)
    , glm::vec3 robustnessVelocity = glm::vec3(0.0)
    , glm::vec3 startPosition = glm::vec3(0.0)
    , glm::vec3 robustnessPosition = glm::vec3(0.0)
    , GLfloat startSize = 1.0
    , GLfloat lifetime = 6.0
    , flc::Texture2D* texture = nullptr
    , GLenum blendingSource = GL_SRC_ALPHA
    , GLenum blendingDestination = GL_ONE_MINUS_SRC_ALPHA
    , GLboolean depthTesting = GL_TRUE
    , GLfloat alphaCutOffLevel = 0.0f);

  ~EmiterPointCPU() override = default;

  /* IEmiterPoint */
  void update(GLfloat timeElapsedSec) override;

  /* IRenderable */
  void drawFR(ICamera& camera) override;
  void drawPBRP(ICamera& camera) override;
  bool getRenderItem(flc::RenderItem &item) override;

  /* IRenderable */
  void updateRenderer(flc::IRenderer &renderer) override;

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
