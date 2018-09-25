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

#include <flw/flc/extended/texturing/Texture3D.h>
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
}

void Texture3D::bind(GLuint id) {

}

void Texture3D::bind(GLint textureUnit, GLuint id) {

}

void Texture3D::unbind() {

}

void Texture3D::setParameter(GLenum parameter, GLenum value) {

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

}

void Texture3D::unbindCubemapTexture(GLint textureUnit) {

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
}

} /* flc */
} /* flw */
