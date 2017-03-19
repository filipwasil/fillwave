/*
 * Texture3DRenderable.h
 *
 *  Created on: Dec 1, 2014
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

#ifndef TEXTURE3DRENDERABLE_H_
#define TEXTURE3DRENDERABLE_H_

#include <fillwave/core/rendering/Texture2DRenderable.h>
#include <fillwave/core/texturing/Texture3D.h>

namespace fillwave {
namespace core {

/*! \class Texture3DRenderable
 * \brief One can render to this texture and use the rendered 6 images as a 2D texture.
 */

class Texture3DRenderable : public Texture3D {
public:
  Texture3DRenderable(Texture2DFile *filePosX,
      Texture2DFile *fileNegX,
      Texture2DFile *filePosY,
      Texture2DFile *fileNegY,
      Texture2DFile *filePosZ,
      Texture2DFile *fileNegZ,
      core::Texture2DRenderable *texture,
      ParameterList &parameters);

  virtual ~Texture3DRenderable() = default;

  void resize(GLint width, GLint height);

  void bindForWriting();

  void bindForRendering();

  void setAttachment(GLenum attachment);

  void setAttachmentFace(GLenum face, GLenum attachment);

  void log();

protected:
  core::Texture2DRenderable *mShadowTexture;
};

} /* core */
typedef std::shared_ptr<core::Texture3DRenderable> pTexture3DRenderable;
} /* fillwave */

#endif /* TEXTURE3DRENDERABLE_H_ */
