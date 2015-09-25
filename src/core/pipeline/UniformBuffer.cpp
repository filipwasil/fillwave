/*
 * UniformBuffer.cpp
 *
 *  Created on: May 18, 2014
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

#include <fillwave/core/pipeline/UniformBuffer.h>
#include <fillwave/extras/Log.h>

FLOGINIT("UniformBuffer", FERROR | FFATAL)

namespace fillwave {
namespace core {

UniformBuffer::UniformBuffer(std::string name,
                             GLuint index,
                             GLuint uniformBlockSize,
                             GLuint bindingPoint,
                             GLuint dataStoreModification)
:Buffer(GL_UNIFORM_BUFFER,
        dataStoreModification,
        index),
 mName(name),
 mBindingPoint(bindingPoint) {
   bind();
   bindBase();
   unbind();
   mSize = uniformBlockSize;

}

UniformBuffer::~UniformBuffer() {

}

void UniformBuffer::bindRange(GLuint id) {
   return glBindBufferRange(mTarget, mBindingPoint, mHandles[id], 0, mSize);
}

void UniformBuffer::push(GLfloat* data) {
   bind();
   mData = data;
   send();
   mRefresh = GL_TRUE;//xxx always refresh
   unbind();
}

std::string UniformBuffer::getName() {
   return mName;
}

} /* core */
} /* fillwave */
