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

#include <flw/flc/texturing/Texture2D.h>
#include <flw/Log.h>

FLOGINIT_MASK(FERROR | FFATAL | FDEBUG)

namespace flw {
namespace flc {

Texture2D::Texture2D(TextureConfig* cfg, ParameterList &parameters, GLuint howMany)
  : mTexture(howMany)
  , mCfg(pu<TextureConfig>(cfg))
  , mParameters(parameters) {
  glGenTextures(mTexture.mHowMany, mTexture.mHandles);
  for (GLsizei i = 0; i < mTexture.mHowMany; i++) {
    bind(i);
    setParameters(mParameters);
    sendData();
    generateMipMaps();
  }
}

void Texture2D::sendData(GLubyte* data) {
  if (data) {
    mCfg->mData = make_pu_with_no_ownership<GLubyte>(data);
  }

  if (mCfg->mContent.mCompression) {
    glCompressedTexImage2D(GL_TEXTURE_2D,
                           mCfg->mContent.mMipmapsLevel,
                           mCfg->mHeader.mInternalFormat,
                           mCfg->mHeader.mWidth,
                           mCfg->mHeader.mHeight,
                           mCfg->mContent.mBorder,
                           mCfg->mContent.mCompressionSize,
                           mCfg->mData.get());
    fLogC("send compressed texture data");
  } else {
    glTexImage2D(GL_TEXTURE_2D,
                 mCfg->mContent.mMipmapsLevel,
                 mCfg->mHeader.mInternalFormat,
                 mCfg->mHeader.mWidth,
                 mCfg->mHeader.mHeight,
                 mCfg->mContent.mBorder,
                 mCfg->mHeader.mFormat,
                 mCfg->mHeader.mType,
                 mCfg->mData.get());
    fLogC("send uncompressed texture data");
  }

  size_t id = 1;
  for (auto& mipmap : mCfg->mMipmaps) {
    glCompressedTexImage2D(
      GL_TEXTURE_2D
      , id++
      , mipmap.mFormat
      , mipmap.mWidth
      , mipmap.mHeight
      , 0
      , mipmap.mSize
      , mipmap.mData.get());
  }
  fLogC("send mipmap data");
}

void Texture2D::generateMipMaps() {
  if (mCfg->mContent.mMipmaps) {
    glGenerateMipmap(GL_TEXTURE_2D);
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
  mTexture.reload();
  for (GLsizei i = 0; i < mTexture.mHowMany; i++) {
    bind(i);
    setParameters(mParameters);
    sendData();
    generateMipMaps();
  }
}

void Texture2D::bind(GLuint id) {
  glBindTexture(GL_TEXTURE_2D, mTexture.mHandles[id]);
  fLogC("bind (id) texture");
}

void Texture2D::bind(GLint textureUnit, GLuint id) {
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_2D, mTexture.mHandles[id]);
  fLogC("bind (texUnit, id) texture");
}

void Texture2D::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
  fLogC("unbind texture");
}

void Texture2D::setParameter(GLenum parameter, GLenum value) {
  glTexParameteri(GL_TEXTURE_2D, parameter, value);
  fLogC("setParameter");
}

void Texture2D::setParameters(ParameterList parameters) {
  for (auto it : parameters) {
    setParameter(it.first, it.second);
  }
}

void Texture2D::log() {
  fLogD("mTarget: GL_TEXTURE_2D");
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
