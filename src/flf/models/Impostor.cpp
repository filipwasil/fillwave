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

#include <flw/flf/models/Impostor.h>
#include <flw/Fillwave.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()


namespace flw {
namespace flf {

Impostor::Impostor(
  Engine *engine
  , GLfloat lifetime
  , GLfloat size
  , flc::Texture2D* texture
  , flc::Program* program
  , GLenum blendingSource
  , GLenum blendingDestination)
  : Finishable(lifetime)
  , mEngine(engine)
  , mTexture(texture)
  , mProgram(program)
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
#else
  , mSampler(engine->storeSO(FILLWAVE_DIFFUSE_UNIT))
#endif
  , mSize(size) {
  mBlending.mSrc = blendingSource;
  mBlending.mDst = blendingDestination;
}

Impostor::~Impostor() = default;

void Impostor::coreDraw() {
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
#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)
  item.mHandles[RenderItem::eRenderHandleSampler] = 0;
#else
  item.mHandles[RenderItem::eRenderHandleSampler] = mSampler->getHandle();
#endif
  item.mHandles[RenderItem::eRenderHandleVAO] = 0;
  item.mHandles[RenderItem::eRenderHandleDiffuse] = mTexture->mTexture.mHandles[0];
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
