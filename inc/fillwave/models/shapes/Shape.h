/*
 * Shape.h
 *
 *  Created on: 18 May 2015
 *      Author: Filip Wasil
 *
 * Copyright (c) 2016, Filip Wasil
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

#ifndef SHAPE_H_
#define SHAPE_H_

#include <fillwave/OpenGL.h>
#include <fillwave/Math.h>
#include <vector>

namespace flw {
namespace flf {

/*! \class Shape
 * \brief Base class for every shape. Specialized with Vertex data structure.
 *
 */

template <class T>
class Shape {
public:
  Shape() {

  }

  virtual ~Shape() {

  }

  std::vector<T> getVertices() {
    return mVertices;
  }

  GLuint getVerticesSize() {
    return mVertices.size();
  }

  std::vector<GLuint> getIndices() {
    return mIndices;
  }

  GLuint getIndicesSize() {
    return mIndices.size();
  }

protected:
  std::vector<T> mVertices;
  std::vector<GLuint> mIndices;
};

} /* flf */
} /* flw */
#endif /* SHAPE_H_ */
