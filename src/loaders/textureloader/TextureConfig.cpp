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

#include <fillwave/loaders/textureloader/TextureConfigs.h>

#include <cstdlib>

namespace flw {
namespace flc {

TextureConfig::TextureConfig()
  : mHeader()
  , mContent()
  , mAllocation(EMemoryAllocation::none)
  , mData(make_pu_with_no_ownership<GLubyte>(nullptr))
  , mMipmaps() {
  // nothing
}

TextureConfig::Mipmap::Mipmap()
  : mSize(0)
  , mHeight(0)
  , mWidth(0)
  , mFormat(0)
  , mData(make_pu_with_no_ownership<GLubyte>(nullptr)) {
  // nothing
}

TextureConfig::Mipmap::Mipmap(unsigned int size, unsigned int height, unsigned int width, unsigned int format, GLubyte* data)
  : mSize(size)
  , mHeight(height)
  , mWidth(width)
  , mFormat(format)
  , mData(make_pu_with_no_ownership<GLubyte>(data)) {
  // nothing
}

TextureConfig::Content::Content(
  GLint level
  , GLint border
  , GLboolean mipmaps
  , GLboolean compression)
  : mMipmapsLevel(level)
  , mMipmaps(mipmaps)
  , mCompression(compression)
  , mBorder(border)
  , mCompressionSize(0) {
  // nothing
}

TextureConfig::Header::Header(
  GLint internalFormat
, GLint format
, GLint type
, GLsizei width
, GLsizei height)
    : mInternalFormat(internalFormat)
    , mHeight(height)
    , mWidth(width)
    , mType(type)
    , mFormat(format)
    , mCubeTarget(0) {
    // nothing
  }


TextureConfig::~TextureConfig() {
  switch (mAllocation) {
  case EMemoryAllocation::cstyle:
    free(mData.get());
    break;
  case EMemoryAllocation::standard:
    delete mData.get();
    mData = make_pu_with_no_ownership<GLubyte>(nullptr);
    break;
 case EMemoryAllocation::none:
    break;
  }
}

} /* flc */
} /* flw */
