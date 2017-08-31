/*
 * EmiterPointCPU.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: filip
 *
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


#include <fillwave/models/EmiterPointCPU.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("EmiterPointCPU", FERROR | FFATAL | FINFO)

namespace flw {
namespace flf {

EmiterPointCPU::EmiterPointCPU(Engine *engine,
    GLfloat /*emitingSourceRate*/, // todo not used for now
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
                   alphaCutOffLevel), mAcceleration(acceleration), mStartVelocity(startVelocity), mStartPosition(
    startPosition) {

  ProgramLoader loader(engine);

  mProgram = loader.getProgram(EProgram::particleCPU);

  /* Fill buffers */
  GLfloat time = 0.0f; // start time
  std::vector<GLfloat> times;
  std::vector<GLfloat> positions;
  std::vector<GLfloat> velocities;
  std::vector<GLfloat> cameraDistanceTF;

  times.reserve(howMany);
  positions.reserve(3 * howMany);
  velocities.reserve(3 * howMany);
  cameraDistanceTF.reserve(howMany);

  for (GLuint i = 0; i < howMany; i++) {

    times.push_back(time);
    time += 1.0f / lifetime;

    /* particles velocity */
    GLfloat x = (((GLfloat) rand() / (GLfloat) RAND_MAX)) * robustnessVelocity.x * 1.0f - robustnessVelocity.x * 0.5f;
    GLfloat y = (((GLfloat) rand() / (GLfloat) RAND_MAX)) * robustnessVelocity.y * 1.0f - robustnessVelocity.y * 0.5f;
    GLfloat z = (((GLfloat) rand() / (GLfloat) RAND_MAX)) * robustnessVelocity.z * 1.0f - robustnessVelocity.z * 0.5f;
    velocities.push_back(x);
    velocities.push_back(y);
    velocities.push_back(z);

    /* emiter surface shape */
    x = ((GLfloat) rand() / (GLfloat) RAND_MAX) * robustnessPosition.x * 1.0f - robustnessPosition.x * 0.5f;
    y = ((GLfloat) rand() / (GLfloat) RAND_MAX) * robustnessPosition.y * 1.0f - robustnessPosition.y * 0.5f;
    z = ((GLfloat) rand() / (GLfloat) RAND_MAX) * robustnessPosition.z * 1.0f - robustnessPosition.z * 0.5f;
    positions.push_back(x);
    positions.push_back(y);
    positions.push_back(z);

    cameraDistanceTF.push_back(0.0);
  }

  /* Initialize OpenGL stuff */
  mVBO = engine->storeBuffer<flc::VertexBufferParticles>(mVAO, velocities, positions, times);
  mIBO = engine->storeBuffer<flc::IndexBuffer>(mVAO, howMany);

  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

void EmiterPointCPU::update(GLfloat timeElapsedSec) {
  mProgram->use();
  flc::Uniform::push(mULCTimeElapsed, timeElapsedSec);
  flc::Program::disusePrograms();
}

void EmiterPointCPU::draw(ICamera &camera) {
  mCameraPosition = camera.getTranslation();

  mProgram->use();

  flc::Uniform::push(mULCModelMatrix, mPhysicsMMC);
  flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
  flc::Uniform::push(mULCCameraPosition, mCameraPosition);
  flc::Uniform::push(mULCPointSize, mStartSize);
  flc::Uniform::push(mULCColor, mColor);
  flc::Uniform::push(mULCAcceleration, mAcceleration);
  flc::Uniform::push(mULCLifeTime, mLifetime);
  flc::Uniform::push(mULCAlphaCutOff, mAlphaCutOff);
//   flc::Uniform::push(mULCSourcePosition, mTranslation);

  coreDraw();

  flc::Program::disusePrograms();
}

void EmiterPointCPU::drawPBRP(ICamera &camera) {
  mCameraPosition = camera.getTranslation();

  flc::Uniform::push(mULCModelMatrix, mPhysicsMMC);
  flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
  flc::Uniform::push(mULCCameraPosition, mCameraPosition);
  flc::Uniform::push(mULCPointSize, mStartSize);
  flc::Uniform::push(mULCColor, mColor);
  flc::Uniform::push(mULCAcceleration, mAcceleration);
  flc::Uniform::push(mULCLifeTime, mLifetime);
  flc::Uniform::push(mULCAlphaCutOff, mAlphaCutOff);
//   flc::Uniform::push(mULCSourcePosition, mTranslation);

  coreDraw();
}

inline void EmiterPointCPU::coreDraw() {

  mVAO->bind();

  if (mTexture) {
    mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
  }

  if (!mDepthTesting) {
    glDepthMask(GL_FALSE);
  }

  glEnable(GL_BLEND);
  glBlendFunc(mBlending.mSrc, mBlending.mDst);
  glDrawElements(GL_POINTS, mIBO->getElements(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(0));
  fLogC("Draw elements");
  glDisable(GL_BLEND);
  if (mDepthTesting) {
    glDepthMask(GL_TRUE);
  }

  flc::Texture2D::unbind2DTextures();

  flc::VertexArray::unbindVAO();
}

void EmiterPointCPU::initBuffers() {
  if (mIBO) {
    mIBO->reload();
  }
  if (mVBO) {
    mVBO->reload();
  }
}

void EmiterPointCPU::initPipeline() {
  mProgram->use();
  mProgram->uniformPush("uTextureUnit", FILLWAVE_DIFFUSE_UNIT);
  flc::Program::disusePrograms();
}

void EmiterPointCPU::initUniformsCache() {
  mULCTimeElapsed = mProgram->getUniformLocation("uTimeElapsed");
  mULCModelMatrix = mProgram->getUniformLocation("uModelMatrix");
  mULCViewProjectionMatrix = mProgram->getUniformLocation("uViewProjectionMatrix");
  mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
  mULCPointSize = mProgram->getUniformLocation("uPointSize");
  mULCColor = mProgram->getUniformLocation("uColor");
  mULCAcceleration = mProgram->getUniformLocation("uAcceleration");
  mULCLifeTime = mProgram->getUniformLocation("uLifeTime");
  mULCAlphaCutOff = mProgram->getUniformLocation("uAlphaCutOff");
  mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
}

void EmiterPointCPU::initVAO() {
  mSampler->bind();
  mVAO->bind();
  mVBO->bind();
  mVBO->setLoaded(GL_FALSE);
  mVBO->send();
  mVBO->attributesSetForVAO();
  mIBO->bind();
  mIBO->setLoaded(GL_FALSE);
  mIBO->send();
  flc::VertexArray::unbindVAO();
}

void EmiterPointCPU::initVBO() {
  mVBO->initAttributes(mProgram->getHandle());
}

bool EmiterPointCPU::getRenderItem(RenderItem &item) {
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

  item.mRenderStatus = 0xe4;
  return true;
}

} /* flf */
} /* flw */
