/*
 * Copyright (c) 2018, Fillwave developers
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

#include <fillwave/core/texturing/Texture3D.h>
#include <fillwave/Log.h>

FLOGINIT("Texture3D", FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture3D::Texture3D(TextureConfig* right, TextureConfig* left, TextureConfig* ceil, TextureConfig* floor, TextureConfig* front, TextureConfig* back, ParameterList& param)
    : Texture(GL_TEXTURE_CUBE_MAP)
    , mRight(right)
    , mLeft(left)
    , mCeil(ceil)
    , mFloor(floor)
    , mFront(front)
    , mBack(back) {
  bind();
  setParameters(param);
  sendData();
  unbind();
}

inline void Texture3D::sendData(TextureConfig* cfg, GLubyte* customData) {

  if (customData) {
    cfg->mData = customData;
  }

  fLogD("cfg->mHeader->mCubeTarget ", cfg->mHeader.mCubeTarget);
  fLogD("cfg->mContent.mMipmapsLevel ", cfg->mContent.mMipmapsLevel);
  fLogD("cfg->mHeader.mInternalFormat ", cfg->mHeader.mInternalFormat);
  fLogD("cfg->mHeader.mWidth ", cfg->mHeader.mWidth);
  fLogD("cfg->mHeader.mHeight ", cfg->mHeader.mHeight);
  fLogD("cfg->mContent.mBorder ", cfg->mContent.mBorder);
  fLogD("cfg->mHeader.mFormat ", cfg->mHeader.mFormat);
  fLogD("cfg->mHeader.mType ", cfg->mHeader.mType);
  glTexImage2D(cfg->mHeader.mCubeTarget,
               cfg->mContent.mMipmapsLevel,
               cfg->mHeader.mInternalFormat,
               cfg->mHeader.mWidth,
               cfg->mHeader.mHeight,
               cfg->mContent.mBorder,
               cfg->mHeader.mFormat,
               cfg->mHeader.mType,
               (GLubyte *) cfg->mData);
  fLogC("send data");
}

void Texture3D::sendData() {
  sendData(mRight.get());
  sendData(mLeft.get());
  sendData(mCeil.get());
  sendData(mFloor.get());
  sendData(mFront.get());
  sendData(mBack.get());
}

void Texture3D::unbindCubemapTextures() {
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::unbindCubemapTexture(GLint textureUnit) {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::log() {
  // nothing
}

void Texture3D::sendData(GLubyte* xp, GLubyte* xn, GLubyte* yp, GLubyte* yn, GLubyte* zp, GLubyte* zn) {

  sendData(mRight.get(), xp);
  sendData(mLeft.get(), xn);
  sendData(mCeil.get(), yp);
  sendData(mFloor.get(), yn);
  sendData(mFront.get(), zp);
  sendData(mBack.get(), zn);

  fLogC("send data");
}

} /* flc */
} /* flw */
