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

#include <fillwave/models/base/IEmiterPoint.h>
#include <fillwave/core/extended/pipeline/Fence.h>
#include <fillwave/core/extended/buffers/VertexBufferParticlesGPU.h>

namespace flw {
class Engine;
namespace flf {

/*! \class EmiterPointGPU
 * \brief Polynomial particle Emiter entirely computed on GPU.
 * Can generate a particles with velocity, direction,
 * and acceleration defined by the user.
 */

class EmiterPointGPU : public IEmiterPoint {
public:
  EmiterPointGPU(Engine *engine,
      GLfloat emitingSourceRate,
      GLuint howMany,
      glm::vec4 color,
      glm::vec3 acceleration,
      glm::vec3 startVelocity,
      glm::vec3 robustnessVelocity,
      glm::vec3 startPosition,
      glm::vec3 robustnessPosition,
      GLfloat startSize,
      GLfloat lifetime,
      flc::Texture2D* texture,
      GLenum blendingSource,
      GLenum blendingDestination,
      GLboolean depthTesting,
      GLfloat alphaCutOffLevel = 0.0f);

  ~EmiterPointGPU() override = default;

  /* IEmiterPoint */
  void update(GLfloat timeElapsedSec) override;

  /* IDrawable */
  void draw(ICamera &camera) override;

  void drawPBRP(ICamera &camera) override;

  /* IRenderable */
  bool getRenderItem(RenderItem &item) override;

private:
  static const GLint mPingPongBuffers = 2;
  GLuint mSrcIndex;
  GLuint mNoiseTextureHandle;
  GLfloat mEmmisingSourceRate;
  glm::vec3 mAcceleration;
  glm::vec3 mStartVelocity;
  glm::vec3 mRobustnessVelocity;
  glm::vec3 mStartPosition;
  glm::vec3 mRobustnessPosition;
  glm::vec3 mCameraPosition;
  GLfloat mTimeDeltaEmiter;
  flc::Program *mProgramEmiter;
  pu<flc::Fence> mFence;

  flc::VertexBufferParticlesGPU* mVBOGPU[mPingPongBuffers];

  GLint mULCTimeEmiter, mULCEmissionRateEmiter, mULCModelMatrixEmiter, mULCCameraPositionEmiter, mULCHowManyEmiter, mULCAccelerationEmiter, mULCStartVelocityEmiter, mULCStartPositionEmiter, mULCLifeTimeEmiter, mULCRobustnessVelocityEmiter, mULCRobustnessPositionEmiter, mULCNoiseSamplerEmiter;

  GLint mULCModelMatrix, mULCViewProjectionMatrix, mULCCameraPosition, mULCTextureUnit, mULCTime, mULCAcceleration, mULCColor, mULCAlphaCutOff, mULCStartSize;

  void initBuffers() override;

  void initPipeline() override;

  void initVBO() override;

  void initVAO() override;

  void initUniformsCache() override;

  void coreDraw();

  void sort(glm::vec3 cameraPosition);
};

} /* flf */
} /* flw */
