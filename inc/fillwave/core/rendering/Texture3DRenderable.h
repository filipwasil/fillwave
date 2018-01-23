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

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/texturing/Texture3D.h>

namespace flw {
namespace flc {

/*! \class Texture3DRenderable
 * \brief One can render to this texture and use the rendered 6 images as a 2D texture.
 */

class Texture3DRenderable : public Texture3D {
public:
  Texture3DRenderable(TextureConfig* posX, TextureConfig* negX, TextureConfig* posY, TextureConfig* nY, TextureConfig* pZ, TextureConfig* nZ, Texture2DRenderable* text, ParameterList &param);

  virtual ~Texture3DRenderable() = default;

  void resize(GLint width, GLint height);

  void bindForWriting();

  void bindForRendering();

  void setAttachment(GLenum attachment);

  void setAttachmentFace(GLenum face, GLenum attachment);

  void log();

protected:
  flc::Texture2DRenderable *mShadowTexture;
};

} /* flc */
} /* flw */
