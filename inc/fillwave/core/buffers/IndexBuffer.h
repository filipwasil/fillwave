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

#include <fillwave/core/buffers/IBuffer.h>
#include <fillwave/Assets.h>
#include <vector>

namespace flw {
namespace flc {

/*! \class IndexBuffer
 * \brief IndexBufferObject - IBO.
 */

class IndexBuffer : public IBuffer {
public:
  // xxx fill - fills buffer with sequential data
  IndexBuffer(GLuint elements, bool fill, GLuint dataStoreModification = GL_STATIC_DRAW);

  IndexBuffer(const std::vector<GLuint> &data, GLuint dataStoreModification = GL_STATIC_DRAW);

#ifdef FILLWAVE_MODEL_LOADER_ASSIMP

  IndexBuffer(const aiMesh *shape, GLuint dataStoreModification = GL_STATIC_DRAW);

#endif /* FILLWAVE_MODEL_LOADER_ASSIMP */

  ~IndexBuffer() override = default;

  GLuint *getDataInternal();

  void emptyCPU() override;

  void emptyGPU() override;

protected:
  std::vector<GLuint> mDataIndices;
};

} /* flc */
} /* flw */
