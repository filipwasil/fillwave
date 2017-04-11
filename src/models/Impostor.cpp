/*
 * Impostor.cpp
 *
 *  Created on: May 10, 2014
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


#include <fillwave/models/Impostor.h>
#include <fillwave/Fillwave.h>


namespace flw {
namespace flf {

Impostor::Impostor(Engine *engine,
    GLfloat lifetime,
    GLfloat size,
    flc::Texture *texture,
    GLenum blendingSource,
    GLenum blendingDestination)
    : Finishable(lifetime), mTexture(texture), mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT)), mSize(size) {
  mBlending.mSrc = blendingSource;
  mBlending.mDst = blendingDestination;
}

void Impostor::coreDraw() {
  if (mTexture) {
    mTexture->bind(FILLWAVE_DIFFUSE_UNIT);
  }

  glEnable(GL_BLEND);
  glBlendFunc(mBlending.mSrc, mBlending.mDst);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
