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

/*! \class Texture2DFileConfig
 * \brief Stores the single file configuration info.
 */
class Texture2DFileConfig {
public:
  Texture2DFileConfig(
      GLint level = 0,
      GLint border = 0,
      GLboolean mipmaps = GL_FALSE,
      GLboolean compression = GL_FALSE);

  GLint mMipmapsLevel;
  GLboolean mMipmaps;
  GLboolean mCompression;
  GLint mBorder;
  GLsizei mCompressionSize;
};

/*! \class Texture2DFileHeader
 * \brief Stores the single file header info.
 */
class Texture2DFileHeader {
public:
  Texture2DFileHeader(
      GLint internalFormat = GL_RGBA,
      GLint format = GL_RGBA,
      GLint type = GL_UNSIGNED_BYTE,
      GLsizei width = 0,
      GLsizei height = 0);

  GLint mInternalFormat;
  GLsizei mHeight;
  GLsizei mWidth;
  GLenum mType;
  GLenum mFormat;
};

/*! \enum eMemoryAllocation
 * \brief Stores the type of memory free method
 */

enum class eMemoryAllocation {
  eMallock
  , eNew
  , eNone
};

/*! \class Texture2DFile
 * \brief Stores the single file info.
 */

class Texture2DFile {
public:
  Texture2DFileHeader mHeader;
  Texture2DFileConfig mConfig;
  GLubyte* mData;
  eMemoryAllocation mAllocation = eMemoryAllocation::eNone;

  virtual ~Texture2DFile();
};

/*! \class Texture3DFile
 * \brief Stores the single file info.
 */

class Texture3DFile : public Texture2DFile {
public:
  GLenum mCubeTarget;

  Texture3DFile(Texture2DFile *file, GLenum target)
      : mCubeTarget(target) {
    mHeader = file->mHeader;
    mConfig = file->mConfig;
    mData = file->mData;
  }
};

} /* flc */
} /* flw */
