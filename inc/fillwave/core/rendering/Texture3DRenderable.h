#pragma once

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Filip Wasil and Fillwave community members
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fillwave/core/base/rendering/Texture2DRenderable.h>
#include <fillwave/core/extended/texturing/Texture3D.h>

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
