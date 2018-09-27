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

#include <flw/flc/buffers/TVertexBuffer.h>

#include <flw/flf/loaders/ModelLoader.h>

namespace flw {
namespace flf {
class Animator;
}

namespace flc {

/*! \struct VertexBasic
 * \brief Stores the basic vertex data.
 */

struct VertexBasic {
  GLfloat mPosition[4];
  GLfloat mColor[4];
  GLfloat mNormal[3];
  GLfloat mNormalTangentMap[3];
  GLfloat mTextureUV[2];
  GLint mBoneID[ModelLoader::COUNT_BONES_USED];
  GLfloat mBoneWeight[ModelLoader::COUNT_BONES_USED];
};

/*! \struct FaceBasic
 * \brief Stores the face data for geometry built on Vertex Basic.
 */

struct FaceBasic {
  flc::VertexBasic vertices[3];
};

/*! \class VertexBufferBasic
 * \brief Vertex buffer specialized with VertexBasic data structure.
 */

class VertexBufferBasic : public TVertexBuffer<VertexBasic> {
public:

  VertexBufferBasic(
    std::function<float(float x, float y)> constructor
    , GLint chunkDensity
    , GLfloat gapSize
    , const std::vector<GLuint> &indices
    , GLuint dataStoreModification = GL_STATIC_DRAW);


  VertexBufferBasic(const std::vector<flc::VertexBasic> &vertices, GLuint dataStoreModification = GL_STATIC_DRAW);

  ~VertexBufferBasic() override = default;

  glm::vec3 getOcclusionBoxSize();

  void log() const override;
};

} /* flc */
} /* flw */
