/*
 * Query.cpp
 *
 *  Created on: May 17, 2015
 *      Author: filip
 *
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


#include <fillwave/core/operations/TQuery.h>
#include <fillwave/Log.h>

FLOGINIT("Query", FERROR | FFATAL | FINFO)

namespace flw {
namespace flc {

template <GLenum target>
TQuery<target>::TQuery(GLsizei howMany)
    :
    GLObject(howMany) {
  glGenQueries(mHowMany, mHandles);
  fLogC("Could not create query");
}

template <GLenum target>
TQuery<target>::~TQuery() {
  glDeleteQueries(mHowMany, mHandles);
  fLogC("Could not delete query");
}

template <GLenum target>
GLuint TQuery<target>::getID(GLuint id) const {
  return mHandles[id];
}

template <GLenum target>
void TQuery<target>::begin(GLuint id) {
  glBeginQuery(mTarget, mHandles[id]);
  fLogC("Could not begin query");
}

template <GLenum target>
void TQuery<target>::end() {
  glEndQuery(mTarget);
  fLogC("Could not end query");
}

template <GLenum target>
GLuint TQuery<target>::getResultAsync(GLuint resultIfNotAvailable, GLuint id) {
  GLuint result;
  glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
  fLogC("Could not get querry result state");
  if (result) {
    glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
    fLogC("Could not get query async result");
    return result;
  } else {
    return resultIfNotAvailable;
  }
}

template <GLenum target>
GLuint TQuery<target>::getResultSync(GLuint id) {
  GLuint result;
  glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
  fLogC("Could not get querry sync result");
  return result;
}

template <GLenum target>
GLboolean TQuery<target>::getResultAvailable(GLuint id) {
  GLuint result;
  glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
  return result ? GL_TRUE : GL_FALSE;
}

template <GLenum target>
void TQuery<target>::reload() {
  glGenQueries(mHowMany, mHandles);
  fLogC("reload");
}

template <GLenum target>
void TQuery<target>::log() {
  for (GLsizei id = 0; id < mHowMany; id++) {
    if (glIsQuery(mHandles[id])) {
      fLogI("Query %d exists", mHandles[id]);
    } else {
      fLogI("Query %d does not exist", mHandles[id]);
    }
  }
}

template
class TQuery<GL_ANY_SAMPLES_PASSED>;

template
class TQuery<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN>;

#ifdef FILLWAVE_GLES_3_0
#else

template
class TQuery<GL_SAMPLES_PASSED>;

template
class TQuery<GL_PRIMITIVES_GENERATED>;

template
class TQuery<GL_TIME_ELAPSED>;

#endif

} /* flc */
} /* flw */
