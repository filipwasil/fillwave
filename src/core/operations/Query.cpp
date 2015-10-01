/*
 * Query.cpp
 *
 *  Created on: May 17, 2015
 *      Author: filip
 */

/*************************************************************************
 *
 * Copyright (C) 2014 Filip Wasil
 *
 * Filip Wasil CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2014] Filip Wasil
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Filip Wasil. The intellectual and technical
 * concepts contained herein are proprietary to Filip Wasil
 * and his suppliers and may be covered by Polish and Foreign
 * Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination of this information or reproduction
 * of this material is strictly forbidden unless prior written
 * permission is obtained from Filip Wasil.
 *
 * To use the code, you must contact the author directly and ask permission.
 *
 * filip.wasil@gmail.com
 *
 */

#include <fillwave/core/operations/Query.h>
#include <fillwave/extras/Log.h>

FLOGINIT("Query", FERROR | FFATAL | FINFO)

namespace fillwave {
namespace core {

template <GLenum target>
Query<target>::Query(GLsizei howMany)
:GLObject(howMany) {
   glGenQueries(mHowMany, mHandles);
   FLOG_CHECK("Could not create query");
}

template <GLenum target>
Query<target>::~Query() {
   glDeleteQueries(mHowMany, mHandles);
   FLOG_CHECK("Could not delete query");
}

template <GLenum target>
GLuint Query<target>::getID(GLuint id) {
   return mHandles[id];
}

template <GLenum target>
void Query<target>::begin(GLuint id) {
   glBeginQuery(mTarget, mHandles[id]);
   FLOG_CHECK("Could not begin query");
}

template <GLenum target>
void Query<target>::end() {
   glEndQuery(mTarget);
   FLOG_CHECK("Could not end query");
}

template <GLenum target>
GLuint Query<target>::getResultAsync(GLuint resultIfNotAvailable, GLuint id) {
   GLuint result;
   glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
   FLOG_CHECK("Could not get querry result state");
   if (result) {
      glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
      FLOG_CHECK("Could not get query async result");
      return result;
   } else {
      return resultIfNotAvailable;
   }
}

template <GLenum target>
GLuint Query<target>::getResultSync(GLuint id) {
   GLuint result;
   glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT, &result);
   FLOG_CHECK("Could not get querry sync result");
   return result;
}

template <GLenum target>
GLboolean Query<target>::getResultAvailable(GLuint id) {
   GLuint result;
   glGetQueryObjectuiv(mHandles[id], GL_QUERY_RESULT_AVAILABLE, &result);
   return result ? GL_TRUE : GL_FALSE;
}

template <GLenum target>
void Query<target>::reload() {
   glGenQueries(mHowMany, mHandles);
   FLOG_CHECK("reload");
}

template <GLenum target>
void Query<target>::log() {
   for (GLuint id=0; id<mHowMany; id++) {
      if (glIsQuery(mHandles[id])){
         FLOG_INFO("Query %d exists", mHandles[id]);
      } else {
         FLOG_INFO("Query %d does not exist", mHandles[id]);
      }
   }
}

template class Query<GL_ANY_SAMPLES_PASSED>;
template class Query<GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN>;
#ifdef __ANDROID__
#else
template class Query<GL_SAMPLES_PASSED>;
template class Query<GL_PRIMITIVES_GENERATED>;
template class Query<GL_TIME_ELAPSED>;
#endif

} /* core */
} /* fillwave */
