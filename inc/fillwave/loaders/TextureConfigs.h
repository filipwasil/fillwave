#pragma once

/*
* Copyright (c) 2017, Fillwave developers
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

#include "fillwave/OpenGL.h"

namespace flw {
namespace flc {

/*! \enum EMemoryAllocation
 * \brief Stores the type of memory free method
 */
enum class EMemoryAllocation {
  eMallock
  , eNew
  , eNone
};

/*! \class TextureConfig
* \brief Stores the single texture data
*/
struct TextureConfig final {
  /*! \class Header
  * \brief Stores the single file header info.
  */
  struct Header {
    Header(GLint internalFormat = GL_RGBA, GLint format = GL_RGBA, GLint type = GL_UNSIGNED_BYTE, GLsizei width = 0, GLsizei height = 0)
        : mInternalFormat(internalFormat)
        , mHeight(height)
        , mWidth(width)
        , mType(type)
        , mFormat(format) {
        // nothing
    }
    GLint mInternalFormat;
    GLsizei mHeight;
    GLsizei mWidth;
    GLenum mType;
    GLenum mFormat;
  };
  /*! \class Content
  * \brief Stores the single file info.
  */
  struct Content {
    Content(GLint level = 0,  GLint border = 0, GLboolean mipmaps = GL_FALSE, GLboolean compression = GL_FALSE)
        : mMipmapsLevel(level)
        , mMipmaps(mipmaps)
        , mCompression(compression)
        , mBorder(border)
        , mCompressionSize(0)
        , mCubeTarget(0) {
      // nothing
    }
    GLint mMipmapsLevel;
    GLboolean mMipmaps;
    GLboolean mCompression;
    GLint mBorder;
    GLsizei mCompressionSize;
    GLenum mCubeTarget;
  };

  TextureConfig()
      : mHeader()
      , mContent()
      , mCubeTarget()
      , mAllocation(EMemoryAllocation::eNone)
      , mData(nullptr) {
    // nothing
  }

  ~TextureConfig();

  Header mHeader;
  Content mContent;
  EMemoryAllocation mAllocation;
  GLenum mCubeTarget;
  GLubyte* mData;
};

} /* flc */
} /* flw */
