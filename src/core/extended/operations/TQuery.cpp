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

#include <fillwave/core/operations/TQuery.h>

#include <fillwave/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

template <GLenum TARGET>
TQuery<TARGET>::TQuery(GLuint howMany)
  : mHowMany(howMany) {
  glGenQueries(mHowMany, mHandles);
  fLogC("Could not create query");
}

template <GLenum TARGET>
TQuery<TARGET>::~TQuery() {
  glDeleteQueries(mHowMany, mHandles);
  fLogC("Could not delete query");
}

template <GLenum TARGET>
GLuint TQuery<TARGET>::getID(GLuint id) const {
  return mHandles[id];
}

template <GLenum TARGET>
void TQuery<TARGET>::begin(GLuint id) {
  glBeginQuery(TARGET, mHandles[id]);
  fLogC("Could not begin query");
}

template <GLenum TARGET>
void TQuery<TARGET>::end() {
  glEndQuery(TARGET);
  fLogC("Could not end query");
}

template <GLenum TARGET>
GLuint TQuery<TARGET>::getResultAsync(GLuint resultIfNotAvailable, GLuint id) {
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

template <GLenum TARGET>
GLuint TQuery<TARGET>::getResultSync(GLuint id) {
  GLuint result;
  glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
  fLogC("Could not get querry sync result");
  return result;
}

template <GLenum TARGET>
GLboolean TQuery<TARGET>::getResultAvailable(GLuint id) {
  GLuint result;
  glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
  return result ? GL_TRUE : GL_FALSE;
}

template <GLenum TARGET>
void TQuery<TARGET>::reload() {
  glGenQueries(mHowMany, mHandles);
  fLogC("reload");
}

template <GLenum TARGET>
void TQuery<TARGET>::log() {
  for (GLsizei id = 0; id < mHowMany; ++id) {
    if (glIsQuery(mHandles[id])) {
      fLogI("Query ", mHandles[id], " exists");
    } else {
      fLogI("Query ", mHandles[id], " does not exist");
    }
  }
}

template
class TQuery<GL_ANY_SAMPLES_PASSED>;

template
class TQuery<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN>;

#ifdef FILLWAVE_BACKEND_OPENGL_ES_30
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
