/*
 * RenderData.h
 *
 *  Created on: Jan 24, 2016
 *      Author: filip
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

#ifndef INC_FILLWAVE_MODELS_BASE_RENDERITEM_H_
#define INC_FILLWAVE_MODELS_BASE_RENDERITEM_H_

#include <fillwave/OpenGL.h>
#include <fillwave/core/pipeline/Blending.h>

namespace fillwave {
namespace framework {
/*! \struct RenderItem
 * \brief Single draw item structure
 */

struct RenderItem {
  enum eRenderHandles {
    eRenderHandleProgram
    , eRenderHandleVAO
    , eRenderHandleDiffuse
    , eRenderHandleNormal
    , eRenderHandleSpecular
    , eRenderHandleSampler
    , eRenderHandlesSize
  };

  union {
    GLubyte mRenderStatus;
    struct {
      GLubyte bVAO
          : 1;
      GLubyte bIndexDraw
          : 1;
      GLubyte bDiffuse
          : 1;
      GLubyte bNormal
          : 1;
      GLubyte bSpecular
          : 1;
      GLubyte bBlending
          : 1;
      GLubyte bIsContainer
          : 1;
      GLubyte bIsAnimated
          : 1;
    } mStatus;
  };

  GLenum mMode;
  GLsizei mFirst;
  GLsizei mCount;
  GLenum mDataType;
  GLint mIndicesPointer;
  Blending mBlend;
  GLuint mHandles[eRenderHandlesSize];
};

} /* namespace framework */
} /* namespace fillwave */

#endif /* INC_FILLWAVE_MODELS_BASE_RENDERITEM_H_ */
