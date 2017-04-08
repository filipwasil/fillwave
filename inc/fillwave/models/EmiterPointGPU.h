/*
 * EmiterPointGPU.h
 *
 *  Created on: 22 Apr 2015
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

#ifndef EMITERPOINTGPU_H_
#define EMITERPOINTGPU_H_

#include <fillwave/core/buffers/VertexBufferParticlesGPU.h>
#include <fillwave/core/pipeline/Fence.h>
#include <fillwave/models/base/IEmiterPoint.h>

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
      flc::Texture *texture,
      GLenum blendingSource,
      GLenum blendingDestination,
      GLboolean depthTesting,
      GLfloat alphaCutOffLevel = 0.0f);

  virtual ~EmiterPointGPU() = default;

  /* IEmiterPoint */
  void update(GLfloat timeElapsedSec);

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
  puFence mFence;

  flc::VertexBufferParticlesGPU *mVBOGPU[mPingPongBuffers];

  GLint mULCTimeEmiter, mULCEmissionRateEmiter, mULCModelMatrixEmiter, mULCCameraPositionEmiter, mULCHowManyEmiter, mULCAccelerationEmiter, mULCStartVelocityEmiter, mULCStartPositionEmiter, mULCLifeTimeEmiter, mULCRobustnessVelocityEmiter, mULCRobustnessPositionEmiter, mULCNoiseSamplerEmiter;

  GLint mULCModelMatrix, mULCViewProjectionMatrix, mULCCameraPosition, mULCTextureUnit, mULCTime, mULCAcceleration, mULCColor, mULCAlphaCutOff, mULCStartSize;

  void initBuffers();

  void initPipeline();

  void initVBO();

  void initVAO();

  void initUniformsCache();

  void coreDraw();

  void sort(glm::vec3 cameraPosition);
};

} /* particles */
} /* flw */

#endif /* EMITERPOINTGPU_H_ */
