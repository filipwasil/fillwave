/*
 * VertexArray.cpp
 *
 *  Created on: 4 Apr 2014
 *      Author: Filip Wasil
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

#include <fillwave/extras/Log.h>

#include <fillwave/core/buffers/VertexArray.h>

FLOGINIT("VertexArray", FERROR | FFATAL)

namespace fillwave {
namespace core {

VertexArray::VertexArray(GLuint howMany)
:GLObject(howMany) {
   glGenVertexArrays(mHowMany, mHandles);
   FLOG_CHECK("Could not generate the VAO");
}

VertexArray::~VertexArray() {
   glDeleteVertexArrays(mHowMany, mHandles);
   FLOG_CHECK("Could not delete the VAO");
}

void VertexArray::bind(GLuint id) {
   glBindVertexArray(mHandles[id]);
   FLOG_CHECK("Could not bind the VAO");
}

void VertexArray::unbind() {
   glBindVertexArray(0);
   FLOG_CHECK("ould unbind the VAO");
}

void VertexArray::reload() {
   glGenVertexArrays(mHowMany, mHandles);
   FLOG_CHECK("reload");
}

} /* core */
} /* Fillwave */
