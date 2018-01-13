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

Texture2D::Texture2D(Texture2DFile *file, ParameterList &parameters, GLuint howMany)
    : Texture(GL_TEXTURE_2D, howMany)
    , mFile(puTexture2DFile(file))
    , mParameters(parameters) {
  reload();
}

void Texture2D::sendData(GLubyte* data) {
  if (data) {
    mFile->mData = data;
  }
  if (mFile->mConfig.mCompression) {
    glCompressedTexImage2D(mTarget,
                           mFile->mConfig.mMipmapsLevel,
                           mFile->mHeader.mInternalFormat,
                           mFile->mHeader.mWidth,
                           mFile->mHeader.mHeight,
                           mFile->mConfig.mBorder,
                           mFile->mConfig.mCompressionSize,
                           (GLubyte *) mFile->mData);
  } else {
    glTexImage2D(mTarget,
                 mFile->mConfig.mMipmapsLevel,
                 mFile->mHeader.mInternalFormat,
                 mFile->mHeader.mWidth,
                 mFile->mHeader.mHeight,
                 mFile->mConfig.mBorder,
                 mFile->mHeader.mFormat,
                 mFile->mHeader.mType,
                 (GLubyte *) mFile->mData);
  }
  fLogC("send data");
}

void Texture2D::generateMipMaps() {
  if (mFile->mConfig.mMipmaps) {
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
  fLogD("mFile->mConfig.mMipmapsLevel: %d", mFile->mConfig.mMipmapsLevel);
  fLogD("mFile->mHeader.mInternalFormat: 0x%x", mFile->mHeader.mInternalFormat);
  fLogD("mFile->mHeader.mWidth: %d", mFile->mHeader.mWidth);
  fLogD("mFile->mHeader.mHeight: %d", mFile->mHeader.mHeight);
  fLogD("mFile->mConfig.mBorder: %d", mFile->mConfig.mBorder);
  fLogD("mFile->mConfig.mType: 0x%x", mFile->mHeader.mType);
  fLogD("mFile->mHeader.mFormat: 0x%x", mFile->mHeader.mFormat);
}

} /* flc */
} /* flw */
