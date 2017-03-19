/*
 * SphereSkybox.h
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

#ifndef SPHERESKYBOX_H_
#define SPHERESKYBOX_H_

#include <fillwave/core/buffers/VertexBufferPosition.h>
#include <fillwave/models/shapes/Shape.h>

namespace fillwave {
class Engine;
namespace framework {

/*! \class SphereSkybox
 * \brief Shape<core::VertexPosition> encapsulating vertices and indices for triangle drawn UV sphere.
 *
 */

class SphereSkybox : public Shape<core::VertexPosition> {
public:
  SphereSkybox(GLfloat radius, GLuint rings, GLuint sectors) {
    float const R = 1.f / (float) (rings - 1);
    float const S = 1.f / (float) (sectors - 1);
    GLuint r, s;

    mVertices.resize (rings * sectors);

    auto vb = mVertices.begin ();

    for (r = 0; r < rings; r++) {
      for (s = 0; s < sectors; s++) {
        float const y = sin (-F_PI_2 + F_PI * r * R);
        float const x = cos (2 * F_PI * s * S) * sin (F_PI * r * R);
        float const z = sin (2 * F_PI * s * S) * sin (F_PI * r * R);

        (*vb).mPosition[0] = x * radius * mScale;
        (*vb).mPosition[1] = y * radius * mScale;
        (*vb).mPosition[2] = z * radius * mScale;
        (*vb).mPosition[3] = 1.0;

        vb++;
      }
    }

    mIndices.resize (rings * sectors * 6);
    auto i = mIndices.begin ();
    for (r = 0; r < rings - 1; r++) {
      for (s = 0; s < sectors; s++) {
        if (r == rings - 1 || s == sectors - 1) {
          break;
        }

        *i++ = r * sectors + (s + 1);
        *i++ = r * sectors + s;
        *i++ = (r + 1) * sectors + (s + 1);
        *i++ = (r + 1) * sectors + s;
        *i++ = (r + 1) * sectors + (s + 1);
        *i++ = r * sectors + s;
      }
    }
  }

  virtual ~SphereSkybox() = default;

private:
  const GLfloat mScale = 100.0;
};

} /* framework */
} /* fillwave */

#endif /* SPHERESKYBOX_H_ */
