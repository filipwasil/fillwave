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

#include <fillwave/core/GLObject.h>

namespace flw {
namespace flc {

/*! \class TQuery
 * \brief GLObject to ask OpenGL questions.
 */

template <GLenum TARGET>
class TQuery final : public GLObject {
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
};

using QueryIfAnySamplesPassed = TQuery<GL_ANY_SAMPLES_PASSED>;
using QueryHowManyTransformFeedbackPrimitivesWritten = TQuery<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN>;

#ifdef FILLWAVE_GLES_3_0
#else

using QueryHowManySamplesPassed = TQuery<GL_SAMPLES_PASSED>;
using QueryHowManyPrimitivesGeneratedByGeometryShader = TQuery<GL_PRIMITIVES_GENERATED>;
using QueryTimeElapsed = TQuery<GL_TIME_ELAPSED>;

#endif

} /* flc */
} /* flw */
