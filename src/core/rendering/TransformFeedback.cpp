/*
 * TransformFeedback.cpp
 *
 *  Created on: May 30, 2014
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


#include <fillwave/core/rendering/TransformFeedback.h>
#include <fillwave/extras/Log.h>

FLOGINIT("TransformFeedback", FERROR | FFATAL)

namespace fillwave {
namespace core {

TransformFeedback::TransformFeedback(GLsizei howMany)
:GLObject(howMany),
 mTarget(GL_TRANSFORM_FEEDBACK) {
  glGenTransformFeedbacks(mHowMany, mHandles);
}

TransformFeedback::~TransformFeedback() {
   glDeleteTransformFeedbacks(mHowMany, mHandles);
}

void TransformFeedback::bind(GLuint id) {
   glBindTransformFeedback(mTarget, mHandles[id]);
}

void TransformFeedback::begin(GLenum primitiveMode) {
   if ( primitiveMode != GL_POINTS &&
        primitiveMode != GL_LINES &&
        primitiveMode != GL_TRIANGLES
#ifndef __ANDROID__
        && primitiveMode != GL_TRIANGLES_ADJACENCY &&
        primitiveMode != GL_TRIANGLE_STRIP_ADJACENCY &&
        primitiveMode != GL_LINES_ADJACENCY &&
        primitiveMode != GL_LINE_STRIP_ADJACENCY
#endif
       )
      FLOG_ERROR("not valid primitive type");
   else
      glBeginTransformFeedback(primitiveMode);
}

void TransformFeedback::end() {
	glEndTransformFeedback();
}

void TransformFeedback::pause() {
   glPauseTransformFeedback();
}

void TransformFeedback::resume() {
   glResumeTransformFeedback();
}

} /* core */
} /* fillwave */
