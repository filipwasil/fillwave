/*
 * Skybox.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: filip
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


#include <fillwave/models/Skybox.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/models/shapes/SphereSkybox.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT("Skybox", FERROR | FFATAL)

namespace flw {
namespace flf {

Skybox::Skybox(Engine *engine, flc::Texture3D *texture)
    : IReloadable(engine), mTexture(texture) {

  ProgramLoader loader(engine);

  mProgram = loader.getSkybox();
  mProgramDR = loader.getSkyboxDR();

  SphereSkybox sphere(1.0, 10, 10);

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
  mSampler->bind();
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
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
  item.mHandles[RenderItem::eRenderHandleVAO] = mVAO->getHandle();
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->getHandle(); //xxx 3d texture handle
  item.mIndicesPointer = 0;
  item.mMode = GL_TRIANGLES;
  item.mRenderStatus = mIBO ? 0xe0 : 0xa0; // vao, ibo, diff, norm, spec, blend, cont, anim
  return true;
}

} /* flf */
} /* flw */
