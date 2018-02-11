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


#include <fillwave/core/rendering/Framebuffer.h>
#include <fillwave/core/texturing/Parameter.h>
#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/management/TextureSystem.h>

namespace flw {
class Engine;
namespace flc {

/*! \class FramebufferGeometry
 * \brief Framebuffer with multiple color and depth attachments.
 */

class FramebufferGeometry : public Framebuffer {
public:
  FramebufferGeometry(flf::TextureSystem &textures,
      GLuint width,
      GLuint height,
      GLuint colorBuffers);

  virtual ~FramebufferGeometry() = default;

  void bindAttachments();

  void setAttachments();

  void setAttachmentStencilDepth();

  void setAttachmentSummaryForReading();

  void setAttachmentSummaryForWriting();

  void resize(GLuint width, GLuint height);

  void reload();

private:

  std::vector<GLenum> mColorBuffers;

  flc::Texture2D *mDeferredColors;
  flc::Texture2D *mStencilDepth;
  flc::Texture2D *mSummary;

  const GLint mColorBufferSize;
  const GLint mSummaryBufferSize;

  const GLenum mSummaryBuffer;
};

} /* flc */
typedef std::shared_ptr<flc::FramebufferGeometry> puFramebufferGeometry;
} /* flw */
