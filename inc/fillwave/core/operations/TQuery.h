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

#include <fillwave/core/base/GLObject.h>

namespace flw {
namespace flc {

/*! \class TQuery
 * \brief GLObject to ask OpenGL questions.
 */

template <GLenum TARGET>
class TQuery final {
public:
  TQuery(GLuint howMany = 1);

  ~TQuery();

  void begin(GLuint id = 0);

  void end();

  GLuint getID(GLuint id = 0) const;

  GLuint getResultSync(GLuint id = 0);

  GLuint getResultAsync(GLuint resultIfNotAvailable, GLuint id = 0);

  GLboolean getResultAvailable(GLuint id = 0);

  void reload();

  void log();

 protected:
  GLsizei mHowMany;
  GLuint mHandles[FILLWAVE_GLOBJECTS_MAX];
};

#if defined(FILLWAVE_BACKEND_OPENGL_ES_20)


#elif defined(FILLWAVE_BACKEND_OPENGL_ES_30)

using QueryIfAnySamplesPassed = TQuery<GL_ANY_SAMPLES_PASSED>;
using QueryHowManyTransformFeedbackPrimitivesWritten = TQuery<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN>;

#else

using QueryHowManySamplesPassed = TQuery<GL_SAMPLES_PASSED>;
using QueryHowManyPrimitivesGeneratedByGeometryShader = TQuery<GL_PRIMITIVES_GENERATED>;
using QueryTimeElapsed = TQuery<GL_TIME_ELAPSED>;

#endif

} /* flc */
} /* flw */
