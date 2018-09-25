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

#include <flw/flf/models/shapes/SphereSkybox.h>

namespace flw {
namespace flf {

SphereSkybox::SphereSkybox(GLfloat radius, GLuint rings, GLuint sectors) {
  float const R = 1.f / (float) (rings - 1);
  float const S = 1.f / (float) (sectors - 1);
  GLuint r, s;

  mVertices.resize(rings * sectors);

  auto vb = mVertices.begin();

  for (r = 0; r < rings; r++) {
    for (s = 0; s < sectors; s++) {
      float const y = sin(-F_PI_2 + F_PI * r * R);
      float const x = cos(2 * F_PI * s * S) * sin(F_PI * r * R);
      float const z = sin(2 * F_PI * s * S) * sin(F_PI * r * R);

      (*vb).mPosition[0] = x * radius * mScale;
      (*vb).mPosition[1] = y * radius * mScale;
      (*vb).mPosition[2] = z * radius * mScale;
      (*vb).mPosition[3] = 1.0;

      vb++;
    }
  }

  mIndices.resize(rings * sectors * 6);
  auto i = mIndices.begin();
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

SphereSkybox::~SphereSkybox() = default;

} /* flf */
} /* flw */
