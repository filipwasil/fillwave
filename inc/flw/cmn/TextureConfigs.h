#pragma once

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

#include <flw/flf/loaders/textureloader/TextureContent.h>
#include <flw/OpenGL.h>
#include <flw/cmn/Containers.h>
#include <flw/cmn/Aliases.h>

namespace flw {
namespace flc {

/*! \class TextureConfig
* \brief Stores the single texture data
*/
struct TextureConfig final {
  /*! \class Header
  * \brief Stores the single file header info.
  */
  struct Header {
    Header(
      GLint internalFormat = GL_RGBA
      , GLint format = GL_RGBA
      , GLint type = GL_UNSIGNED_BYTE
      , GLsizei width = 0
      , GLsizei height = 0);
    GLint mInternalFormat;
    GLsizei mHeight;
    GLsizei mWidth;
    GLenum mType;
    GLenum mFormat;
    GLenum mCubeTarget;
  };

  struct Mipmap {
    Mipmap();
    Mipmap(unsigned int size, unsigned int height, unsigned int width, unsigned int format, GLubyte* data);
    GLsizei mSize;
    GLsizei mHeight;
    GLsizei mWidth;
    GLenum mFormat;
    pn<GLubyte> mData;
  };
  /*! \class Content
  * \brief Stores the single file info.
  */
  struct Content {
    Content(
      GLint level = 0
      ,  GLint border = 0
      , GLboolean mipmaps = GL_FALSE
      , GLboolean compression = GL_FALSE);
    GLint mMipmapsLevel;
    GLboolean mMipmaps;
    GLboolean mCompression;
    GLint mBorder;
    GLsizei mCompressionSize;
  };

  TextureConfig();

  ~TextureConfig();

  Header mHeader;
  Content mContent;
  EMemoryAllocation mAllocation;
  pn<GLubyte> mData;
  vecStack<Mipmap> mMipmaps;
};

} /* flc */
} /* flw */
