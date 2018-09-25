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

#include <flw/core/texturing/Texture2D.h>
#include <flw/Log.h>

FLOGINIT_MASK(FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture2D::Texture2D(TextureConfig* cfg, ParameterList &parameters, GLuint howMany)
  : mTexture(howMany)
  , mCfg(pu<TextureConfig>(cfg))
  , mParameters(parameters) {
  reload();
}

void Texture2D::sendData(GLubyte* data) {
  if (data) {
    mCfg->mData = make_pu_with_no_ownership<GLubyte>(data);
  }

  if (mCfg->mContent.mCompression) {

  } else {

  }

  for (auto& mipmap : mCfg->mMipmaps) {

  }
}

void Texture2D::generateMipMaps() {
  if (mCfg->mContent.mMipmaps) {

  }
}

void Texture2D::unbind2DTexture(GLint textureUnit) {

}

void Texture2D::unbind2DTextures() {

}

void Texture2D::reload() {
  mTexture.reload();
  for (GLsizei i = 0; i < mTexture.mHowMany; i++) {
    bind(i);
    setParameters(mParameters);
    sendData();
    generateMipMaps();
  }
}

void Texture2D::bind(GLuint id) {

}

void Texture2D::bind(GLint textureUnit, GLuint id) {

}

void Texture2D::unbind() {
}

void Texture2D::setParameter(GLenum parameter, GLenum value) {
}

void Texture2D::setParameters(ParameterList parameters) {
  for (auto it : parameters) {
    setParameter(it.first, it.second);
  }
}

void Texture2D::log() {

}

} /* flc */
} /* flw */
