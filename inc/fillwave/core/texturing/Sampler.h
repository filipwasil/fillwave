/*
 * Sampler.h
 *
 *  Created on: Mar 30, 2014
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

#ifndef SAMPLER_H_
#define SAMPLER_H_

#include <fillwave/core/GLObject.h>
#include <fillwave/core/texturing/Parameter.h>
#include <memory>

namespace fillwave {
namespace core {

/*! \class Sampler
 * \brief SamplerObject - SO.
 */
class Sampler : public GLObject {
public:
  Sampler(GLint textureUnit, GLuint howMany = 1);

  virtual ~Sampler();

  void bind(GLuint id = 0);

  void unbind(GLuint id = 0);

  void setParameters(ParameterList parameters);

  void setParameter(GLenum parameter, GLenum value, GLuint id = 0);

  void setParameter(Parameter parameter, GLuint id = 0);

  void reload();

  GLint getTextureUnit();

private:
  GLint mTextureUnit;
};

} /* core */
} /* fillwave */

#endif /* SAMPLER_H_ */
