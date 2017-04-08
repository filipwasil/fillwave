/*
 * Sphere.h
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

#ifndef SPHERE_H_
#define SPHERE_H_

#include <fillwave/core/buffers/VertexBufferBasic.h>
#include <fillwave/models/shapes/Shape.h>

namespace fillwave {
namespace framework {

/*! \class Sphere
 * \brief Shape<core::VertexBasic> encapsulating vertices and indices for triangle drawn UV sphere.
 *
 */

class Sphere : public Shape<core::VertexBasic> {

public:
  Sphere(GLfloat radius, GLuint rings = 10, GLuint sectors = 10, glm::vec3 color = glm::vec3(0.0)) {
    float const R = 1.f / (float) (rings - 1);
    float const S = 1.f / (float) (sectors - 1);
    float r, s;

    mVertices.resize(rings * sectors);

    auto vb = mVertices.begin();

    for (r = 0; r < rings; r++) {
      for (s = 0; s < sectors; s++) {
        float const y = sin(-F_PI_2 + F_PI * r * R);
        float const x = cos(2 * F_PI * s * S) * sin(F_PI * r * R);
        float const z = sin(2 * F_PI * s * S) * sin(F_PI * r * R);

        (*vb).mTextureUV[0] = s * S;
        (*vb).mTextureUV[1] = r * R;

        (*vb).mPosition[0] = x * radius;
        (*vb).mPosition[1] = y * radius;
        (*vb).mPosition[2] = z * radius;
        (*vb).mPosition[3] = 1.0;

        (*vb).mNormal[0] = x;
        (*vb).mNormal[1] = y;
        (*vb).mNormal[2] = z;

        (*vb).mColor[0] = color.x;
        (*vb).mColor[1] = color.y;
        (*vb).mColor[2] = color.z;
        vb++;
      }
    }

    mIndices.resize((rings - 1) * sectors * 6 - 1);
    auto i = mIndices.begin();
    for (r = 0; r < rings - 1; r++) {
      for (s = 0; s < sectors; s++) {
        if (r == rings - 1 || s == sectors - 1) {
          break;
        }

        *i++ = static_cast<GLuint>(r * sectors + (s + 1));
        *i++ = static_cast<GLuint>(r * sectors + s);
        *i++ = static_cast<GLuint>((r + 1) * sectors + (s + 1));
        *i++ = static_cast<GLuint>((r + 1) * sectors + s);
        *i++ = static_cast<GLuint>((r + 1) * sectors + (s + 1));
        *i++ = static_cast<GLuint>(r * sectors + s);
      }
    }
  }

  ~Sphere() = default;
};

} /* framework */
} /* fillwave */

#endif /* SPHERE_H_ */
