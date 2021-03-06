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

#include <flw/cmn/scene/ICamera.h>

#include <flw/flf/models/EmiterPointCPU.h>
#include <flw/flf/loaders/ProgramLoader.h>

#include <flw/Fillwave.h>

#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

EmiterPointCPU::EmiterPointCPU(Engine *engine,
  GLfloat /*emitingSourceRate*/,
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
  GLfloat alphaCutOffLevel)
  : IReloadable(engine)
  , Entity()
  , IEmiterPoint(howMany,
                 startSize,
                 lifetime,
                 texture,
                 color,
                 blendingSource,
                 blendingDestination,
                 depthTesting,
                 alphaCutOffLevel)
  , mAcceleration(acceleration)
  , mStartVelocity(startVelocity)
  , mStartPosition(startPosition) {

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

  for (GLuint i = 0; i < howMany; ++i) {

    times.push_back(time);
    time += 1.0f / lifetime;
    const auto max = static_cast<GLfloat>( RAND_MAX );
    /* particles velocity */
    GLfloat x = (static_cast<GLfloat>(rand()) / max) * robustnessVelocity.x * 1.0f - robustnessVelocity.x * 0.5f;
    GLfloat y = (static_cast<GLfloat>(rand()) / max) * robustnessVelocity.y * 1.0f - robustnessVelocity.y * 0.5f;
    GLfloat z = (static_cast<GLfloat>(rand()) / max) * robustnessVelocity.z * 1.0f - robustnessVelocity.z * 0.5f;
    velocities.push_back(x);
    velocities.push_back(y);
    velocities.push_back(z);

    /* emiter surface shape */
    x = (static_cast<GLfloat>(rand()) / max) * robustnessPosition.x * 1.0f - robustnessPosition.x * 0.5f;
    y = (static_cast<GLfloat>(rand()) / max) * robustnessPosition.y * 1.0f - robustnessPosition.y * 0.5f;
    z = (static_cast<GLfloat>(rand()) / max) * robustnessPosition.z * 1.0f - robustnessPosition.z * 0.5f;
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

  attachHandler([this] (const Event& event) {
    mCallbackTimePassed += event.getData().mTime.timePassed;
    update(mCallbackTimePassed);
  }, EEventType::time );
}

void EmiterPointCPU::update(GLfloat timeElapsedSec) {
  mProgram->use();
  flc::Uniform::push(mULCTimeElapsed, timeElapsedSec);
  flc::Program::disusePrograms();
}

void EmiterPointCPU::drawFR(ICamera &camera) {
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

  drawParticles();

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
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20) || defined(FILLWAVE_BACKEND_OPENGL_ES_30)
#else
  mSampler->bind();
#endif
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

bool EmiterPointCPU::getRenderItem(flc::RenderItem &item) {
  item.mBlend = mBlending;
  item.mCount = mIBO->getElements();
  item.mDataType = GL_UNSIGNED_INT;
  item.mFirst = 0;
  item.mHandles[flc::RenderItem::eRenderHandleProgram] = mProgram->getHandle();
#if defined(FILLWAVE_BACKEND_OPENGL_ES_30) || defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  item.mHandles[flc::RenderItem::eRenderHandleSampler] = 0;
#else
  item.mHandles[flc::RenderItem::eRenderHandleSampler] = mSampler->getHandle();
#endif
  item.mHandles[flc::RenderItem::eRenderHandleVAO] = mVAO->getHandle();
  item.mHandles[flc::RenderItem::eRenderHandleDiffuse] = mTexture->mTexture.mHandles[0];
  item.mIndicesPointer = 0;
  item.mMode = GL_POINTS;

  item.mRenderStatus = 0xe4;
  return true;
}

void EmiterPointCPU::updateRenderer(flc::IRenderer &renderer) {
  renderer.update(this);
}

} /* flf */
} /* flw */
