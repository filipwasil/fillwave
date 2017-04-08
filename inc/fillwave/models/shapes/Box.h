/*
 * Box.h
 *
 *  Created on: 9 Jun 2015
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

#ifndef BOX_H_
#define BOX_H_

#include <fillwave/models/shapes/Quad.h>

namespace flw {
namespace flf {

/*! \class Box
 * \brief Basic Shape for general usage. Indices and vertices provided.
 */

class Box : public Shape<flc::VertexBasic> {
public:
  Box(GLfloat quadSize = 1.0f)
      : mSize(quadSize), mQuad(quadSize) {
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

  virtual ~Box() = default;

  void generateVertices();

  void generateSide();

  void generateIndices();

private:
  GLfloat mSize;
  Quad mQuad;
};

} /* flf */
} /* flw */
#endif /* BOX_H_ */
