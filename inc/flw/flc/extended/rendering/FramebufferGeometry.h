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

#include <flw/flc/rendering/Framebuffer.h>
#include <flw/flc/texturing/Parameter.h>
#include <flw/flc/texturing/Texture2D.h>

namespace flw {
class Engine;
namespace flf {
class TextureSystem;
}
namespace flc {

/*! \class FramebufferGeometry
 * \brief Framebuffer with multiple color and depth attachments.
 */

class FramebufferGeometry : public Framebuffer {
public:
  FramebufferGeometry(flf::TextureSystem& textures,
      GLsizei width,
      GLsizei height,
      GLsizei colorBuffers);

  virtual ~FramebufferGeometry() = default;

  void bindAttachments();

  void setAttachments();

  void setAttachmentStencilDepth();

  void setAttachmentSummaryForReading();

  void setAttachmentSummaryForWriting();

  void resize(GLsizei width, GLsizei height);

  void reload();

private:

  std::vector<GLenum> mColorBuffers;

  flc::Texture2D* mDeferredColors;
  flc::Texture2D* mStencilDepth;
  flc::Texture2D* mSummary;

  const GLsizei mColorBufferSize;
  const GLsizei mSummaryBufferSize;

  const GLsizei mSummaryBuffer;
};

} /* flc */
} /* flw */
