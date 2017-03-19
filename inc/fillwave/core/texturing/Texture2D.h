/*
 * Texture.h
 *
 *  Created on: 28 Mar 2014
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
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

#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include <fillwave/core/texturing/Texture.h>

namespace fillwave {
namespace core {

/*! \class Texture2D
 * \brief Single GLSL 2D Texture object.
 */

class Texture2D : public Texture {
public:
  Texture2D(Texture2DFile *file, ParameterList &parameters, GLuint howMany = 1);

  virtual ~Texture2D() = default;

  void generateMipMaps();

  void sendData(Texture2DFileData data = nullptr);

  virtual void reload();

  void log();

  static void unbind2DTexture(GLint textureUnit);

  static void unbind2DTextures();

  puTexture2DFile mFile;

protected:
  ParameterList mParameters;
};

} /* core */
typedef std::shared_ptr<core::Texture2D> pTexture2D;
} /* fillwave */

#endif /* TEXTURE_2D_H_ */
