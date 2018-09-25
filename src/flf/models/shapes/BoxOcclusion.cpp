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

#include <flw/flf/models/shapes/BoxOcclusion.h>

namespace flw {
namespace flf {

/*! \class BoxOcclusion
 * \brief Basic Shape for specific usage, providing each model to participate in OQ algorithm
 */

BoxOcclusion::BoxOcclusion(GLfloat quadSize)
  : mSize(quadSize)
  , mQuad(quadSize) {

  std::vector<flc::VertexBasic> quadVertices = mQuad.getVertices();
  std::vector<glm::vec3> vertVertices;

  mVertices.resize(36);

  /* Back */
  for (int i = 0; i < 6; i++) {
    vertVertices.push_back(glm::vec3(quadVertices[i].mPosition[0],
                                     quadVertices[i].mPosition[1],
                                     quadVertices[i].mPosition[2] += mSize));
  }

  /* Down */
  for (GLuint i = 0; i < 6; i++) {
    glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(90.0f)));
    vertVertices.push_back(vec);
  }

  /* Back */
  for (GLuint i = 0; i < 6; i++) {
    glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(180.0f)));
    vertVertices.push_back(vec);
  }

  /* Up */
  for (GLuint i = 0; i < 6; i++) {
    glm::vec3 vec(glm::rotateX(vertVertices[i], glm::radians(270.0f)));
    vertVertices.push_back(vec);
  }

  /* Right */
  for (GLuint i = 0; i < 6; i++) {
    glm::vec3 vec = glm::rotateZ(glm::rotateX(vertVertices[i], glm::radians(90.0f)), glm::radians(90.0f));
    vertVertices.push_back(vec);
  }

  for (GLuint i = 0; i < 6; i++) {
    glm::vec3 vec = glm::rotateZ(glm::rotateX(vertVertices[i], glm::radians(90.0f)), glm::radians(-90.0f));
    vertVertices.push_back(vec);
  }

  /* Vertices and Indices */
  for (GLuint i = 0; i < vertVertices.size(); i++) {
    mVertices[i].mPosition[0] = vertVertices[i].x;
    mVertices[i].mPosition[1] = vertVertices[i].y;
    mVertices[i].mPosition[2] = vertVertices[i].z;
    mVertices[i].mPosition[3] = 1.0f;
    mIndices.push_back(i);
  }
}

BoxOcclusion::~BoxOcclusion() = default;

} /* flf */
} /* flw */
