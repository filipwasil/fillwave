/*
 * EmiterPointGPU.cpp
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


#include <fillwave/loaders/ProgramLoader.h>

#include <fillwave/models/EmiterPointGPU.h>

#include <fillwave/Fillwave.h>

#include <fillwave/core/texturing/NoiseTexture3DArray.h>
#include <fillwave/Log.h>

FLOGINIT("EmiterPointGPU", FERROR | FFATAL)

namespace fillwave {
namespace framework {

EmiterPointGPU::EmiterPointGPU(Engine *engine,
    GLfloat emitingSourceRate,
    GLuint howMany,
    glm::vec4 color,
    glm::vec3 acceleration,
    glm::vec3 startVelocity,
    glm::vec3 /*robustnessVelocity*/, // xxx this is not used for now
    glm::vec3 startPosition,
    glm::vec3 robustnessPosition,
    GLfloat startSize,
    GLfloat lifetime,
    core::Texture *texture,
    GLenum blendingSource,
    GLenum blendingDestination,
    GLboolean depthTesting,
    GLfloat alphaCutOffLevel)
    : IEmiterPoint(engine,
                   howMany,
                   startSize,
                   lifetime,
                   texture,
                   color,
                   blendingSource,
                   blendingDestination,
                   depthTesting,
                   alphaCutOffLevel), mSrcIndex(0), mNoiseTextureHandle(0), mEmmisingSourceRate(emitingSourceRate)
    , mAcceleration(acceleration), mStartVelocity(startVelocity), mRobustnessVelocity(robustnessPosition)
    , mStartPosition(startPosition), mRobustnessPosition(robustnessPosition), mTimeDeltaEmiter(0.0) {

  ProgramLoader loader(engine);

  mProgram = loader.getParticleGPU();
  mProgramEmiter = loader.getParticleGPUEmiter();

  std::vector<core::VertexParticleGPU> particles;
  for (GLuint i = 0; i < mHowMany; i++) {
    core::VertexParticleGPU particle;
    particle.position[0] = 0.0f;
    particle.position[1] = 0.0f;
    particle.position[2] = 0.0f;
    particle.velocity[0] = 0.0f;
    particle.velocity[1] = 0.0f;
    particle.velocity[2] = 0.0f;
    particle.size = 0.0f;
    particle.currentTime = 0.0f;
    particle.lifetime = 0.0f;
    particle.cameraDistance = 0.0f;
    particles.push_back(particle);
  }

  /* Initialize OpenGL stuff */
  GLint noiseTextureSize;
  if (howMany < 50.0) {
    noiseTextureSize = 64;
  } else if (howMany < 1001.0) {
    noiseTextureSize = 128;
  } else {
    noiseTextureSize = 256;
  }

  mNoiseTextureHandle = Create3DNoiseTexture(noiseTextureSize, howMany / 3); //xxx todo store in Manager

  mVBOGPU[0] = engine->storeBuffers<core::VertexBufferParticlesGPU>(mVAO, 0, particles);
  mVBOGPU[1] = engine->storeBuffers<core::VertexBufferParticlesGPU>(mVAO, 1, particles);
  mIBO = engine->storeBuffer<core::IndexBuffer>(mVAO, mHowMany);

  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

void EmiterPointGPU::draw(ICamera &camera) {
  /* Save camera position for optimization purposes. */
  mCameraPosition = camera.getTranslation();

  /* Emit particles */
  mProgramEmiter->use();

  core::Uniform::push(mULCTimeEmiter, mTimeDeltaEmiter);
  core::Uniform::push(mULCModelMatrixEmiter, mPhysicsMMC);
  core::Uniform::push(mULCCameraPositionEmiter, mCameraPosition);
  core::Uniform::push(mULCHowManyEmiter, static_cast<GLfloat>(mHowMany));
  core::Uniform::push(mULCEmissionRateEmiter, mEmmisingSourceRate);
  core::Uniform::push(mULCAccelerationEmiter, mAcceleration);
  core::Uniform::push(mULCStartVelocityEmiter, mStartVelocity);
  core::Uniform::push(mULCStartPositionEmiter, mStartPosition);
  core::Uniform::push(mULCLifeTimeEmiter, mLifetime);
  core::Uniform::push(mULCRobustnessVelocityEmiter, mRobustnessVelocity);
  core::Uniform::push(mULCRobustnessPositionEmiter, mRobustnessPosition);
  core::Uniform::push(mULCNoiseSamplerEmiter, FILLWAVE_NOISE_UNIT);

  mVBOGPU[mSrcIndex]->bind();
  mVBOGPU[mSrcIndex]->attributesSetForVAO();

  mVBOGPU[(mSrcIndex + 1) % 2]->bind(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
  mVBOGPU[(mSrcIndex + 1) % 2]->bindBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0);

  glEnable(GL_RASTERIZER_DISCARD);

  glActiveTexture(GL_TEXTURE0 + FILLWAVE_NOISE_UNIT);
  glBindTexture(GL_TEXTURE_3D, mNoiseTextureHandle);

  core::TransformFeedback::begin(GL_POINTS);

  glDrawArrays(GL_POINTS, 0, mVBOGPU[mSrcIndex]->getElements());
  fLogC("Drawn buffer index %d drawing %d ", mSrcIndex, mVBOGPU[mSrcIndex]->getElements());

  core::TransformFeedback::end();

//   mFence = puFence (new core::Fence(GL_SYNC_GPU_COMMANDS_COMPLETE));

  glDisable(GL_RASTERIZER_DISCARD);

  mVBOGPU[(mSrcIndex + 1) % 2]->unbindBase(GL_TRANSFORM_FEEDBACK_BUFFER);
  mVBOGPU[(mSrcIndex + 1) % 2]->unbind();

  glBindTexture(GL_TEXTURE_3D, 0);

  mSrcIndex = (mSrcIndex + 1) % 2;

  /* Draw particles */

  mProgram->use();

  core::Uniform::push(mULCModelMatrix, mPhysicsMMC);
  core::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
  core::Uniform::push(mULCCameraPosition, mCameraPosition);
  core::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);
  core::Uniform::push(mULCTime, mTimeDeltaEmiter);
  core::Uniform::push(mULCAcceleration, mAcceleration);
  core::Uniform::push(mULCColor, mColor);
  core::Uniform::push(mULCStartSize, mStartSize);
  core::Uniform::push(mULCAlphaCutOff, mAlphaCutOff);

  coreDraw();
}

void EmiterPointGPU::drawPBRP(ICamera &camera) {
  /* for now PBRP is not supported for GPU particle emiter */
  draw(camera);
}

inline void EmiterPointGPU::coreDraw() {
  mVAO->bind();
  /* Disabled fence for speed boost */
//   mFence->wait();
//   mFence.reset();
  mVBOGPU[mSrcIndex]->bind();
  mVBOGPU[mSrcIndex]->attributesSetPointer();

  if (not mDepthTesting) {
    glDepthMask(GL_FALSE);
  }

  if (mTexture) {
    mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
  }

  glEnable(GL_BLEND);
  glBlendFunc(mBlending.mSrc, mBlending.mDst);
  glDrawElements(GL_POINTS, mIBO->getElements(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(0));
  fLogC("Draw elements");

  if (not mDepthTesting) {
    glDepthMask(GL_TRUE);
  }

  glDisable(GL_BLEND);

  core::Texture2D::unbind2DTextures();
  core::VertexArray::unbindVAO();
}

void EmiterPointGPU::update(GLfloat timeElapsedSec) {
  mTimeDeltaEmiter = timeElapsedSec;
}

void EmiterPointGPU::initBuffers() {
  if (mIBO) {
    mIBO->reload();
  }
  for (int i = 0; i < mPingPongBuffers; i++) {
    mVBOGPU[i]->reload();
  }
}

void EmiterPointGPU::initPipeline() {
  const char *feedbackVaryingsGPUEmiter[6] = {
      "tfPosition",
      "tfVelocity",
      "tfSize",
      "tfCurtime",
      "tfLifetime",
      "tfCameraDistance"
  };

  /* GL_INTERLEAVED_ATTRIBS - Common VBO for all attributes */
  /* GL_SEPARATE_ATTRIBS - Common VBO for all attrobutes */
  glTransformFeedbackVaryings(mProgramEmiter->getHandle(), 6, feedbackVaryingsGPUEmiter, GL_INTERLEAVED_ATTRIBS);
  mProgramEmiter->link();

  mProgramEmiter->use();
  mProgramEmiter->uniformPush("uNoiseSampler", FILLWAVE_NOISE_UNIT);

  core::Program::disusePrograms();
}

void EmiterPointGPU::initUniformsCache() {
  /* Emiter program */
  mULCTimeEmiter = mProgramEmiter->getUniformLocation("uTime");
  mULCModelMatrixEmiter = mProgramEmiter->getUniformLocation("uModelMatrix");
  mULCCameraPositionEmiter = mProgramEmiter->getUniformLocation("uCameraPosition");
  mULCHowManyEmiter = mProgramEmiter->getUniformLocation("uHowMany");
  mULCEmissionRateEmiter = mProgramEmiter->getUniformLocation("uEmissionRate");
  mULCAccelerationEmiter = mProgramEmiter->getUniformLocation("uAcceleration");
  mULCStartVelocityEmiter = mProgramEmiter->getUniformLocation("uStartVelocity");
  mULCStartPositionEmiter = mProgramEmiter->getUniformLocation("uStartPosition");
  mULCLifeTimeEmiter = mProgramEmiter->getUniformLocation("uLifeTime");
  mULCRobustnessVelocityEmiter = mProgramEmiter->getUniformLocation("uRobustnessVelocity");
  mULCRobustnessPositionEmiter = mProgramEmiter->getUniformLocation("uRobustnessPosition");
  mULCNoiseSamplerEmiter = mProgramEmiter->getUniformLocation("uNoiseSampler");

  /* Regular program */
  mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
  mULCViewProjectionMatrix = mProgram->getUniformLocation("uViewProjectionMatrix");
  mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
  mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
  mULCTime = mProgram->getUniformLocation("uTime");
  mULCAcceleration = mProgram->getUniformLocation("uAcceleration");
  mULCColor = mProgram->getUniformLocation("uColor");
  mULCStartSize = mProgram->getUniformLocation("uStartSize");
  mULCAlphaCutOff = mProgram->getUniformLocation("uAlphaCutOff");
}

void EmiterPointGPU::initVAO() {
  mSampler->bind();
  mVAO->bind();

  for (int i = 0; i < mPingPongBuffers; i++) {
    mVBOGPU[i]->bind();
    mVBOGPU[i]->setLoaded(GL_FALSE);
    mVBOGPU[i]->send();
    mVBOGPU[i]->attributesSetForVAO();
  }

  mIBO->bind();
  mIBO->setLoaded(GL_FALSE);
  mIBO->send();
  core::VertexArray::unbindVAO();
}

void EmiterPointGPU::initVBO() {
  for (int i = 0; i < mPingPongBuffers; i++) {
    mVBOGPU[i]->initAttributes(mProgram->getHandle());
  }
}

bool EmiterPointGPU::getRenderItem(RenderItem &item) {
  item.mBlend = mBlending;
  item.mCount = mIBO->getElements();
  item.mDataType = GL_UNSIGNED_INT;
  item.mFirst = 0;
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
  item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->getHandle();
  item.mIndicesPointer = 0;
  item.mMode = GL_POINTS;

  item.mRenderStatus = 0xe4; // 11100100
  return true;
}

} /* framework */
} /* fillwave */
