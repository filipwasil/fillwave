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

#include "fillwave/loaders/TextureFiles.h"
#include <cstdlib>

namespace flw {
namespace flc {

Texture2DFileConfig::Texture2DFileConfig(GLint level,
    GLint border,
    GLboolean mipmaps,
    GLboolean compression)
    : mMipmapsLevel(level)
    , mMipmaps(mipmaps)
    , mCompression(compression)
    , mBorder(border)
    , mCompressionSize(0) {

}


Texture2DFileHeader::Texture2DFileHeader(GLint internalFormat,
    GLint format,
    GLint type,
    GLsizei width,
    GLsizei height)
    : mInternalFormat(internalFormat)
    , mHeight(height)
    , mWidth(width)
    , mType(type)
    , mFormat(format) {

}

Texture2DFile::~Texture2DFile() {
  switch (mAllocation) {
    case EMemoryAllocation::eMallock:
      free(mData);
      break;
    case EMemoryAllocation::eNew:
      delete mData;
      mData = nullptr;
      break;
    case EMemoryAllocation::eNone:
      break;
  }
}

} /* flc */
} /* flw */
