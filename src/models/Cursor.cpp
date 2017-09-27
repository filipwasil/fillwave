/*
 * Cursor.cpp
 *
 *  Created on: Nov 6, 2014
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


#include <fillwave/models/Cursor.h>
#include <fillwave/loaders/ProgramLoader.h>
#include <fillwave/Fillwave.h>
#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flf {

Cursor::Cursor(Engine *engine, flc::Texture *texture)
    : mTexture(texture)
    , mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT))
    , mSize(0.06f)
    , mScreenFactor(static_cast<GLfloat>(engine->getScreenSize()[0]) / static_cast<GLfloat>(engine->getScreenSize()[1])) {

  mBlending.mSrc = GL_SRC_ALPHA;
  mBlending.mDst = GL_ONE_MINUS_SRC_ALPHA;

  mProgram = ProgramLoader(engine).getProgram(EProgram::cursor);

  initUniformsCache();
}

void Cursor::move(glm::vec2 position) {
  mProgram->use();
  flc::Uniform::push(mULCPosition, position);
  flc::Program::disusePrograms();
}

void Cursor::redraw() {
  mProgram->use();

  flc::Uniform::push(mULCScreenFactor, mScreenFactor);
  flc::Uniform::push(mULCSize, mSize);

  coreDraw();

  flc::Program::disusePrograms();
}

void Cursor::initUniformsCache() {
  mULCPosition = mProgram->getUniformLocation("uPosition");
  mULCScreenFactor = mProgram->getUniformLocation("uScreenFactor");
  mULCTextureUnit = mProgram->getUniformLocation("uTextureUnit");
  mULCSize = mProgram->getUniformLocation("uSize");

  mProgram->use();
  flc::Uniform::push(mULCTextureUnit, FILLWAVE_DIFFUSE_UNIT);
  flc::Program::disusePrograms();
}

void Cursor::coreDraw() {
  if (mTexture) {
    mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
  }

  glEnable(GL_BLEND);
  glBlendFunc(mBlending.mSrc, mBlending.mDst);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  fLogC("Drawing impostor failed");
  glDisable(GL_BLEND);
  flc::Texture2D::unbind2DTextures();
}

bool Cursor::getRenderItem(RenderItem &item) {
  item.mBlend = mBlending;
  item.mCount = 4;
  item.mDataType = GL_NONE;
  item.mFirst = 0;
  item.mHandles[RenderItem::eRenderHandleProgram] = mProgram->getHandle();
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
  item.mHandles[RenderItem::eRenderHandleVAO] = 0;
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->getHandle();
  item.mHandles[RenderItem::eRenderHandleNormal] = 0;
  item.mHandles[RenderItem::eRenderHandleSpecular] = 0;
  item.mIndicesPointer = 0;
  item.mMode = GL_TRIANGLE_STRIP;
  item.mStatus.bBlending = 1;
  item.mRenderStatus = 0x24; // blending, diffuse
  return true;
}

} /* flf */
} /* flw */
