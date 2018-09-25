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

#include <flw/core/extended/texturing/Texture3D.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

Texture3D::Texture3D(
  TextureConfig* right
  , TextureConfig* left
  , TextureConfig* ceil
  , TextureConfig* floor
  , TextureConfig* front
  , TextureConfig* back
  , ParameterList& param)
  : mTexture(1)
  , mRight(right)
  , mLeft(left)
  , mCeil(ceil)
  , mFloor(floor)
  , mFront(front)
  , mBack(back)
  , mParameters(param) {
  bind();
  setParameters(mParameters);
  sendData();
  unbind();
}

inline void Texture3D::sendData(TextureConfig* cfg, GLubyte* customData) {

  if (customData) {
    cfg->mData = make_pu_with_no_ownership<GLubyte>(customData);
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
               cfg->mData.get());
  fLogC("send data");
}

void Texture3D::bind(GLuint id) {
  glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture.mHandles[id]);
  fLogC("bind (id) texture");
}

void Texture3D::bind(GLint textureUnit, GLuint id) {
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture.mHandles[id]);
  fLogC("bind (texUnit, id) texture");
}

void Texture3D::unbind() {
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  fLogC("unbind texture");
}

void Texture3D::setParameter(GLenum parameter, GLenum value) {
  glTexParameteri(GL_TEXTURE_CUBE_MAP, parameter, value);
  fLogC("setParameter");
}

void Texture3D::setParameters(ParameterList parameters) {
  for (auto it : parameters) {
    setParameter(it.first, it.second);
  }
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

void Texture3D::reload() {
  mTexture.reload();
  bind();
  setParameters(mParameters);
  sendData();
  unbind();
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
