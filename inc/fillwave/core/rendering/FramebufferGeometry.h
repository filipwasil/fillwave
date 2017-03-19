/*
 * FramebufferGeometry.h
 *
 *  Created on: 22 May 2015
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

#ifndef FRAMEBUFFERGEOMETRY_H_
#define FRAMEBUFFERGEOMETRY_H_

#include <fillwave/core/rendering/Framebuffer.h>
#include <fillwave/core/texturing/Parameter.h>
#include <fillwave/core/texturing/Texture2D.h>
#include <fillwave/management/TextureSystem.h>

namespace fillwave {
class Engine;
namespace core {

/*! \class FramebufferGeometry
 * \brief Framebuffer with multiple color and depth attachments.
 */

class FramebufferGeometry : public Framebuffer {
public:
  FramebufferGeometry(framework::TextureSystem *textures,
      GLuint width,
      GLuint height,
      GLuint colorBuffers,
      GLuint depthBuffers);

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

  core::Texture2D *mDeferredColors, *mStencilDepth, *mSummary;

  const GLint mColorBufferSize;
  const GLint mSummaryBufferSize;
  const GLint mDepthStencilBufferSize;

  const GLenum mSummaryBuffer;
  const GLenum mNone;
};

} /* core */
typedef std::shared_ptr<core::FramebufferGeometry> puFramebufferGeometry;
} /* fillwave */
#endif /* FRAMEBUFFERGEOMETRY_H_ */
