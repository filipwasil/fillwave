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

#include <flw/flf/models/Skybox.h>
#include <flw/flf/loaders/ProgramLoader.h>
#include <flw/flf/models/shapes/SphereSkybox.h>
#include <flw/Fillwave.h>
#include <flw/Log.h>

FLOGINIT("Skybox", FERROR | FFATAL)

namespace flw {
namespace flf {

Skybox::Skybox(Engine *engine, flc::Texture3D *texture)
    : IReloadable(engine), mTexture(texture) {

  ProgramLoader loader(engine);

  mProgram = loader.getProgram(EProgram::skybox);
  mProgramDR = loader.getProgram(EProgram::skyboxDR);

  SphereSkybox sphere(1.0f, 10, 10);

  std::vector<GLuint> indices = sphere.getIndices();
  std::vector<flc::VertexPosition> vertices = sphere.getVertices();

  fLogD("Initializing skybox buffer");

  mIBO = engine->storeBuffer<flc::IndexBuffer>(mVAO, indices);
  mVBO = engine->storeBuffer<flc::VertexBufferPosition>(mVAO, vertices);

  initPipeline();
  initVBO();
  initVAO();
  initUniformsCache();
}

void Skybox::draw(ICamera &camera) {
  mProgram->use();

  flc::Uniform::push(mULCCameraPosition, camera.getTranslation());
  flc::Uniform::push(mULCModelMatrixPosition, mPhysicsMMC);
  flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
  flc::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

  mVAO->bind();

  mTexture->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

  glFrontFace(GL_CW);
  if (mIBO) {
    /* Perform index drawing */
    glDrawElements(GL_TRIANGLES, mIBO->getElements(), GL_UNSIGNED_INT, (GLvoid *) 0);
  } else {
    /* Perform array drawing */
    glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
  }
  glFrontFace(GL_CCW);

  flc::Texture2D::unbind2DTextures();

  flc::VertexArray::unbindVAO();
  flc::Program::disusePrograms();
}

void Skybox::drawDR(ICamera &camera) {
  mProgramDR->use();

  flc::Uniform::push(mULCCameraPosition, camera.getTranslation());
  flc::Uniform::push(mULCModelMatrixPosition, mPhysicsMMC);
  flc::Uniform::push(mULCViewProjectionMatrix, camera.getViewProjection());
  flc::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);

  mVAO->bind();

  mTexture->bind(FILLWAVE_DIFFUSE_UNIT); //xxx texture region coordinates are not used

  glFrontFace(GL_CW);
  if (mIBO) {
    /* Perform index drawing */
    glDrawElements(GL_TRIANGLES, mIBO->getElements(), GL_UNSIGNED_INT, (GLvoid *) 0);
  } else {
    /* Perform array drawing */
    glDrawArrays(GL_TRIANGLES, 0, mVBO->getElements());
  }
  glFrontFace(GL_CCW);

  flc::Texture2D::unbind2DTextures();

  flc::VertexArray::unbindVAO();
  flc::Program::disusePrograms();
}

inline void Skybox::initBuffers() {
  if (mIBO) {
    mIBO->reload();
  }
  if (mVBO) {
    mVBO->reload();
  }
}

inline void Skybox::initPipeline() {

}

inline void Skybox::initUniformsCache() {
  mULCCameraPosition = mProgram->getUniformLocation("uCameraPosition");
  mULCModelMatrixPosition = mProgram->getUniformLocation("uModelMatrix");
  mULCViewProjectionMatrix = mProgram->getUniformLocation("uViewProjectionMatrix");
  mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
}

inline void Skybox::initVAO() {
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  mSampler->bind();
#endif
  mVAO->bind();

  mVBO->bind();
  mVBO->attributesSetForVAO();
  mVBO->setLoaded(GL_FALSE);
  mVBO->send();
  if (mIBO) {
    mIBO->bind();
    mIBO->setLoaded(GL_FALSE);
    mIBO->send();
  }
  flc::VertexArray::unbindVAO();
}

inline void Skybox::initVBO() {
  mVBO->initAttributes(mProgram->getHandle());
}

bool Skybox::getRenderItem(RenderItem &item) {
  item.mCount = mIBO ? mIBO->getElements() : mVBO->getElements();
  item.mDataType = GL_UNSIGNED_INT;
  item.mFirst = 0;
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  item.mHandles[RenderItem::eRenderHandleSampler] = 0;
#else
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
#endif
  item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->mTexture.mHandles[0]; //xxx 3d texture handle
  item.mIndicesPointer = 0;
  item.mMode = GL_TRIANGLES;
  item.mRenderStatus = mIBO ? 0xe0 : 0xa0; // vao, ibo, diff, norm, spec, blend, cont, anim
  return true;
}

} /* flf */
} /* flw */
