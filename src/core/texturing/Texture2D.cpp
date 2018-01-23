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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/Log.h>

FLOGINIT_MASK(FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture2D::Texture2D(TextureConfig* cfg, ParameterList &parameters, GLuint howMany)
    : Texture(GL_TEXTURE_2D, howMany)
    , mCfg(pu<TextureConfig>(cfg))
    , mParameters(parameters) {
  reload();
}

void Texture2D::sendData(GLubyte* data) {
  if (data) {
    mCfg->mData = data;
  }
  if (mCfg->mContent.mCompression) {
    glCompressedTexImage2D(mTarget,
                           mCfg->mContent.mMipmapsLevel,
                           mCfg->mHeader.mInternalFormat,
                           mCfg->mHeader.mWidth,
                           mCfg->mHeader.mHeight,
                           mCfg->mContent.mBorder,
                           mCfg->mContent.mCompressionSize,
                           (GLubyte *) mCfg->mData);
  } else {
    glTexImage2D(mTarget,
                 mCfg->mContent.mMipmapsLevel,
                 mCfg->mHeader.mInternalFormat,
                 mCfg->mHeader.mWidth,
                 mCfg->mHeader.mHeight,
                 mCfg->mContent.mBorder,
                 mCfg->mHeader.mFormat,
                 mCfg->mHeader.mType,
                 (GLubyte *) mCfg->mData);
  }
  fLogC("send data");
}

void Texture2D::generateMipMaps() {
  if (mCfg->mContent.mMipmaps) {
    glGenerateMipmap(mTarget);
    fLogC("generateMipMaps");
  }
}

void Texture2D::unbind2DTexture(GLint textureUnit) {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::unbind2DTextures() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::reload() {
  fLogD("Reload");
  Texture::reload();
  for (GLsizei i = 0; i < mHowMany; i++) {
    bind(i);
    setParameters(mParameters);
    sendData();
    generateMipMaps();
  }
}

void Texture2D::log() {
  fLogD("mTarget: 0x%x", mTarget);
  fLogD("mCfg->mContent.mMipmapsLevel: %d", mCfg->mContent.mMipmapsLevel);
  fLogD("mCfg->mHeader.mInternalFormat: 0x%x", mCfg->mHeader.mInternalFormat);
  fLogD("mCfg->mHeader.mWidth: %d", mCfg->mHeader.mWidth);
  fLogD("mCfg->mHeader.mHeight: %d", mCfg->mHeader.mHeight);
  fLogD("mCfg->mContent.mBorder: %d", mCfg->mContent.mBorder);
  fLogD("mCfg->mContent.mType: 0x%x", mCfg->mHeader.mType);
  fLogD("mCfg->mHeader.mFormat: 0x%x", mCfg->mHeader.mFormat);
}

} /* flc */
} /* flw */
