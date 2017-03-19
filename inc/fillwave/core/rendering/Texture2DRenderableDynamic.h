/*
 * Texture2DRenderableDynamic.h
 *
 *  Created on: Dec 3, 2014
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

#ifndef TEXTURE2DRENDERABLEDYNAMIC_H_
#define TEXTURE2DRENDERABLEDYNAMIC_H_

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/pipeline/Program.h>

namespace fillwave {
namespace core {

/*! \class Texture2DRenderableDynamic
 * \brief Dynamic texture will update its content during runtime according to specified fragment shader.
 */

class Texture2DRenderableDynamic : public Texture2DRenderable {
public:
  Texture2DRenderableDynamic(Texture2DFile *file, ParameterList &parameters, core::Program *program);

  virtual ~Texture2DRenderableDynamic() = default;

  void draw(GLfloat timePassed);

  void reload();

private:
  core::Program *mProgram;

  GLfloat mTimePassed;
  GLint mUniformLocationCacheTime;
  GLint mUniformLocationCachePostprocessingSampler;

  void initUniformsCache();
};

} /* core */
typedef std::shared_ptr<core::Texture2DRenderableDynamic> pTexture2DRenderableDynamic;
} /* fillwave */

#endif /* TEXTURE2DRENDERABLEDYNAMIC_H_ */
