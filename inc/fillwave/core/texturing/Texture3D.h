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

#include <fillwave/core/texturing/Texture.h>
#include <fillwave/loaders/TextureFiles.h>

namespace flw {
namespace flc {

/*! \class Texture3D
 * \brief Single GLSL 3D Texture object.
 * It consists of six 2D images.
 */

using puTexture3DFile = std::unique_ptr<flc::Texture3DFile>;

class Texture3D : public Texture {
private:
  void sendData(Texture3DFile* file, GLubyte* customData = nullptr);

public:
  puTexture3DFile mRight; /* Positive X*/
  puTexture3DFile mLeft; /* Negative X*/
  puTexture3DFile mCeil; /* Positive Y*/
  puTexture3DFile mFloor; /* Negative Y*/
  puTexture3DFile mFront; /* Positive Z*/
  puTexture3DFile mBack; /* Negative Z*/

  Texture3D(Texture2DFile *fileRight,
      Texture2DFile *fileLeft,
      Texture2DFile *fileCeil,
      Texture2DFile *fileFloor,
      Texture2DFile *fileFront,
      Texture2DFile *fileBack,
      ParameterList &parameters);

  virtual ~Texture3D() = default;

  void sendData();

  void log();

  static void unbindCubemapTexture(GLint textureUnit);

  static void unbindCubemapTextures();

  void sendData(GLubyte* xp,
      GLubyte* xn,
      GLubyte* yp,
      GLubyte* yn,
      GLubyte* zp,
      GLubyte* zn);
};

} /* flc */
typedef std::shared_ptr<flc::Texture3D> pTexture3D;
} /* flw */
