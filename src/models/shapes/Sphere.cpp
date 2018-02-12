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

#include <fillwave/models/shapes/Sphere.h>

namespace flw {
namespace flf {

Sphere::Sphere(GLfloat radius, GLuint rings, GLuint sectors, glm::vec3 color) {
  float const R = 1.f / (float) (rings - 1);
  float const S = 1.f / (float) (sectors - 1);
  float r;
  float s;

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
      if (static_cast<GLuint>(r) == rings - 1 || static_cast<GLuint>(s) == sectors - 1) {
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

Sphere::~Sphere() = default;

} /* flf */
} /* flw */
