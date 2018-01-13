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

FLOGINIT("Texture3D", FERROR | FFATAL)

namespace flw {
namespace flc {

Texture3D::Texture3D(Texture2DFile *fileRight,
    Texture2DFile* fileLeft,
    Texture2DFile* fileCeil,
    Texture2DFile* fileFloor,
    Texture2DFile* fileFront,
    Texture2DFile* fileBack,
    ParameterList& parameters)
    : Texture(GL_TEXTURE_CUBE_MAP)
    , mRight(std::make_unique<Texture3DFile>(fileRight, GL_TEXTURE_CUBE_MAP_POSITIVE_X))
    , mLeft(std::make_unique<Texture3DFile>(fileLeft, GL_TEXTURE_CUBE_MAP_NEGATIVE_X))
    , mCeil(std::make_unique<Texture3DFile>(fileCeil, GL_TEXTURE_CUBE_MAP_POSITIVE_Y))
    , mFloor(std::make_unique<Texture3DFile>(fileFloor, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y))
    , mFront(std::make_unique<Texture3DFile>(fileFront, GL_TEXTURE_CUBE_MAP_POSITIVE_Z))
    , mBack(std::make_unique<Texture3DFile>(fileBack, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)) {
  bind();
  setParameters(parameters);
  sendData();
  unbind();
}

inline void Texture3D::sendData(flc::Texture3DFile* file, GLubyte* customData) {

  if (customData) {
    file->mFile2d.mData = customData;
  }

  fLogD("file->mCubeTarget ", file->mCubeTarget);
  fLogD("file->mConfig.mMipmapsLevel ", file->mFile2d.mConfig.mMipmapsLevel);
  fLogD("file->mHeader.mInternalFormat ", file->mFile2d.mHeader.mInternalFormat);
  fLogD("file->mHeader.mWidth ", file->mFile2d.mHeader.mWidth);
  fLogD("file->mHeader.mHeight ", file->mFile2d.mHeader.mHeight);
  fLogD("file->mConfig.mBorder ", file->mFile2d.mConfig.mBorder);
  fLogD("file->mHeader.mFormat ", file->mFile2d.mHeader.mFormat);
  fLogD("file->mHeader.mType ", file->mFile2d.mHeader.mType);
  glTexImage2D(file->mCubeTarget,
               file->mFile2d.mConfig.mMipmapsLevel,
               file->mFile2d.mHeader.mInternalFormat,
               file->mFile2d.mHeader.mWidth,
               file->mFile2d.mHeader.mHeight,
               file->mFile2d.mConfig.mBorder,
               file->mFile2d.mHeader.mFormat,
               file->mFile2d.mHeader.mType,
               (GLubyte *) file->mFile2d.mData);
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
