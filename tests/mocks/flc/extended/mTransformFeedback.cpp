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

#include <flw/flc/extended/rendering/TransformFeedback.h>
#include <flw/Log.h>

FLOGINIT_DEFAULT()

namespace flw {
namespace flc {

TransformFeedback::TransformFeedback(GLsizei howMany)
  : mHowMany(howMany)
  , mTarget(GL_TRANSFORM_FEEDBACK) {

}

TransformFeedback::~TransformFeedback() {

}

void TransformFeedback::bind(GLuint id) const {

}

void TransformFeedback::begin(GLenum primitiveMode) {

}


void TransformFeedback::end() {

}

void TransformFeedback::pause() {

}

void TransformFeedback::resume() {

}

GLuint TransformFeedback::getHandle(GLuint id) {
  return id < FILLWAVE_GLOBJECTS_MAX ? mHandles[id] : 0;
}

} /* flc */
} /* flw */
