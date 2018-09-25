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

#include <flw/OpenGL.h>
#include <flw/flc/pipeline/Blending.h>

namespace flw {
namespace flf {
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
      GLubyte bVAO : 1;
      GLubyte bIndexDraw : 1;
      GLubyte bDiffuse : 1;
      GLubyte bNormal : 1;
      GLubyte bSpecular : 1;
      GLubyte bBlending : 1;
      GLubyte bIsContainer : 1;
      GLubyte bIsAnimated : 1;
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

} /* flf */
} /* flw */
