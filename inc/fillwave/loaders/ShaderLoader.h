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

#include <fillwave/OpenGL.h>
#include <string>

namespace flw {
namespace flf {

/*! \class ShaderLoader
 * \brief Loads shader sources.
 */

struct ShaderLoader {
/* Headers */
#if defined(FILLWAVE_GLES_3_0)
  const std::string mGLVersion = "#version 300 es\n";
#else /* defined(FILLWAVE_GLES_3_0) */
#if defined(FILLWAVE_COMPILATION_OPENGL_4_5)
  const std::string mGLVersion = "#version 450 core\n";
#else /* defined(FILLWAVE_COMPILATION_OPENGL_4_5) */
  const std::string mGLVersion = "#version 330 core\n";
#endif /* defined(FILLWAVE_COMPILATION_OPENGL_4_5) */
#endif /* defined(FILLWAVE_GLES_3_0) */
  const std::string mGLFragmentPrecision = "precision lowp float;\n";
  const std::string mGLVertexPrecision = "precision mediump float;\n";

  const std::string mGLVaryingIn = "in";
  const std::string mGLVaryingOut = "out";
};

} /* flf */
} /* flw */
