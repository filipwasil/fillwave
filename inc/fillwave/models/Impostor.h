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

#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/core/texturing/Sampler.h>
#include <fillwave/core/pipeline/Program.h>
#include <fillwave/common/Finishable.h>
#include <fillwave/models/Entity.h>

namespace flw {
class Engine;
namespace flf {

/*! \class Impostor
 * \brief Drawable Entity built by fragment shader. Time limited.
 */

class Impostor : public Entity, public Finishable {
public:
  Impostor(Engine *engine,
      GLfloat lifetime,
      GLfloat size,
      flc::Texture *texture = nullptr,
      GLenum blendingSource = GL_SRC_ALPHA,
      GLenum blendingDestination = GL_ONE_MINUS_SRC_ALPHA);

  virtual ~Impostor() = default;

protected:
  flc::Program *mProgram;
  flc::Texture *mTexture;
  flc::Sampler *mSampler;
  GLfloat mSize;
  Blending mBlending;

  void coreDraw();
};

} /* flf */
typedef std::unique_ptr<flf::Impostor> pImpostor;
} /* flw */
